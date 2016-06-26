/*
 * Author: Alexander Rajula
 * E-mail: superrajula@gmail.com
 * Descrpition:
 *   Implementation file for the logger class.
 */

#include <string.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <unistd.h>
#include "logger.hpp"

namespace logging_services{

logger::logger(){
  prefix_length = 0;
  memset(prefix_string, 0x0, MAX_PREFIX_STRING_LENGTH);
  memset(log_string, 0x0, MAX_TOTAL_LOG_STRING_LENGTH);

  terminal_output_enabled = true;
  file_output_enabled     = false;
  network_output_enabled  = false;

  terminal_output_available = true;
  file_output_available     = false;
  network_output_available  = false;

  insert_timestamp          = false;
  insert_prefix             = false;

  file_output_descriptor    = NULL;
  network_output_descriptor = 0;
}/*logger::logger*/

logger::~logger(){

}/*logger::~logger*/

int logger::set_prefix(const char* string, unsigned int string_length){
  if(string_length > MAX_PREFIX_STRING_LENGTH){
    return 0;
  }/*if*/

  prefix_length = string_length;

  memset(prefix_string, 0x0, MAX_PREFIX_STRING_LENGTH);

  memcpy(prefix_string, string, prefix_length);

  return 1;
}/*logger::set_prefix*/

void logger::enable_data_destination(Data_Destination_Type  destination){
  switch(destination){
    case Data_Destination_Type::Terminal:
      terminal_output_enabled = true;
      break;
    case Data_Destination_Type::File:
      file_output_enabled     = true;
      break;
    case Data_Destination_Type::Network:
      network_output_enabled  = true;
      break;
    default:
      break;
  }/*switch*/
}/*logger::enable_data_destination*/

void logger::disable_data_destination(Data_Destination_Type destination){
  switch(destination){
    case Data_Destination_Type::Terminal:
      terminal_output_enabled = false;
      break;
    case Data_Destination_Type::File:
      file_output_enabled     = false;
      break;
    case Data_Destination_Type::Network:
      network_output_enabled  = false;
      break;
    default:
      break;
  }/*switch*/

}/*logger::disable_data_destination*/

void logger::enable_timestamping(void){
  insert_timestamp = true;
}/*logger::enable_timestamping*/

void logger::disable_timestamping(void){
  insert_timestamp = false;
}/*logger::disable_timestamping*/

int logger::set_file_output(const char* name){
  if(name == NULL){
    return 0;
  }/*if*/

  unset_file_output();

  file_output_descriptor = fopen(name, "a");

  if(file_output_descriptor == NULL){
    file_output_available = false;
    return 0;
  }/*if*/
  else{
    file_output_available = true;
  }/*else*/
 
  return 1;
}/*logger::set_file_output*/

int logger::unset_file_output(void){
  bool success = false;

  if(file_output_descriptor == NULL){
    return 0;
  }/*if*/

  file_output_available = false;

  if(fclose(file_output_descriptor) == EOF){
    perror("Tried to close file output but failed - continued usage is undefined.\n");
    success = false;
  }/*if*/
  else{
    success = true;
  }/*else*/

  file_output_descriptor = NULL;

  return success;
}/*logger::unset_file_output*/

int logger::set_network_output(unsigned int address, unsigned int port){
  bool success = false;
  struct sockaddr_in network_output_address;

  if( (port > 65535) || (port < 1) ){
    printf("Invalid port number 0x%x - refusing to continue.\n", port);
    return 0;
  }/*if*/

  unset_network_output();

  memset(&network_output_address, 0x0, sizeof(network_output_address));

  network_output_address.sin_family       = AF_INET;
  network_output_address.sin_port         = htons(port);
  network_output_address.sin_addr.s_addr  = htonl(address);

  network_output_descriptor = socket(network_output_address.sin_family, SOCK_DGRAM | SOCK_NONBLOCK, 0);
  if(network_output_descriptor == -1){
    perror("Could not create socket.\n");
    success = false;
  }/*if*/
  else{
    success = true;
  }/*else*/

  if(success){
    if(bind(network_output_descriptor, (sockaddr*)&network_output_address, sizeof(network_output_address)) == -1){
      perror("Could not bind socket to destination.\n");
      printf("Attempted destination IPv4 address 0x%x and destination port 0x%x.\n", address, port);
      printf("Performing roll-back and closing socket.\n");
      unset_network_output();

      success = false;
    }/*if*/
    else{
      network_output_available  = true;
      success                   = true;
    }/*else*/
  }/*if*/

  return success;
}/*logger::set_network_output*/

int logger::unset_network_output(void){
  bool success = false;

  if(close(network_output_descriptor) == -1){
    perror("Failed to close socket.\n");
    success = false;
  }/*if*/

  network_output_available = false;
  success = true;

  return success;
}/*logger::unset_network_output*/

void logger::log(const char* string){
  log(string, strlen(string));
}/*logger::log*/

void logger::log(const char* string, unsigned int length){
  if(string == NULL){
    return;
  }/*if*/

  memset(log_string, 0x0, MAX_TOTAL_LOG_STRING_LENGTH);

  unsigned int log_string_offset = 0;

  if(insert_timestamp){
    char  seconds[4]  = {'0','0','0','0'};
    char  useconds[5] = {'0','0','0','0','0'};

    struct timeval current_time;
    if(gettimeofday(&current_time, NULL) == -1){
      perror("Failed to retrieve current time - will insert zeroes instead.\n");
    }/*if*/
    else{
      
    }/*else*/

    memcpy(&log_string[log_string_offset], seconds, 4);
    log_string_offset += 4;
    log_string[log_string_offset] = '.';
    log_string_offset += 1;
    memcpy(&log_string[log_string_offset], useconds, 5);
    log_string_offset += 5;
    log_string[log_string_offset] = '|';
    log_string_offset += 1;
  }/*if*/

  /* @NOTE: This could be made cheaper since the prefix is typically not changed during runtime.
   *        As such, the prefix shouldn't actually *need* to be inserted in the log string each
   *        time.
   */
  if(insert_prefix){
    memcpy(&log_string[log_string_offset], prefix_string, prefix_length);
    log_string_offset += prefix_length;
    log_string[log_string_offset] = '|';
    log_string_offset += 1;
  }/*if*/

  log_string[log_string_offset] = '\0';

  if(terminal_output_enabled && terminal_output_available){
    puts(log_string);
  }/*if*/

  if(file_output_enabled && file_output_available){
    fwrite(log_string, 1, log_string_offset, file_output_descriptor);
  }/*if*/

  if(network_output_enabled && network_output_available){
    send(network_output_descriptor, log_string, log_string_offset, 0);
  }/*if*/

}/*logger::log*/

}