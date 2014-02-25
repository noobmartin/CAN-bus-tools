CC=g++
CFLAGS=-I

sample:
	$(CC) -o sample busdump/main.cpp adaptercode/lawicel-canusb.cpp cannetwork/canbus.cpp
