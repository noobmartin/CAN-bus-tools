CPP=g++
CC=gcc
CFLAGS=-I

sample:
	$(CPP) -o sample busdump/main.cpp adaptercode/lawicel-canusb.cpp cannetwork/canbus.cpp

symboltable:
	$(CC) -o symbolextract tablebuilder/trionic5/symbolextract.c
