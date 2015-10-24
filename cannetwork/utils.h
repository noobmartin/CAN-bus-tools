#ifndef CAN_UTILS_H
#define CAN_UTILS_H

unsigned int extract_message_id(unsigned int can_id);
bool	is_rtr(unsigned int can_id);
bool	is_error(unsigned int can_id);

#endif
