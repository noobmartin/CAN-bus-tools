#include "../cannetwork/canbus.hpp"
#include "../cannetwork/trionic5/messages.hpp"
#include "../adaptercode/lawicel-canusb.hpp"
#include "../obd2/obd2pids.h"
#include "../obd2/obd2modes.h"
#include "../obd2/obd2can.h"
#include "../cannetwork/utils.h"

void unpack_data(unsigned int message_id, char* data, unsigned int data_size);
void unpack_obd2_response(obd2_response* response);
void unpack_engine_coolant(char A);

int main(){
  canusb_devices::lawicel_canusb adapter;
  adapter.auto_setup();
  cannet::canbus canbus;
  canbus.set_busname(sizeof(adapter.interface_name), adapter.interface_name);

  struct timeval pump_rate;
  pump_rate.tv_sec = 1;
  pump_rate.tv_usec = 0;

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

	canbus.open_bus();

	canbus.send(&obd2_frame);

  unsigned int incoming_frame_id;
  char receive_data[20];
  memset(receive_data, 0x0, 20);

  do{
		canbus.send(&obd2_frame);
  	unsigned int data_size = canbus.receive(19, receive_data, &incoming_frame_id);

		unpack_data(incoming_frame_id, receive_data, data_size);
		

		incoming_frame_id = extract_message_id(incoming_frame_id);
		printf("Rx - ID: %u (0x%x) Size: %u	Msg: %s\n", incoming_frame_id&CAN_ERR_MASK, incoming_frame_id, data_size, receive_data);

  }while(1);

  return 0;
}

void unpack_data(unsigned int message_id, char* data, unsigned int data_size){
	if( (message_id <= CAN_OBD2_RESPONSE_MESSAGE_ID_HIGH) &&
			(message_id >= CAN_OBD2_RESPONSE_MESSAGE_ID_LOW))
	{
		printf("Found OBD-II response!\n");
		unpack_obd2_response( (obd2_response*) data);
	}/*if*/
}/*unpack_data*/

void unpack_obd2_response(obd2_response* response){
	switch(response->pid){
		case ENGINE_COOLANT_TEMP:
			unpack_engine_coolant(response->A);
			break;
		default:
			break;
	}
}/*unpack_obd2_response*/

void unpack_engine_coolant(char A){
	printf("Engine coolant: %i Celsius\n", A-40);
}/*unpack_engine_coolant*/
