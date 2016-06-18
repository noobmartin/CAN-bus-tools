#include "cannetwork/canbus.hpp"
#include "cannetwork/trionic5/messages.hpp"
#include "adaptercode/lawicel-canusb.hpp"
#include "obd2/obd2pids.h"
#include "obd2/obd2modes.h"
#include "obd2/obd2can.h"
#include "obd2/unpack.h"

#include <time.h>

cannet::canbus canbus;

void initialize();

void receive_data();
void send_data();
void unpack_data(unsigned int message_id, char* data, unsigned int data_size);

int main(){
  initialize();

  do{
    receive_data();
    send_data();
  }while(1);

  return 0;
}/*main*/

void initialize(){
  canusb_devices::lawicel_canusb adapter;
  adapter.auto_setup();
  canbus.set_busname(IFNAMSIZ, adapter.get_interface_name());
	canbus.open_bus();
}/*initialize*/

void receive_data(){
  unsigned int incoming_frame_id;
  unsigned int incoming_data_size;
  char receive_data[20];

  const unsigned int receive_tries = 200;

  for(unsigned int i = 0; i < receive_tries; i++){
    memset(receive_data, 0x0, 20);
    incoming_data_size = canbus.receive(19, receive_data, &incoming_frame_id);
    unpack_data(incoming_frame_id, receive_data, incoming_data_size);
  }/*for*/

}/*receive_data*/

void send_data(){
  /* Set a message transmission rate of approximately 30Hz */
  const struct timespec transmission_period = {0, 33333333};

  struct timespec current_time;
  clock_gettime(CLOCK_REALTIME, &current_time);

  static struct timespec transmission_time = {0,0};

  bool transmit = false;

  /* This should also check tv_sec... */
  if(current_time.tv_nsec - transmission_time.tv_nsec >= transmission_period.tv_nsec){
    transmit = true;
  }/*if*/

  if(transmit){
    struct can_frame obd2_frame;
    obd2_frame.can_id = CAN_OBD2_QUERY_MESSAGE_ID_BROADCAST;
    obd2_frame.can_dlc = 8;

    obd2_request_current_data	engine_coolant_temp_request;
    obd2_request_current_data	rpm_request;

    engine_coolant_temp_request.pid	= ENGINE_COOLANT_TEMP;
    rpm_request.pid = ENGINE_RPM;

    memcpy(obd2_frame.data, &rpm_request, obd2_frame.can_dlc);
    canbus.send(&obd2_frame);

    memcpy(obd2_frame.data, &engine_coolant_temp_request, obd2_frame.can_dlc);
    canbus.send(&obd2_frame);

    transmission_time.tv_sec  = current_time.tv_sec;
    transmission_time.tv_nsec = current_time.tv_nsec;
  }/*if*/

}/*send_data*/

void unpack_data(unsigned int message_id, char* data, unsigned int data_size){
	if(is_obd2_response(message_id)){
		unpack_obd2_response( (obd2_response*) data);
	}/*if*/
}/*unpack_data*/

