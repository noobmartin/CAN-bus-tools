/*
 * Author: Alexander Rajula
 * E-mail: superrajula@gmail.com
 * Description:
 *   This class is an abstraction layer hiding the fact that communication
 *   is performed by using regular POSIX sockets.
 *
 * Kudos to:
 * 1) https://www.kernel.org/doc/Documentation/networking/can.txt
 * 2) SocketCAN - The official CAN API of the Linux kernel
 *	Marc Kleine-Budde, Pengutronix
 */

#ifndef _canbus_hpp_
#define _canbus_hpp_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>

#include <linux/can.h>
#include <linux/can/raw.h>
#include <linux/can/bcm.h>

namespace cannet{

#define MAX_BUSNAME_SIZE 	256
#define MAX_CYCLIC_TX_FRAMES	256

struct frame_list_node{
  can_frame* this_frame;
  frame_list_node* next_frame_list_node;
};

struct cyclic_tx_buffer{
  struct bcm_msg_head cyclic_header;
  struct can_frame cyclic_frames[MAX_CYCLIC_TX_FRAMES];
};

class canbus{
  private:
    int bus_socket;

    /* 
     * These are structs which are used when the socket is used with no bells and whistles.
     * I.e - regular CAN frame transmission and reception.
     */
    struct can_frame send_frame;
    struct can_frame read_frame;
    struct can_filter receive_frame_filter;

    /*
     * This struct holds all data pertaining to the cyclic transmission of a set of CAN frames.
     */
    struct cyclic_tx_buffer tx_buffer;

    struct sockaddr_can addr;
    struct ifreq ifr;
    
    char busname[MAX_BUSNAME_SIZE];

  public:
    canbus();
    ~canbus();

    /* 
     * For the bind/connect operations to function, they will need a valid interface name.
     * This is the interface name which is output using the ifconfig command.
     */
    int set_busname(const unsigned size, const char* busname);

    /* 
     * If you're not interested in listening to all the gossip on the bus, you may set a
     * frame filter, containing both CAN ID and CAD payload filter.
     */
    void set_receive_frame_filter(const unsigned int can_id, const unsigned int frame_mask);

    /* 
     * Call this method if the socket will only be used to send frames.
     * This will speed up the kenrel processing somewhat.
     */
    void disable_listening(void);
    
    /*
     * This call should be used when having configured a standard RAW CAN socket.
     */
    int open_bus(void);

    /*
     * This call applies to both kinds of CAN sockets.
     */
    int close_bus(void);

    /*
     * These are operations which handle the reception and transmission of frames.
     * If any filters have been applied by using set_receive_frame_filter,
     * only frames which match this filter will be received.
     */
    int receive(const unsigned size, char* buf, unsigned int* can_id);
    int send(const unsigned int can_id, const unsigned size, const char* buf);
   	int send(const can_frame* frame);

    /*
     * When using the broadcast manager, and you simply want to configure a set of frames
     * being sent cyclically, without caring to listen for incoming frames, use this operation.
     */
    void configure_cyclic_deaf_datapump(struct timeval cyclic_rate);
    void configure_cyclic_datapump_frames(unsigned int frames, frame_list_node first_frame_list_node);

    /*
     * These calls should be used to start and stop the transmission of cyclic frames.
     */
    void start_pumping_cyclic_data(void);
    void stop_pumping_cyclic_data(void);

    /*
     * This sets up a socket which is connected to the interface name set with set_busname.
     */
    int open_cyclic_bus(void);

};

}

#endif
