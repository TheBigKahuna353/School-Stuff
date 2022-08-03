def check_param(value, bits):
    if value < 0 or value > 2**bits-1:
        return True
    return False


def compose_header(version, hdrlen, tosdscp, totallength, identification, flags, fragmentoffset, timetolive, protocoltype, headerchecksum, sourceaddress, destinationaddress):
    if version != 4:
        return 1
    if check_param(hdrlen, 4) or hdrlen < 5:
        return 2
    if check_param(tosdscp, 6):
        return 3
    if check_param(totallength, 16):
        return 4
    if check_param(identification, 16):
        return 5
    if check_param(flags, 3):
        return 6
    if check_param(fragmentoffset, 13):
        return 7
    if check_param(timetolive, 8):
        return 8
    if check_param(protocoltype, 8):
        return 9
    if check_param(headerchecksum, 16):
        return 10
    if check_param(sourceaddress, 32):
        return 11
    if check_param(destinationaddress, 32):
        return 12

    
    a = bytearray(20)
    a[0] = version << 4 | hdrlen
    a[1] = tosdscp
    a[2] = totallength >> 8 & 0xFF
    a[3] = totallength & 0xFF
    a[4] = identification >> 8 & 0xFF
    a[5] = identification & 0xFF
    a[6] = flags << 5 | (fragmentoffset >> 8 & 0x1F)
    a[7] = fragmentoffset & 0xFF
    a[8] = timetolive
    a[9] = protocoltype
    a[10] = headerchecksum >> 8 & 0xFF
    a[11] = headerchecksum & 0xFF
    a[12] = sourceaddress >> 24 & 0xFF
    a[13] = sourceaddress >> 16 & 0xFF
    a[14] = sourceaddress >> 8 & 0xFF
    a[15] = sourceaddress & 0xFF
    a[16] = destinationaddress >> 24 & 0xFF
    a[17] = destinationaddress >> 16 & 0xFF
    a[18] = destinationaddress >> 8 & 0xFF
    a[19] = destinationaddress & 0xFF
    return a

def checksum(packet):
    sum = 0
    for i in range(0, len(packet), 2):
        if i == len(packet)-1:
            sum += packet[i]
        else:
            sum += packet[i] << 8 | packet[i+1]
    sum = (sum & 0xFFFF) + (sum >> 16)
    return sum

def basic_packet_check(packet):
    if len(packet) < 20:
        return 1
    if packet[0] >> 4 != 4:
        return 2
    check = checksum(packet) 
    if check != 0xFFFF:
        return 3
    total_length = packet[2] << 8 | packet[3]
    if len(packet) != total_length:
        return 4
    return True

def destination_address(packet):
    address = packet[16] << 24 | packet[17] << 16 | packet[18] << 8 | packet[19]
    dd = '{:032b}'.format(address)
    string = ""
    for i in range(0, 32, 8):
        string += str(int(dd[i:i+8], 2)) + "."
    return address, string[:-1]

def payload(packet):
    length = packet[0] & 0xF
    return packet[length*4:]

def create_checksum(packet, length):
    sum = 0
    for i in range(0, length, 2):
        if i == length-1:
            sum += packet[i]
        else:
            sum += packet[i] << 8 | packet[i+1]
    sum = ~((sum & 0xFFFF) + (sum >> 16))
    packet[10] = sum >> 8 & 0xFF
    packet[11] = sum & 0xFF
    

def compose_packet(hdrlen, tosdscp, identification, flags, fragmentoffset, timetolive, protocoltype, sourceaddress, destinationaddress, payload):
    if check_param(hdrlen, 4) or hdrlen < 5:
        return 2
    if check_param(tosdscp, 6):
        return 3
    if check_param(identification, 16):
        return 5
    if check_param(flags, 3):
        return 6
    if check_param(fragmentoffset, 13):
        return 7
    if check_param(timetolive, 8):
        return 8
    if check_param(protocoltype, 8):
        return 9
    if check_param(sourceaddress, 32):
        return 11
    if check_param(destinationaddress, 32):
        return 12
    version = 4
    totallength = hdrlen*4 + len(payload)
    a = bytearray(totallength)
    a[0] = version << 4 | hdrlen
    a[1] = tosdscp << 2
    a[2] = totallength >> 8 & 0xFF
    a[3] = totallength & 0xFF
    a[4] = identification >> 8 & 0xFF
    a[5] = identification & 0xFF
    a[6] = flags << 5 | (fragmentoffset >> 8 & 0x1F)
    a[7] = fragmentoffset & 0xFF
    a[8] = timetolive
    a[9] = protocoltype
    # a[10] = headerchecksum >> 8 & 0xFF
    # a[11] = headerchecksum & 0xFF
    a[12] = sourceaddress >> 24 & 0xFF
    a[13] = sourceaddress >> 16 & 0xFF
    a[14] = sourceaddress >> 8 & 0xFF
    a[15] = sourceaddress & 0xFF
    a[16] = destinationaddress >> 24 & 0xFF
    a[17] = destinationaddress >> 16 & 0xFF
    a[18] = destinationaddress >> 8 & 0xFF
    a[19] = destinationaddress & 0xFF
    for i in range(len(payload)):
        a[hdrlen*4+i] = payload[i]
    create_checksum(a, hdrlen*4)
    return a
