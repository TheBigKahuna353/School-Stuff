def check_param(value, bits):
    if value < 0 or value > 2**bits-1:
        return True
    return False


def compose_header(version, hdrlen, tosdscp, totallength, identification, flags, fragmentoffset, timetolive, protocoltype, headerchecksum, sourceaddress, destinationaddress):
    if version != 4:
        return 1
    if check_param(hdrlen, 4):
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

def basic_packet_check(packet):
    if len(packet) < 20:
        return 1
    if packet[0] >> 4 != 4:
        return 2
    checksum = sum(packet[:20]) 
    if checksum & 0xFF != 0:
        return hex(checksum)
    total_length = packet[2] << 8 | packet[3]
    if len(packet) != total_length:
        return 4
    return 0


packet = bytearray([0x45, 0x0, 0x0, 0x1e, 0x4, 0xd2, 0x0, 0x0, 0x40, 0x6, 0x20, 0xb4, 0x12, 0x34, 0x56, 0x78, 0x98, 0x76, 0x54, 0x32, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0])
print(basic_packet_check(packet))