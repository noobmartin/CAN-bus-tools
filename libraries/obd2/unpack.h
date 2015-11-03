#ifndef UNPACK_OBD2_H
#define UNPACK_OBD2_H

#include "obd2can.h"

/* @NOTE: For information regarding units and ranges, see obd2pids.h */

bool is_obd2_response(unsigned int message_id);

void unpack_obd2_response(obd2_response* response);

int unpack_engine_coolant(char A);

unsigned int unpack_engine_rpm(char A, char B);

unsigned int unpack_intake_manifold_pressure(char A);

double unpack_mass_airflow_rate(char A, char B);

double unpack_throttle_position(char A);

int unpack_intake_air_temperature(char A);

double unpack_ethanol_fuel_percentage(char A);

double unpack_timing_advance(char A);

unsigned int unpack_vehicle_speed(char A);

#endif
