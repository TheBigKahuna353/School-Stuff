def queueingDelay (packetSize_bits, dataRate_bps, flagCurrentTransmission, numberInQueue):
    L    =  packetSize_bits
    R    =  dataRate_bps
    flag =  flagCurrentTransmission
    N    =  numberInQueue
    if not flag:
        return 0
    total_bits = (L-1) * N + (L/2)
    return total_bits / R

def fragmentOffsets (fragmentSize_bytes, overheadSize_bytes, messageSize_bytes):
    F  =  fragmentSize_bytes
    O  =  overheadSize_bytes
    M  =  messageSize_bytes
    msg_size = F-O
    temp = [i * msg_size for i in range(M//msg_size+1)]
    return temp

def packetSwitching (numberRouters, messageSize_b, userDataSize_b, overheadSize_b, processingTime_s, dataRate_bps, propagationDelay_s):
    N  =  numberRouters
    M  =  messageSize_b
    S  =  userDataSize_b
    O  =  overheadSize_b
    P  =  processingTime_s
    R  =  dataRate_bps
    T  =  propagationDelay_s
    packet = S+O
    num_packets = M/S
    #time for 1 bit to travel through all routers
    travel_time = P*N + T*(N+1)
    sending_time = packet/R # r = s/t  t = s/r 
    sending_time *= num_packets
    total = travel_time + sending_time
    print(total, travel_time, sending_time)
    return total
    

def IPToString (addr):
    temp = [str(addr >> i & 0xFF) for i in range(24, -1, -8)]
    return ".".join(temp)

import math

def number_fdma_channels (b_hz, g_hz, u_hz):
    B = b_hz
    G = g_hz
    U = u_hz
    return math.floor(B/(G+U))

def number_tdma_users (s_s, g_s, u_s):
    S = s_s
    G = g_s
    U = u_s
    return math.floor(S/(G+U))

print ()
