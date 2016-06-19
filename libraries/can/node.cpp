/*
 * Author: Alexander Rajula
 * E-mail: superrajula@gmail.com
 * Descrpition:
 *   Implementation file for the node class.
 */

#include "node.hpp"

namespace can{

node::node(){
  memset(name, 0x0, MAX_NODENAME_SIZE);
  memset(provided_frame_identifiers, 0x0, MAX_PROVIDED_FRAME_IDENTIFIERS*sizeof(unsigned int));
  number_of_provided_frame_identifiers = 0x0;
}/*node::node*/

node::~node(){

}/*node::~node*/

int node::set_name(const unsigned size, const char* given_name){
  if((given_name == 0) || size < 1){
    perror("Cannot set name");
    return -1;
  }/*if*/

  memcpy(name, given_name, size);
}/*node::set_name*/

int node::add_provided_frame(const unsigned int identifier){
  if(number_of_provided_frame_identifiers >= MAX_PROVIDED_FRAME_IDENTIFIERS){
    return -1;
  }/*if*/

  provided_frame_identifiers[number_of_provided_frame_identifiers] = identifier;

  number_of_provided_frame_identifiers += 1;

  return 0;

}/*node::add_provided_frame*/

int node::initialize(const char* canbus_name){
  canbus::set_name(canbus_name);
  canbus::open();

  for(int i = 0; i < number_of_provided_frame_identifiers; i++){
    canbus::add_receive_frame_filter(provided_frame_identifiers[i], CAN_SFF_MASK);
  }/*for*/

}/*node::initialize*/

int node::initialize_mute(void){
  canbus::open_all();

  for(int i = 0; i < number_of_provided_frame_identifiers; i++){
    canbus::add_receive_frame_filter(provided_frame_identifiers[i], CAN_SFF_MASK);
  }/*for*/

}/*node::initialize_mute*/

int get_provided_data(const unsigned size, char* data_buffer, unsigned int* identifier){
  return canbus::receive(size, data_buffer, identifier);
}/*node::get_provided_data*/

}
