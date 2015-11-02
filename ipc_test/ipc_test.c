#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#include "../data_distribution/distribution_areas.h"

void* ignition_angle_data = NULL;
void* engine_torque_data  = NULL;
void* engine_speed_data   = NULL;

void initialize_simulation();
void update_rpm();
void update_ignition_angle();
void update_torque();

int main(){

  srand(time(NULL));

  data_item_header  ignition_angle  = {"Ignition angle",  Real32_Type,  Degrees};
  data_item_header  engine_torque   = {"Engine torque",   Real32_Type,  Newton_Metres};
  data_item_header  engine_speed    = {"Engine speed",    UInt32_Type,   Revolutions_Per_Second};

  int ignition_angle_port = -1;
  int engine_torque_port  = -1;
  int engine_speed_port   = -1;

  unsigned int  ignition_angle_port_size = sizeof(data_item_header)+4;
  unsigned int  engine_torque_port_size  = sizeof(data_item_header)+4;
  unsigned int  engine_speed_port_size   = sizeof(data_item_header)+4;

  ignition_angle_data = setup_port(port_ignition_angle_btdc, &ignition_angle_port, ignition_angle_port_size);
  engine_torque_data  = setup_port(port_engine_torque, &engine_torque_port, engine_torque_port_size);
  engine_speed_data   = setup_port(port_engine_speed, &engine_speed_port, engine_speed_port_size);

  initialize_simulation();

  sleep(5);

  memcpy(ignition_angle_data, &ignition_angle, sizeof(data_item_header) );
  memcpy(engine_torque_data, &engine_torque, sizeof(data_item_header) );
  memcpy(engine_speed_data, &engine_speed, sizeof(data_item_header) );

  int i = 0;
  for(; i < 100; i++){
    update_rpm();
    update_ignition_angle();
    update_torque();
    sleep(1);
  }

  sleep(5);

  close_port(port_ignition_angle_btdc, ignition_angle_data, ignition_angle_port_size);
  close_port(port_engine_torque, engine_torque_data, engine_torque_port_size);
  close_port(port_engine_speed, engine_speed_data, engine_speed_port_size);
}

void initialize_simulation(){
  float ignition    = 10.0;
  float torque      = 10;
  unsigned int  rpm = 750;

  *( (float*) ignition_angle_data+sizeof(data_item_header)) = ignition;
  *( (float*) engine_torque_data+sizeof(data_item_header))  = torque;
  *( (unsigned int*) engine_speed_data+sizeof(data_item_header)) = rpm;
}

void update_rpm(){
  static int flip = 0;

  unsigned int* rpm = ( (unsigned int*) engine_speed_data+sizeof(data_item_header));

  int jitter = rand()%25;

  if(flip){
    jitter*=-1;
    flip = 0;
  }
  else{
    flip = 1;
  }

  *rpm += jitter;
}

void update_torque(){
  static int flip = 0;

  float* torque = ( (float*) engine_torque_data+sizeof(data_item_header));

  int jitter = rand()%25;

  if(flip){
    jitter*=-1;
    flip = 0;
  }
  else{
    flip = 1;
  }

  *torque += jitter;

}

void update_ignition_angle(){
  static int flip = 1;

  float* ignition_angle = ( (float*) engine_torque_data+sizeof(data_item_header));

  int jitter = rand()%25;

  if(flip){
    jitter*=-1;
    flip = 0;
  }
  else{
    flip = 1;
  }

  *ignition_angle += jitter;
}
