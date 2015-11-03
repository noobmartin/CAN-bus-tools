LIB_DIR=libraries
CPP=g++ -g -std=c++11 -I$(LIB_DIR)
CC=gcc
CFLAGS=-I
BIN=sample_programs/bin
SAMPLES=sample_programs

obd:
	$(CPP) -o $(BIN)/obd2 $(SAMPLES)/obd2_sample/obd2_sample.cpp $(LIB_DIR)/adaptercode/lawicel-canusb.cpp $(LIB_DIR)/cannetwork/canbus.cpp $(LIB_DIR)/obd2/utils.c $(LIB_DIR)/obd2/unpack.c

sample:
	$(CPP) -o $(BIN)/sample $(SAMPLES)/busdump/main.cpp $(LIB_DIR)/adaptercode/lawicel-canusb.cpp $(LIB_DIR)/cannetwork/canbus.cpp

dump_all:
	$(CPP) -o $(BIN)/dump_all $(SAMPLES)/busdump/all_variable_dump.cpp $(LIB_DIR)/adaptercode/lawicel-canusb.cpp $(LIB_DIR)/cannetwork/canbus.cpp

symboltable:
	$(CC) -o $(BIN)/symbolextract $(SAMPLES)/tablebuilder/trionic5/symbolextract.c
