LIB_DIR=libraries
CPP=g++ -g -std=c++11 -I$(LIB_DIR) -lrt
CC=gcc -I$(LIB_DIR) -lrt
CFLAGS=-I
BIN=sample_programs/bin
SAMPLES=sample_programs

obd:
	$(CPP) -o $(BIN)/obd2 $(SAMPLES)/obd2_sample/obd2_sample.cpp $(LIB_DIR)/logging/logger.cpp $(LIB_DIR)/adapters/lawicel-canusb.cpp $(LIB_DIR)/can/bus.cpp $(LIB_DIR)/obd2/utils.c $(LIB_DIR)/obd2/unpack.c

sample:
	$(CPP) -o $(BIN)/sample $(SAMPLES)/busdump/main.cpp $(LIB_DIR)/adapters/lawicel-canusb.cpp $(LIB_DIR)/can/bus.cpp

dump_all:
	$(CPP) -o $(BIN)/dump_all $(SAMPLES)/busdump/all_variable_dump.cpp $(LIB_DIR)/adapters/lawicel-canusb.cpp $(LIB_DIR)/can/bus.cpp

symboltable:
	$(CC) -o $(BIN)/symbolextract $(SAMPLES)/tablebuilder/trionic5/symbolextract.c

ipc_test:
	$(CC) -o $(BIN)/ipc_master $(SAMPLES)/ipc_test/ipc_test.c $(LIB_DIR)/data_distribution/distribution_areas.c

dtc:
	$(CPP)	-o $(BIN)/dtc	$(SAMPLES)/diagnostic_trouble_codes/dtc.cpp $(LIB_DIR)/adapters/lawicel-canusb.cpp $(LIB_DIR)/can/bus.cpp $(LIB_DIR)/obd2/utils.c $(LIB_DIR)/obd2/unpack.c
