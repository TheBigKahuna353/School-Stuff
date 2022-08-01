# def transmission_delay(packet_length_bytes, rate_bps):
#     """
#     Calculates the transmission delay of a packet.
#     """
#     rate_bps /= 8 
#     return packet_length_bytes / rate_bps

# print(f"{transmission_delay(1000000, 4000000):.3f}")

from numpy import average


def transmission_delay(packet_length_bytes, rate_mbps):
    """
    Calculates the transmission delay of a packet.
    """
    rate_mbps /= 8 # convert to bytes per second
    rate_bps = rate_mbps * 1000000 # convert to bytes per second
    return packet_length_bytes / rate_bps

def total_time(cable_length_km, packet_length_b):
    """
    Calculates the total time it takes to transmit a packet.
    """
    speed = 200000 # km/s
    data_rate = 10000 # Mbps
    packet_length_b /= 8 # convert to bytes
    time = (cable_length_km / speed) + transmission_delay(packet_length_b, data_rate)
    return time * 1000 # convert to ms

# print(f"{total_time(10000, 8000):.4f}")

def queueing_delay(rate_bps, num_packets, packet_length_b):
    """
    Calculates the queueing delay of a packet.
    """
    return (num_packets * packet_length_b) / rate_bps

def average_trials(p_loss):
    """
    Calculates the average number of trials for a packet to be transmitted.
    """
    return 1 / (1 - p_loss)

def per_from_ber(bit_error_prob, packet_len_b):
    """
    Calculates the PER from a bit error probability.
    """
    return 1 - (1 - bit_error_prob) ** (packet_len_b)

def avg_trials_from_ber(bit_error_probability, packet_length_b):
    """
    Calculates the average number of trials for a packet to be transmitted.
    """
    return average_trials(per_from_ber(bit_error_probability, packet_length_b))

print(avg_trials_from_ber(0.001, 2000))