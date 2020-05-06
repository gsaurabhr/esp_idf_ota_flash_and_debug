#!/usr/bin/env python3

#  Copyright 2020 by Saurabh Gandhi


import socket
import datetime

UDP_IP = "0.0.0.0"
UDP_PORT = 1338

sock = socket.socket( socket.AF_INET, socket.SOCK_DGRAM )
sock.bind( (UDP_IP, UDP_PORT) )

print("+============================+")
print("|  ESP32 UDP Flashing Server  |")
print("+============================+")
print("")

while True:
	data, addr = sock.recvfrom(1024)
	print(datetime.datetime.now(), data.decode(), end='\n', flush=True)
	if data.decode() == 'Init':
		sock.sendto("Message from python!!!!!".encode(), addr)
