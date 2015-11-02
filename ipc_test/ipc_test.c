#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

#include "../data_distribution/distribution_areas.h"

int main(){

  data_item_header  ignition_angle  = {"Ignition angle", Real32_Type};
  data_item_header  engine_torque   = {"Engine torque", Real32_Type};
  data_item_header  engine_speed    = {"Engine speed", Int16_Type};

  int   ignition_angle_port = shm_open(port_ignition_angle_btdc, O_RDWR|O_CREAT, S_IROTH);
  ftruncate(ignition_angle_port, sizeof(data_item_header)+4);
  void* ignition_angle_data = mmap(0, sizeof(data_item_header)+4, PROT_READ|PROT_WRITE, MAP_SHARED, ignition_angle_port, 0);

  sleep(5);

  munmap(ignition_angle_data, sizeof(data_item_header)+4);

  shm_unlink(port_ignition_angle_btdc);
}
