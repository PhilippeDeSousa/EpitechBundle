#! /usr/bin/env python3
# Python UDP Listener, listening on localhost 1025, change address 
# to listen on other ip/port combos. 

import socket
import sys
import re

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind(('127.0.0.1', int(sys.argv[1] if len(sys.argv) == 2 else 1234)))
print("Sock: ", sock)

clients = []

while True:
    data, address = sock.recvfrom(65538)
    if address not in clients:
        clients.append(address)
        result = re.search("Username:(.+)", str(data))
        if (result):
            print(result.group(1))
        print(address)
    for client in clients:
        sock.sendto(data, client)
    print("Sent to everyone: ", data)
