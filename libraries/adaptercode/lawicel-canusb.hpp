/*
 * Author: Alexander Rajula
 * E-mail: superrajula@gmail.com
 * Description:
 *
 * Kudos to:
 *  The guys and gals behind slcan_attach.c - a part of the set of userspace tools
 *  for serial line CAN interface driver SLCAN.
 */

#ifndef _lawicel_canusb_h
#define _lawicel_canusb_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <termios.h>
#include <netinet/in.h>
#include <linux/limits.h>

namespace canusb_devices{

#define MAX_TTY_TX_SIZE 256
#define LDISC_N_SLCAN 17

typedef enum can_speed{
	Kbit_10,
	Kbit_20,
	Kbit_50,
	Kbit_100,
	Kbit_125,
	Kbit_250,
	Kbit_500,
	Kbit_800,
	Mbit_1
} can_speed;

class lawicel_canusb{
  private:
    int ttyfd;
    char tty_tx_buf[MAX_TTY_TX_SIZE];
    char serial_device_path[PATH_MAX];

  public:
    lawicel_canusb();
    ~lawicel_canusb();
    
    char interface_name[IFNAMSIZ];

    /*
     * This function probes the system to find any attached LAWICEL CANUSB dongles.
     * Returns 0 on failure.
     */
    int find_lawicel_canusb_devices();

    /*
     * This is used to select one device from the device found by find_lawicel_canusb_devices
     * find_lawicel_canusb_devices()
     * Returns 0 on failure.
     */
    int set_lawicel_canusb_device(const char* tty);

    /*
     * This function sets the correct speed and TTY options to facilitate Trionic communication.
     * Returns 0 on failure.
     */
    int set_lawicel_canusb_speed(can_speed Speed);

    /* 
     * This function will transform the serial interface to an ethernet interface.
     * Returns 0 on failure.
     */
    int create_lawicel_canusb_interface();

    /*
     * This function will remove the previously created ethernet interface.
     * Returns 0 on failure.
     */
    int delete_lawicel_canusb_interface();

    /*
     * Once the LAWICEL CANUSB dongle has been found, the communication to Trionic must be opened.
     * Returns 0 on failure.
     */
    int open_lawicel_canusb();

    /*
     * Use this to close CAN communication to Trionic.
     * Returns 0 on failure.
     */
    int close_lawicel_canusb();

    void unset_lawicel_canusb_device();

    /*
     * Only use this if you are a lazy SOB.
     */
    void auto_setup();
};

}

#endif
