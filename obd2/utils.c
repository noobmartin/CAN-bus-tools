#include "utils.h"
#include <linux/can.h>

unsigned int extract_message_id(unsigned int can_id){
	return (can_id & CAN_ERR_MASK);
}

bool is_rtr(unsigned int can_id){
	return (can_id & CAN_RTR_FLAG);
}

bool is_error(unsigned int can_id){
	return (can_id & CAN_ERR_FLAG);
}
