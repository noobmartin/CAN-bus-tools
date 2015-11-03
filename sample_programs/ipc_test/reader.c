#include "data_distribution/distribution_areas.h"
#include <stdio.h>

int main(){
  int rpm_port = -1;
  unsigned int rpm_port_size = sizeof(data_item_header)+4;

  void* rpm_data = get_port(port_engine_speed, &rpm_port, rpm_port_size);

  if(rpm_data == 0){
    return 0;
  }/*if*/

  unsigned int* rpm = ((unsigned int*)rpm_data+sizeof(data_item_header));

  do{
    printf("RPM: %u\n", *rpm);
  }while(1);

  return 0;
}
