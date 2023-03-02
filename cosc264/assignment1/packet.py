"""
packet.py
"""

class Packet:
    """
    Base class for all packets.
    """
    magic_no = 0x497E

    def __init__(self, length):
        self.buffer = bytearray(length)
        self.length = length


class DT_Request(Packet):
    """
    packet for requesting date or time
    """
    type = 0x0001

    def __init__(self, request):
        super().__init__(6)
        self.request = 0x0001 if request == "date" else 0x0002
    
    def pack(self):
        """
        pack the packet
        """
        self.buffer[0] = self.magic_no >> 8
        self.buffer[1] = self.magic_no & 0xFF
        self.buffer[2] = self.type >> 8
        self.buffer[3] = self.type & 0xFF
        self.buffer[4] = self.request >> 8
        self.buffer[5] = self.request & 0xFF


def check_request(buffer):
    """
    check if the packet is a valid request packet
    """
    if buffer[0] << 8 | buffer[1] != 0x497E:                    # check magic number
        return False
    if buffer[2] << 8 | buffer[3] != 0x0001:                    # check type
        return False
    if buffer[4] << 8 | buffer[5] not in [0x0001, 0x0002]:      # check language
        return False
    return True

def get_request(buffer):
    """
    get the request type from a request packet
    """
    return buffer[4] << 8 | buffer[5]

class DT_Response(Packet):
    """
    packet for sending date or time
    """
    type = 0x0002

    def __init__(self, language, datetime, data):
        super().__init__(13 + len(data))
        self.language = 0x0001 if language == "english" else 0x0002 if language == "te_reo" else 0x0003
        self.datetime = datetime
        self.data = data

    def pack(self):
        """
        pack the packet
        """
        self.buffer[0] = self.magic_no >> 8
        self.buffer[1] = self.magic_no & 0xFF
        self.buffer[2] = self.type >> 8
        self.buffer[3] = self.type & 0xFF
        self.buffer[4] = self.language >> 8
        self.buffer[5] = self.language & 0xFF
        self.buffer[6] = self.datetime[0] >> 8
        self.buffer[7] = self.datetime[0] & 0xFF
        self.buffer[8] = self.datetime[1]
        self.buffer[9] = self.datetime[2]
        self.buffer[10] = self.datetime[3]
        self.buffer[11] = self.datetime[4]
        self.buffer[12] = self.length - 13
        for i in range(13, self.length):
            self.buffer[i] = self.data[i - 13]


def check_response(buffer):
    """
    check if the packet is a valid response packet
    """
    if len(buffer) < 13:                                                # check if buffer is at least 13 bytes long
        return False
    if buffer[0] << 8 | buffer[1] != 0x497E:                            # check magic number
        return False
    if buffer[2] << 8 | buffer[3] != 0x0002:                            # check type
        return False
    if buffer[4] << 8 | buffer[5] not in [0x0001, 0x0002, 0x0003]:      # check language
        return False
    if (buffer[6] << 8 | buffer[7]) > 2100:                             # check year is below 2100
        return False
    if not(0x1 <= (buffer[8]) <= 0x12):                                 # check month is between 1 and 12
        return False
    if not(0x1 <= buffer[9] <= 0x1f):                                   # check day is between 1 and 31
        return False
    if not(0x0 <= buffer[10] <= 0x18):                                  # check hour is between 0 and 24
        return False
    if not(0x0 <= buffer[11] <= 0x3c):                                  # check minute is between 0 and 60
        return False
    if len(buffer) != 13 + buffer[12]:                                  # check length is correct
        return False
    return True

def get_whole_response(buffer):
    """
    return the whole response from a response packet in a list with the field names as the first element
    """
    temp = []
    temp.append(("Magic Number", hex(buffer[0] << 8 | buffer[1])))      # magic number
    temp.append(("type", hex(buffer[2] << 8 | buffer[3])))              # type
    temp.append(("language", buffer[4] << 8 | buffer[5]))               # language
    temp.append(("year", buffer[6] << 8 | buffer[7]))                   # year
    temp.append(("month", buffer[8]))                                   # month
    temp.append(("day", buffer[9]))                                     # day
    temp.append(("hour", buffer[10]))                                   # hour
    temp.append(("minute", buffer[11]))                                 # minute
    temp.append(("length", buffer[12]))                                 # length
    temp.append(("data", str(buffer[13:], 'utf-8')))                    # data
    return temp
