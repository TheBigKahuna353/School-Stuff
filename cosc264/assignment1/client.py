"""
client.py
"""

import select
import socket
import sys
from packet import DT_Request, check_response, get_whole_response

# get command line arguments
try:
    request = sys.argv[1]
    ip = sys.argv[2]
    port = int(sys.argv[3])
except IndexError:
    print("Please enter three arguments")
    sys.exit(1)

if port < 1024 or port > 64000:
    print("Please enter ports between 1024 and 64000")
    sys.exit(1)

if request not in ["date", "time"]:
    print("Argument 1 must be either 'date' or 'time'")
    sys.exit(1)

if socket.getaddrinfo(ip, port)[0][0] != socket.AF_INET:
    print("Argument 2 must be a valid IP address")
    sys.exit(1)


def print_nicely(List):
    """
    print the list nicely
    """
    for (name, value) in List:
        print(name + ":" + " " * (16 - len(name)), value)
    print()

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect((ip, port))
packet = DT_Request(request)
packet.pack()
client.send(packet.buffer)
writeable, readable, exceptional = select.select([client], [], [], 1)

if writeable:
    response = client.recv(1024)
    if check_response(response):
        print_nicely(get_whole_response(response))
    elif response == b"":
        print("Server timed out")
    else:
        print("Invalid response")
else:
    print("Server timed out")