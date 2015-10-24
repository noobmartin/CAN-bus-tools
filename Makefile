CPP=g++ -g
CC=gcc
CFLAGS=-I
BIN=built

obd:
	$(CPP) -o $(BIN)/obd2 obd2_sample/obd2_sample.cpp adaptercode/lawicel-canusb.cpp cannetwork/canbus.cpp obd2/utils.c

sample:
	$(CPP) -o $(BIN)/sample busdump/main.cpp adaptercode/lawicel-canusb.cpp cannetwork/canbus.cpp

dump_all:
	$(CPP) -o $(BIN)/dump_all busdump/all_variable_dump.cpp adaptercode/lawicel-canusb.cpp cannetwork/canbus.cpp

symboltable:
	$(CC) -o $(BIN)/symbolextract tablebuilder/trionic5/symbolextract.c
