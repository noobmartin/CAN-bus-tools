/*
 * Author: Alexander Rajula
 * E-mail: superrajula@gmail.com
 * Descrpition:
 *   Implementation file for the canbus class.
 */

#include "canbus.hpp"

namespace cannet{

canbus::canbus(){
  bus_socket = 0x0;
  memset(&ifr, 0x0, sizeof(ifr));
  memset(&addr, 0x0, sizeof(addr));
  memset(&send_frame, 0x0, sizeof(send_frame));
  memset(&read_frame, 0x0, sizeof(read_frame));
  memset(&receive_frame_filter, 0x0, sizeof(receive_frame_filter));
  memset(busname, 0x0, MAX_BUSNAME_SIZE);
  memset(&tx_buffer, 0x0, MAX_CYCLIC_TX_FRAMES*sizeof(can_frame)+sizeof(bcm_msg_head));
}

canbus::~canbus(){

}

int canbus::set_busname(const unsigned size, const char* given_busname){
  if( (given_busname == 0) || size < 1){
    perror("Cannot not set busname");
    return -1;
  }
  memcpy(busname, given_busname, size);
}

void canbus::set_receive_frame_filter(const unsigned int can_id, const unsigned int frame_mask){
  receive_frame_filter.can_id = can_id;
  receive_frame_filter.can_mask = frame_mask;
  setsockopt(bus_socket, SOL_CAN_RAW, CAN_RAW_FILTER, &receive_frame_filter, sizeof(receive_frame_filter));
}

void canbus::disable_listening(void){
  setsockopt(bus_socket, SOL_CAN_RAW, CAN_RAW_FILTER, NULL, 0);
}

int canbus::open_bus(void){
  if( (bus_socket = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0){
    perror("Could not open socket");
    return -1;
  }

  strcpy(ifr.ifr_name, busname);
  ioctl(bus_socket, SIOCGIFINDEX, &ifr);

  addr.can_ifindex = ifr.ifr_ifindex;
  addr.can_family = PF_CAN;

  if(bind(bus_socket, (struct sockaddr*)&addr, sizeof(addr)) < 0){
    perror("Could not bind socket");
    return -2;
  }
}

int canbus::open_cyclic_bus(void){
  bus_socket = socket(PF_CAN, SOCK_DGRAM, CAN_BCM);
  if( (bus_socket < 0)){
    perror("Could not open socket");
    return -1;
  }

  strcpy(ifr.ifr_name, busname);
  ioctl(bus_socket, SIOCGIFINDEX, &ifr);

  addr.can_family = AF_CAN;
  addr.can_ifindex = ifr.ifr_ifindex;

  if(connect(bus_socket, (struct sockaddr*)&addr, sizeof(addr)) < 0){
    perror("Could not connect socket");
    return -2;
  }
}

int canbus::close_bus(void){
  close(bus_socket);
}

int canbus::receive(const unsigned size, char* buf, unsigned int* can_id){
  int read_bytes = read(bus_socket, &read_frame, sizeof(read_frame));

  if(read_bytes < 0){
    perror("CAN bus read returned < 0");
    return -1;
  }
  else{
    *can_id = read_frame.can_id;
    memcpy(buf, read_frame.data, read_frame.can_dlc);
  }

  return read_frame.can_dlc;
}

int canbus::send(const unsigned int can_id, const unsigned size, const char* buf){
  if( (buf == 0) || (size < 1) || (size > 8) ){
    perror("Data is too large/small to send");
    return -1;
  }

  send_frame.can_id = can_id;
  memcpy(send_frame.data, buf, size);
  send_frame.can_dlc = size;

  int written_bytes = write(bus_socket, &send_frame, sizeof(send_frame));
  if( written_bytes < size ){
    perror("Could not write all bytes");
  }

  return written_bytes;

}

void canbus::configure_cyclic_deaf_datapump(struct timeval cyclic_rate){
  tx_buffer.cyclic_header.opcode = 0x0;
  tx_buffer.cyclic_header.opcode = TX_SETUP;
  
  tx_buffer.cyclic_header.flags = 0x0;
  tx_buffer.cyclic_header.flags = SETTIMER | STARTTIMER;

  tx_buffer.cyclic_header.count = 0x0;
  tx_buffer.cyclic_header.ival1.tv_sec = 0x0;
  tx_buffer.cyclic_header.ival1.tv_usec = 0x0;
  tx_buffer.cyclic_header.ival2 = cyclic_rate;
}

void canbus::configure_cyclic_datapump_frames(unsigned int frames, frame_list_node first_frame_list_node){
  /* 
   * Implicitly assume that all can_frame(s) have the same CAN ID, so we'll use that one!
   */
  tx_buffer.cyclic_header.can_id = first_frame_list_node.this_frame->can_id;  
  tx_buffer.cyclic_header.nframes = frames;

  frame_list_node* cur_frame_list_node = &first_frame_list_node;
  for(int i = 0; i < frames ; i++){
    memcpy(&tx_buffer.cyclic_frames[i], cur_frame_list_node->this_frame, sizeof(can_frame));
    cur_frame_list_node = cur_frame_list_node->next_frame_list_node;
  }
}

void canbus::start_pumping_cyclic_data(void){
  write(bus_socket, &tx_buffer, sizeof(bcm_msg_head) + tx_buffer.cyclic_header.nframes*sizeof(can_frame));
}

void canbus::stop_pumping_cyclic_data(void){
  struct bcm_msg_head stop_pumping_command;
  memset(&stop_pumping_command, 0x0, sizeof(bcm_msg_head));
  stop_pumping_command.opcode = TX_DELETE;
  stop_pumping_command.can_id = tx_buffer.cyclic_header.can_id;

  write(bus_socket, &stop_pumping_command, sizeof(bcm_msg_head));
}

}
