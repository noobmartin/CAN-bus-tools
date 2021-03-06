#ifndef OBD2_CAN_H
#define	OBD2_CAN_H

#include <linux/can.h>
#include "obd2modes.h"
#include "obd2pids.h"

/* @NOTE: A diagnostic reader requests data for a certain OBD-II mode and PID using CAN_OBD2_QUERY_MESSAGE_ID as identifier in the CAN Frame.
 * 				This CAN Frame identifier is used as a broadcast message.
 * 				The diagnostic reader may also transmit these requests directly to a specific unit on the bus, for which there may exist a total of eight units.
 * 				These unicast requests have been allocated CAN Frame IDs according to the information below.
 * 				If a request is transmitted using unicast, the device responding uses its singlecast message id + 8.
 */

#define CAN_OBD2_QUERY_MESSAGE_ID_BROADCAST		0x7df
#define CAN_OBD2_QUERY_MESSAGE_ID_LOW						0x7e0
#define CAN_OBD2_QUERY_MESSAGE_ID_HIGH					0x7e7
#define CAN_OBD2_RESPONSE_MESSAGE_ID_LOW				0x7e8
#define CAN_OBD2_RESPONSE_MESSAGE_ID_HIGH				0x7ef
#define CAN_OBD2_QUERY_SAE_STANDARD_DATA_LENGTH	0x2

typedef struct{
	char	num_extra_bytes = CAN_OBD2_QUERY_SAE_STANDARD_DATA_LENGTH;
	char	mode						= SHOW_CURRENT_DATA;
	char	pid;
	char	A								= 0x55;
	char	B								= 0x55;
	char	C								= 0x55;
	char	D								= 0x55;
	char	E								= 0x55;
}obd2_request_current_data;

typedef struct{
  char  num_extra_bytes = CAN_OBD2_QUERY_SAE_STANDARD_DATA_LENGTH;
  char  mode            = SHOW_STORED_DIAGNOSTIC_TROUBLE_CODES;
  char  pid             = REQUEST_TROUBLE_CODES;
  char  A               = 0x55;
  char  B               = 0x55;
  char  C               = 0x55;
  char  D               = 0x55;
  char  E               = 0x55;
}obd2_request_dtc;

typedef struct{
	char	num_extra_bytes;
	char	mode;
	char	pid;
	char	A;
	char	B;
	char	C;
	char	D;
	char	Extra;
}obd2_response;

#endif
