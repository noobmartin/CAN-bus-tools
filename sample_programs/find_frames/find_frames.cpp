/*
 * Author:      Alexander Rajula
 * Description: This simple program simply opens the CAN bus for sniffing to determine unique CAN frame IDs.
 *              The program may be useful if you're unsure which action triggers which CAN frame.
 */

#include "can/bus.hpp"
#include "adapters/lawicel-canusb.hpp"
#include "logging/logger.hpp"

int setup_bus(can::bus* bus);
int do_stuff(can::bus* bus, logging_services::logger*);
void parse_frame(unsigned int can_frame, char* buffer, logging_services::logger*);

int main(){
  canusb_devices::lawicel_canusb  adapter;
  can::bus                        bus;
  logging_services::logger        log;

  log.set_prefix("Frame scan", 10);
  log.set_file_output("find_frames_results.txt");
  log.enable_timestamping();
  log.enable_prefix();
  log.enable_data_destination(logging_services::Data_Destination_Type::Terminal);
  log.enable_data_destination(logging_services::Data_Destination_Type::File);
  log.disable_data_destination(logging_services::Data_Destination_Type::Network);

  if(adapter.auto_setup()){
    log.log("Successfully set up adapter.");

    if(setup_bus(&bus)){
      log.log("Successfully set up bus.");
      
      while(do_stuff(&bus, &log)){

      }/*while*/
    }/*if*/
    else{
      log.log("Failed to set up bus.");

    }/*else*/

  }/*if*/
  else{
    log.log("Failed to setup adapter.");

  }/*else*/

}/*main*/

int setup_bus(can::bus* bus){
  return bus->open_all();
}/*setup_bus*/

int do_stuff(can::bus* bus, logging_services::logger* log){
  char          buffer[128];
  unsigned int  can_id;
  int           success;

  success = bus->receive(128, buffer, &can_id); 

  if(success == -1){
    return 0;
  }/*if*/
  else{
    parse_frame(can_id, buffer, log);
    return 1;
  }/*else*/

}/*do_stuff*/

void parse_frame(unsigned int can_frame_id, char* buffer, logging_services::logger* log){
  /* @TODO: Parse through a list of can_frame IDs.
   *        If can_frame_id is not in the list, something interesting has happened!
   */

  bool new_frame = false;

  if(new_frame){
    log->log("Received new CAN frame type!");
  }/*if*/

  return;
}/*parse_frame*/
