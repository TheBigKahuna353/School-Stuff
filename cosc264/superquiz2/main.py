"""
Sender-side simulation of RDT 3.0;

Input packets are formatted
[type, seq_num, message]
0 message with seq_num to be sent;
1 ACK received, ACKing seq_num;
2 timeout event - resend last packet; 

Output packets are formatted
[status, seq_num]
-1 unexpected packet, -1 as seq_num;
0 message sent successfully - seq_num is the seq # of the message;
1 ACK processed - seq_num is the ACk seq_num;
2 re-sending finished - seq_num is the seq_num of the re-sent message;

Four states as described in the FSM
0 - wait for data 0;
1 - wait for ack 0;
2 - wait for data 1;
3 - wait for ack 1;

"""

def rdt_sender(event, state):        

    ### Your code goes here ###
    if state == 0:
        if event[0] == 0 and event[1] == 0:
            return 1, [0, event[1]]
        else:
            return 0, [-1, -1]
    elif state == 1:
        if event[0] == 1:
            if event[1] == 0:
                return 2, [1, event[1]]
            else:
                return 1, [-1, -1]
        elif event[0] == 2:
            return 1, [2, 0] 
        else:
            return 1, [-1, -1]
    elif state == 2:
        if event[0] == 0:
            return 3, [0, event[1]]
        else:
            return 2, [-1, -1]
    elif state == 3:
        if event[0] == 1:
            if event[1] == 1:
                return 0, [1, event[1]]
            else:
                return 3, [-1, -1]
        elif event[0] == 2:
            return 3, [2, 1]
        else:
            return 3, [-1, -1]




                

#Do not modify the following lines    
# def sender_test(event_list):    
#     state = 0
#     action_list = []    
    
#     for event in event_list:        
#         state, action = rdt_sender(event,state)
#         action_list.append(action)    
#     print(f'{action_list}')

"""
Receiver-side simulation of RDT 3.0

"""


def rdt_receiver(packet):
    ### Your code goes here ###
    if packet[0] in [0, 1]:
        return [0, packet[0]]
    else:
        return [-1, -1]
       


#Do NOT modify the following lines    
# def receiver_test(event_list):    
#     action_list = []    
    
#     for event in event_list:        
#         action = rdt_receiver(event)
#         action_list.append(action)    
        
#     print(f'{action_list}')  


"""
Sender-side simulation of GBN;

An event is formatted as
[type, seq_num, data]
0 data to send; no check on seq_num and data;
1 ACK received; acking seq_num;
2 timeout event; resend all outgoing unAck'ed events; no check on seq_num and data;

Output of function gbn_sender() is formatted as
[status, base, next_seq]
-1 unexpected event/window full
0 data sent successfully
1 ACK processed; 
2 resending finished; 

N - the window size
base - seq# of lower winder boundary (base)

"""

N = 4 # window size

def gbn_sender(event, base, next_seq):        
    if event[0] == 0: # Data to send; check whether the window is full
        if next_seq < base + N:
            return [0, base, next_seq + 1]
        else:
            return [-1, base, next_seq]
    elif event[0] == 1: # ACK received; check whether the ACK is in the window
        if base <= event[1] <= next_seq - 1:
            return [1, event[1] + 1, next_seq]
        else:
            return [-1, base, next_seq]
    elif event[0] == 2: # timeout event; resend all unAck'ed data
        return [2, base, next_seq]
    
 
                

#Do NOT modify the following code    
def sender_test(event_list):    
    base = 0
    next_seq = 0
    action_list = []    
    
    for event in event_list:        
        action = gbn_sender(event, base, next_seq)
        base = action[1]
        next_seq = action[2]
        action_list.append(action)    
        
    print(f'{action_list}')

 	
 	
"""
Receiver-side simulation of GBN

Input packets are formatted as
[seq_num, data]

Output packets are formatted as
[status, exp_num]
0 - an ACK is sent;
-1 - unexpected packet received; 

"""

def gbn_receiver(packet, exp_num):
    if packet[0] == exp_num:
        return [0, exp_num + 1]
    else:
        return [-1, exp_num]


    
       
#Do NOT modify the following code    
def receiver_test(packet_list):    
    action_list = []
    exp_num = 1
    
    for packet in packet_list:        
        action = gbn_receiver(packet, exp_num)
        exp_num = action[1]
        action_list.append(action)    
        
    print(f'{action_list}')  


a = 0xE32F
b = 0x2396
c = 0x4427
d = 0x99F3

print(hex(a + b + c + d))
print(hex(c + d))
print(hex(0x06c6))
print(hex(0x06c6 + c + d))
print(hex(0xFFFF - 0xE4E0))