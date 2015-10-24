#include "unpack.h"
#include "obd2pids.h"

#include <stdio.h>

void unpack_obd2_response(obd2_response* response){
	switch(response->pid){
		case ENGINE_COOLANT_TEMP:
			printf("Engine coolant: %i Celsius\n", unpack_engine_coolant(response->A));
			break;
		case ENGINE_RPM:
			printf("Engine rpm: %u\n" , unpack_engine_rpm(response->A, response->B));
		default:
			break;
	}
}/*unpack_obd2_response*/

int unpack_engine_coolant(char A){
	int engine_coolant_temperature_centigrade = A-40;
	return engine_coolant_temperature_centigrade;
}/*unpack_engine_coolant*/

unsigned int unpack_engine_rpm(char A, char B){
	unsigned int engine_rpm = (A*256 + B)/4;
	return engine_rpm;
}/*unpack_engine_rpm*/
