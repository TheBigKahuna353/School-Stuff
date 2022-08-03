def connection_setup_delay(cable_length_km, light_speed_kmps, message_length_b, data_rate_bps, processing_time_s):
    """
    Calculates the connection setup delay.
    """
    
    return ((cable_length_km / light_speed_kmps) + (message_length_b / data_rate_bps) + processing_time_s) * 4

def message_delay(conn_setup_time_s, cable_length_km, light_speed_kmps, message_length_b, data_rate_bps):
    """
    Calculates the message delay.
    """
    return conn_setup_time_s + (message_length_b / data_rate_bps) + (cable_length_km / light_speed_kmps)*2


import math

def total_number_bits(max_user_data_per_packet_b, overhead_per_packet_b, message_length_b):
    s = max_user_data_per_packet_b
    o = overhead_per_packet_b
    m = message_length_b

    num_packets = math.ceil(m / s)
    num_bits_o = num_packets * o
    num_bits_m = m
    return num_bits_m + num_bits_o

def packet_transfer_time(link_length_km, light_speed_kmps, processing_delay_s, data_rate_bps, max_user_data_per_packet_b, overhead_per_packet_b):
    l = link_length_km
    c = light_speed_kmps
    p = processing_delay_s
    r = data_rate_bps
    s = max_user_data_per_packet_b
    o = overhead_per_packet_b
    total_bits = s + o
    send_time = l / c
    transfer_time = total_bits / r
    return (send_time + transfer_time + p) * 2

def total_transfer_time(link_length_km, light_speed_kmps, processing_delay_s, data_rate_bps, max_user_data_per_packet_b, overhead_per_packet_b, message_length_b):
    l = link_length_km
    c = light_speed_kmps
    p = processing_delay_s
    r = data_rate_bps
    s = max_user_data_per_packet_b
    o = overhead_per_packet_b
    m = message_length_b
    packets = m//s
    total_bits = (s + o)
    send_time = l / c
    transfer_time = total_bits / r
    return send_time*2 + (transfer_time) * (packets + 1) + p*2

print(total_transfer_time (10000, 200000, 0.001, 1000000, 1000, 100, 1000000000))