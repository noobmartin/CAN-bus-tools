#ifndef UNPACK_OBD2_H
#define UNPACK_OBD2_H

#include "obd2can.h"

void unpack_obd2_response(obd2_response* response);

int unpack_engine_coolant(char A);

unsigned int unpack_engine_rpm(char A, char B);

#endif
