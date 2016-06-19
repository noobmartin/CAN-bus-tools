/*
 * Author: Alexander Rajula
 * E-mail: superrajula@gmail.com
 * Description:
 *   Implementation file for lawicel-canusb
 */

#include "lawicel-canusb.hpp"

namespace canusb_devices{

lawicel_canusb::lawicel_canusb(){
  ttyfd = 0x0;
  memset(tty_tx_buf, 0x0, MAX_TTY_TX_SIZE);
  memset(serial_device_path, 0x0, PATH_MAX);
}/*lawicel_canusb::lawicel_canusb*/

lawicel_canusb::~lawicel_canusb(){

}/*lawicel_canusb::~lawicel_canusb*/

int lawicel_canusb::find_lawicel_canusb_devices(){
  /*
   * I'm sorry, this is ugly as fuck.
   * Please forgive me.
   *
   * The correct solution would be to find all USB devices, sort them out based on the manufacturer,
   * and then find their serial device offspring, and provide that as a list for the program/user
   * to choose from.
   */

  system("find /dev/serial/by-id/|grep LAWICEL > file");

  FILE* fd = fopen("file", "r");
    fscanf(fd, "%s", serial_device_path);
    printf("Found serial device path %s\n", serial_device_path);
    fclose(fd);
    system("rm file");

    return 1;
}/*lawicel_canusb::find_lawicel_canusb_devices*/

int lawicel_canusb::set_lawicel_canusb_device(const char* tty){
  if((ttyfd = open(tty, O_WRONLY | O_NOCTTY)) < 0){
    perror(tty);
    return 0;
  }/*if*/

  return 1;
}/*lawicel_canusb::set_lawicel_canusb_device*/

void lawicel_canusb::unset_lawicel_canusb_device(){
  close(ttyfd);
}/*lawicel_canusb::unset_lawicel_canusb_device*/

int lawicel_canusb::set_lawicel_canusb_speed(can_speed Speed){
	switch(Speed){
		case Kbit_500:
		  sprintf(tty_tx_buf, "s4037\n");
			sprintf(tty_tx_buf, "S6\n");
		default:
		  sprintf(tty_tx_buf, "s4037\r");
			sprintf(tty_tx_buf, "S6\r");
			break;
	}/*switch*/

  if( write(ttyfd, tty_tx_buf, strlen(tty_tx_buf)) < 0 ){
    perror("Could not set canusb speed");
    return 0;
  }/*if*/

  printf("Canusb speed set\n");
  return 1;
}/*lawicel_canusb::set_lawicel_canusb_speed*/

int lawicel_canusb::create_lawicel_canusb_interface(){
  int ldisc = LDISC_N_SLCAN;
  if( ioctl(ttyfd, TIOCSETD, &ldisc) < 0){
    perror("Could not create interface");
    return 0;
  }/*if*/
  else{

    if( ioctl(ttyfd, SIOCGIFNAME, interface_name) < 0){
      perror("Could not retreive interface name");
      return 0;
    }/*if*/
    else{
      printf("Setting ethernet interface %s to UP\n", interface_name);
      int fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);

      if(fd == -1){
        perror("Could not open socket");
	      return 0;
      }/*if*/

      struct ifreq tifr;
      memcpy(tifr.ifr_name, interface_name, IFNAMSIZ);
      tifr.ifr_flags = IFF_UP|IFF_RUNNING|IFF_NOARP;

      if( ioctl(fd, SIOCSIFFLAGS, &tifr) == -1 ){
	      perror("Could not set socket options");
	      return 0;
      }/*if*/

      close(fd);

      return 1;
    }/*else*/

  }/*else*/

}/*lawicel_canusb::create_lawicel_canusb_interface*/

int lawicel_canusb::delete_lawicel_canusb_interface(){
  int ldisc = N_TTY;
  if( ioctl(ttyfd, TIOCSETD, &ldisc) < 0){
    perror("Could not delete interface");
    return 0;
  /*if*/
  }

  return 1;
}/*lawicel_canusb::delete_lawicel_canusb_interface*/

int lawicel_canusb::open_lawicel_canusb(){
  sprintf(tty_tx_buf, "O\r");
  if( write(ttyfd, tty_tx_buf, strlen(tty_tx_buf)) < 0){
    perror("Could not open CAN bus");
    return 0;
  }/*if*/

  return 1;
}/*lawicel_canusb::open_lawicel_canusb*/

int lawicel_canusb::close_lawicel_canusb(){
  sprintf(tty_tx_buf, "C\r");
  if( write(ttyfd, tty_tx_buf, strlen(tty_tx_buf)) < 0){
    perror("Could not close CAN bus");
    return 0;
  }/*if*/

  return 1;
}/*lawicel_canusb::close_lawicel_canusb*/

void lawicel_canusb::auto_setup(){
  find_lawicel_canusb_devices();
  set_lawicel_canusb_device(serial_device_path);
	close_lawicel_canusb();
  set_lawicel_canusb_speed(Kbit_500);
  open_lawicel_canusb();
  create_lawicel_canusb_interface();
}/*lawicel_canusb::auto_setup*/

const char* lawicel_canusb::get_interface_name(void){
  return interface_name;
}/*lawicel_canusb::get_interface_name*/

}/*canusb_devices*/
