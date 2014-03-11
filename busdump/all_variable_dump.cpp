#include "../cannetwork/canbus.hpp"
#include "../cannetwork/trionic5/messages.hpp"
#include "../adaptercode/lawicel-canusb.hpp"

int main(){
  unsigned int incoming_frame_id;
  char receive_data[20];
  memset(receive_data, 0x0, 20);

  canusb_devices::lawicel_canusb adapter;
  adapter.auto_setup();

  cannet::canbus canbus;
  canbus.set_busname(sizeof(adapter.interface_name), adapter.interface_name);

  canbus.open_bus();

  do{
		canbus.send(&trionic5net::VSS_status);
  	canbus.receive(19, receive_data, &incoming_frame_id);
  	printf("I read the following from Trionic: %s\n", receive_data);
  }while(1);

  return 0;
}
