CPP=g++
CC=gcc
CFLAGS=-I

sample:
	$(CPP) -o sample busdump/main.cpp adaptercode/lawicel-canusb.cpp cannetwork/canbus.cpp

dump_all:
	$(CPP) -o dump_all busdump/all_variable_dump.cpp adaptercode/lawicel-canusb.cpp cannetwork/canbus.cpp

symboltable:
	$(CC) -o symbolextract tablebuilder/trionic5/symbolextract.c
