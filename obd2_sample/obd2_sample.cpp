#include "../cannetwork/canbus.hpp"
#include "../cannetwork/trionic5/messages.hpp"
#include "../adaptercode/lawicel-canusb.hpp"
#include "../obd2/obd2pids.h"
#include "../obd2/obd2modes.h"
#include "../obd2/obd2can.h"

int main(){
  canusb_devices::lawicel_canusb adapter;
  adapter.auto_setup();

  cannet::canbus canbus;
  canbus.set_busname(sizeof(adapter.interface_name), adapter.interface_name);

  struct timeval pump_rate;
  pump_rate.tv_sec = 1;
  pump_rate.tv_usec = 0;

  canbus.configure_cyclic_deaf_datapump(pump_rate);

  char data[8] = {CAN_OBD2_QUERY_SAE_STANDARD_DATA_LENGTH,
									SHOW_CURRENT_DATA,
									ENGINE_COOLANT_TEMP,
									0x55,0x55,0x55,0x55,0x55};
  
  struct can_frame obd2_frame;
  obd2_frame.can_id = CAN_OBD2_QUERY_MESSAGE_ID_BROADCAST;
  obd2_frame.can_dlc = 8;
  memcpy(obd2_frame.data, data, 8);

  cannet::frame_list_node fnode;
  fnode.this_frame = &obd2_frame;
  fnode.next_frame_list_node = 0;

  canbus.configure_cyclic_datapump_frames(1, fnode);

  canbus.open_cyclic_bus();
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
