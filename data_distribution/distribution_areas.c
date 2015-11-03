#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

void* setup_port(const char* port_name, int* port_handle, unsigned int port_size){
  *port_handle = shm_open(port_name, O_RDWR | O_CREAT, S_IROTH | S_IRGRP | S_IRWXU);

  if(*port_handle == -1){
    perror("setup_port - shm_open");
    printf("Port name: %s\n", port_name);
    return 0;
  }/*if*/

  int result = ftruncate(*port_handle, port_size);
  if(result == -1){
    perror("setup_port - ftruncate");
    return 0;
  }/*if*/

  void* port_area = mmap(0, port_size, PROT_READ|PROT_WRITE, MAP_SHARED, *port_handle, 0);

  if(port_area == MAP_FAILED){
    perror("setup_port - mmap");
    return 0;
  }/*if*/

  return port_area;
}/*setup_port*/

void* get_port(const char* port_name, int* port_handle, unsigned int port_size){
  *port_handle = shm_open(port_name, O_RDONLY, 0);
  if(*port_handle == -1){
    perror("get_port - shm_open");
    printf("Port name: %s\n", port_name);
    return 0;
  }/*if*/

  void* port_area = mmap(0, port_size, PROT_READ, MAP_SHARED, *port_handle, 0);
  if(port_area == MAP_FAILED){
    perror("get_port - mmap");
    return 0;
  }/*if*/

  return port_area;
}/*get_port*/

int close_port(char* port_name, void* port_area, unsigned int port_size){
  int result = munmap(port_area, port_size);
  if(result == -1){
    perror("close_port - munmap");
    return result;
  }/*if*/

  result = shm_unlink(port_name);
  if(result == -1){
    perror("close_port - shm_unlink");
    return result;
  }/*if*/

  return result;
}/*close_port*/
