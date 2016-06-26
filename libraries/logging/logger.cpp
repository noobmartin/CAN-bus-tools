/*
 * Author: Alexander Rajula
 * E-mail: superrajula@gmail.com
 * Descrpition:
 *   Implementation file for the logger class.
 */

#include "logger.hpp"

namespace logging_services{

logger::logger(){
  memset(prefix_string, 0x0, MAX_PREFIX_STRING_LENGTH);

  terminal_output_enabled = true;
  file_output_enabled     = false;
  network_output_enabled  = false;

  insert_timestamp  = false;
}/*logger::logger*/

logger::~logger(){

}/*logger::~logger*/

int logger::set_prefix(const char* string, unsigned int string_length){
  if(string_length > MAX_PREFIX_STRING_LENGTH){
    return 0;
  }/*if*/

  memset(prefix_string, 0x0, MAX_PREFIX_STRING_LENGTH);

  memcpy(prefix_string, string, string_length);

  return 1;
}/*logger::set_prefix*/

void logger::enable_data_destination(Data_Destination_Type  destination){
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
}/*logger::enable_data_destination*/

void logger::disable_data_destination(Data_Destination_Type destination){
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

}/*logger::disable_data_destination*/

}
