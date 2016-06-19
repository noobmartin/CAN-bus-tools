#include "can/bus.hpp"
#include "can/trionic5/messages.hpp"
#include "adapters/lawicel-canusb.hpp"

int main(){
  canusb_devices::lawicel_canusb adapter;
  adapter.auto_setup();

  can::bus canbus;
  canbus.set_name(IFNAMSIZ, adapter.get_interface_name());

  struct timeval pump_rate;
  pump_rate.tv_sec = 1;
  pump_rate.tv_usec = 0;

  canbus.configure_cyclic_deaf_datapump(pump_rate);

  char data[8] = {0xC4,0x73,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
  
  struct can_frame cyclic_frame;
  cyclic_frame.can_id = 0x005;
  cyclic_frame.can_dlc = 8;
  memcpy(cyclic_frame.data, data, 8);

  can::frame_list_node fnode;
  fnode.this_frame = &cyclic_frame;
  fnode.next_frame_list_node = 0;

  canbus.configure_cyclic_datapump_frames(1, fnode);

  canbus.open_cyclic();
  canbus.start_pumping_cyclic_data();

  unsigned int incoming_frame_id;
  char receive_data[20];
  memset(receive_data, 0x0, 20);


  do{
  canbus.receive(19, receive_data, &incoming_frame_id);
  printf("I read the following from Trionic: %s\n", receive_data);
  }while(1);

  return 0;
}
