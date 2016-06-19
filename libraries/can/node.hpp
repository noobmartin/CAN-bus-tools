/*
 * Author: Alexander Rajula
 * E-mail: superrajula@gmail.com
 * Description:
 *  This class represents a node connected to a CAN bus.
 *  Each node may be the originator of a number of CAN frame identifiers,
 *  also called arbitration IDs.
 *
 *  The list of frame identifiers is used to filter incoming traffic to only match
 *  the set of identifiers associated with this node.
 */

#ifndef _node_hpp_
#define _node_hpp_

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

#include "can/bus.hpp"

namespace can{

#define MAX_NODENAME_SIZE               256
#define MAX_PROVIDED_FRAME_IDENTIFIERS  256

class node{
  private:
    char          name[MAX_NODENAME_SIZE];
    unsigned int  provided_frame_identifiers[MAX_PROVIDED_FRAME_IDENTIFIERS];
    unsigned int  number_of_provided_frame_identifiers;

    can::bus      canbus;

  public:
    node();
    ~node();

    /*
     * Use this method if you want to associate this node with a
     * textual string name.
     */
    int set_name(const unsigned size, const char* name);

    /*
     * Use this method during initialization of the node.
     * If the node provides several frames with different identifiers,
     * call this method several times, in sequence, with the set of 
     * provided identifiers associated with this node.
     */
    int add_provided_frame(const unsigned int identifier);

    /*
     * Once the name, applicable filters etc. have been set up,
     * call this method to connect this node to the CAN bus.
     * This method has to be called before any data from the 
     * node may be retrieved.
     */
    int initialize(const char* canbus_name);

    /*
     * Performs the same function as initialize, but with one
     * important difference - the node won't be able to output
     * data on the bus.
     */
    int initialize_mute(void);

    /*
     * Use this method to fetch data from this node.
     * The number of bytes fetched is returned.
     */
    int get_provided_data(const unsigned size, char* data_buffer, unsigned int* identifier);
};

}

#endif
