#ifndef DISTRIBUTION_AREAS_H
#define DISTRIBUTION_AREAS_H

#define DATA_ITEM_NAME_SIZE 256

typedef enum{
  Real8_Type,
  Real16_Type,
  Real32_Type,
  Real64_Type,
  Int8_Type,
  Int16_Type,
  Int32_Type,
  Int64_Type,
  UInt8_Type,
  UInt16_Type,
  UInt32_Type,
  UInt64_Type
}data_encapsulation;

typedef enum{
  Metres,
  Seconds,
  Kilograms,
  Amperes,
  Kelvin,
  Mole,
  Candela,
  Radians,
  Hertz,
  Newton,
  Pascal,
  Joule,
  Watt,
  Coulomb,
  Volt,
  Farad,
  Ohm,
  Siemens,
  Weber,
  Tesla,
  Henry,
  Centigrade,
  Lumen,
  Lux,
  Becquerel,
  Gray,
  Sievert,
  Katal,
  Fraction,
  Metres_Per_Second,
  Newton_Metres,
  Revolutions_Per_Second
}data_unit;

typedef struct{
  char                name[DATA_ITEM_NAME_SIZE];
  data_encapsulation  encapsulation;
}data_item_header;

const char* port_ignition_angle_btdc                = "/ignition_angle";
const char* port_engine_torque                      = "/engine_torque";
const char* port_engine_speed                       = "/engine_speed";
const char* port_engine_power                       = "/engine_power";
const char* port_cylinder_head_coolant_temperature  = "/cylinder_head_coolant_temperature";
const char* port_intake_air_flow_rate               = "/intake_mass_air_flow_rate";
const char* port_intake_air_temperature             = "/intake_air_temperature";

#endif
