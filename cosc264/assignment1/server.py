"""
Server.py

"""

import select
import socket
import sys
import datetime
from packet import DT_Response, check_request, get_request

# get command line arguments
try:
    ports = [int(sys.argv[1]), int(sys.argv[2]), int(sys.argv[3])]
    for port in ports:
        if port < 1024 or port > 64000:
            raise ValueError
except IndexError:
    print("Please enter three ports")
    sys.exit(1)
except ValueError:
    print("Please enter ports between 1024 and 64000")
    sys.exit(1)
except:
    print("Usage: python3 server.py port1 port2 port3")
    sys.exit(1)

# te reo months list
te_reo_months = [
    "Kohitātea",
    "Hui-tanguru",
    "Poutū-te-rangi",
    "Paenga-whāwhā",
    "Haratua",
    "Pipiri",
    "Hōngongoi",
    "Here-turi-kōkā",
    "Mahuru",
    "Whiringa-ā-nuku",
    "Whiringa-ā-rangi",
    "Hakihea"
]

# german months list
german_months = [
    "Januar",
    "Februar",
    "M¨arz",
    "April",
    "Mai",
    "Juni",
    "Juli",
    "August",
    "September",
    "Oktober",
    "November",
    "Dezember"
]


def date(language):
    """
    return the text literal for the current date in the given language
    """
    date = datetime.date.today()
    day = date.strftime("%d")
    year = date.strftime("%Y")
    if language == "te_reo":
        month = te_reo_months[date.month - 1]
        return "Ko te ra o tenei ra ko %s %s, %s" %(month, day, year)
    elif language == "german":
        month = german_months[date.month - 1]
        return "Heute ist der %s. %s %s" %(day, month, year)
    else:
        month = date.strftime("%B")
        return "Today's date is %s %s, %s" %(month, day, year)

def time(language):
    """
    return the text literal for the current time in the given language
    """
    time = datetime.datetime.now().strftime("%H:%M")
    if language == "te_reo":
        return "Ko te wa o tenei wa %s" % time
    elif language == "german":
        return "Die Uhrzeit ist %s" % time
    else:
        return "The current time is %s" % time


class Server(socket.socket):
    """
    Server class
    """
    def __init__(self, port, language) -> None:
        self.port = port
        self.language = language
        super().__init__(socket.AF_INET, socket.SOCK_STREAM)
        self.bind(("", port))
        self.listen(5)
    
    def connection(self) -> None:
        """
        handle the connection
        """
        client, address = self.accept()
        request = self.recieve(client)
        if request: # if the request is valid, send the response, else, ignore the request
            self.send(client, get_request(request))
        client.close()
    
    def recieve(self, client) -> None:
        """
        recieve the request from the client and check if it is valid
        """
        request = client.recv(1024).decode()
        request = bytearray(request, "utf-8")
        if check_request(request):
            return request
        return None
        
    def send(self, client, request) -> None:
        """
        send the response to the client
        """
        date_time = list(map(int,datetime.datetime.now().strftime("%Y %m %d %H %M %S").split()))
        data = time(self.language) if request == "time" else date(self.language)
        data = data.encode("utf-8")
        packet = DT_Response(self.language, date_time, data)
        packet.pack()
        client.send(packet.buffer)


#globals
server = Server(ports[0], "english")
server2 = Server(ports[1], "te_reo")
server3 = Server(ports[2],  "german")
inputs = [server, server2, server3]


def main():
    """
    main function
    """
    while True: # loop forever
        readable, writable, exceptional = select.select(inputs, [], []) # select the sockets that are ready to be read
        for s in readable: # read the sockets
            s.connection() # handle the connection

if __name__ == "__main__":
    main()