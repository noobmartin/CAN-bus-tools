#include "../cannetwork/canbus.hpp"
#include "../cannetwork/trionic5/messages.hpp"
#include "../adaptercode/lawicel-canusb.hpp"
#include "../obd2/obd2pids.h"
#include "../obd2/obd2modes.h"
#include "../obd2/obd2can.h"
#include "../obd2/unpack.h"

void unpack_data(unsigned int message_id, char* data, unsigned int data_size);

int main(){
  canusb_devices::lawicel_canusb adapter;
  adapter.auto_setup();
  cannet::canbus canbus;
  canbus.set_busname(sizeof(adapter.interface_name), adapter.interface_name);
	canbus.open_bus();

	obd2_request_current_data	engine_coolant_temp_request;
	obd2_request_current_data	rpm_request;

	engine_coolant_temp_request.pid	= ENGINE_COOLANT_TEMP;
	rpm_request.pid = ENGINE_RPM;

  struct can_frame obd2_frame;
  obd2_frame.can_id = CAN_OBD2_QUERY_MESSAGE_ID_BROADCAST;
  obd2_frame.can_dlc = 8;


  unsigned int incoming_frame_id;
  char receive_data[20];
  memset(receive_data, 0x0, 20);

  do{
		/* The right way to do this is to set up the request messages to be pumped out cyclically. */
		memcpy(obd2_frame.data, &rpm_request, 8);
		canbus.send(&obd2_frame);

  	unsigned int data_size = canbus.receive(19, receive_data, &incoming_frame_id);
		unpack_data(incoming_frame_id, receive_data, data_size);

		memcpy(obd2_frame.data, &engine_coolant_temp_request, 8);
		canbus.send(&obd2_frame);

  	data_size = canbus.receive(19, receive_data, &incoming_frame_id);
		unpack_data(incoming_frame_id, receive_data, data_size);

		//incoming_frame_id = extract_message_id(incoming_frame_id);
		//printf("Rx - ID: %u (0x%x) Size: %u	Msg: %s\n", incoming_frame_id&CAN_ERR_MASK, incoming_frame_id, data_size, receive_data);

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
