#include "adaptercode/lawicel-canusb.hpp"
#include "cannetwork/canbus.hpp"
#include "obd2/obd2can.h"
#include "obd2/unpack.h"

#include <stdio.h>

cannet::canbus  canbus;

void initialize();
void harvest_can_frames();
void request_dtcs();
void look_for_dtc_response(unsigned int incoming_frame_id, char* data, unsigned int data_size);

void initialize(){
  canusb_devices::lawicel_canusb  adapter;
  adapter.auto_setup();
  canbus.set_busname(IFNAMSIZ, adapter.get_interface_name());
  canbus.open_bus();
}/*initialize*/

int main(){
  initialize();

  do{
    printf("Press enter to request DTC.\n");
    int c = getchar();
    request_dtcs();
    printf("Transmitted DTC request.\n");
    int i = 0;
    for(; i < 1000; i++){
      harvest_can_frames();
    }
  }while(1);
}/*main*/

void request_dtcs(){
  struct can_frame  obd2_dtc_request;
  obd2_dtc_request.can_id   = CAN_OBD2_QUERY_MESSAGE_ID_BROADCAST;
  obd2_dtc_request.can_dlc  = 8;

  obd2_request_dtc  dtc_request_data;

  memcpy(obd2_dtc_request.data, &dtc_request_data, obd2_dtc_request.can_dlc);

  canbus.send(&obd2_dtc_request);

}/*request_dtcs*/

void harvest_can_frames(){
  unsigned int  incoming_frame_id;
  int           incoming_data_size = -1;
  char          receive_data[20];

  memset(receive_data, 0, 20);
  incoming_data_size = canbus.receive(20, receive_data, &incoming_frame_id);

  if(incoming_data_size > 0){
    look_for_dtc_response(incoming_frame_id, receive_data, incoming_data_size);
  }/*if*/

}/*harvest_can_frames*/

void look_for_dtc_response(unsigned int incoming_frame_id, char* data, unsigned int data_size){
  if(is_obd2_response(incoming_frame_id)){
    unpack_obd2_response( (obd2_response*) data);
  }/*if*/
  else{
    return;
  }/*else*/
}/*look_for_dtc_response*/
