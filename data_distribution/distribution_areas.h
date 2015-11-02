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
  Newton_Metres
}data_unit;

typedef struct{
  char                name[DATA_ITEM_NAME_SIZE];
  data_encapsulation  encapsulation;
}data_item_header;

const char* ignition_angle_btdc = "/ignition_angle";

#endif
