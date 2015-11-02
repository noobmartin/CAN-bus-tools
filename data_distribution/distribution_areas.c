#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

void* setup_port(const char* port_name, int* port_handle, unsigned int port_size){
  *port_handle = shm_open(port_name, O_RDWR | O_CREAT, S_IROTH | S_IRGRP | S_IRWXU);

  int result = ftruncate(*port_handle, port_size);

  void* port_area = mmap(0, port_size, PROT_READ|PROT_WRITE, MAP_SHARED, *port_handle, 0);

  return port_area;
}

void* get_port(const char* port_name, int* port_handle, unsigned int port_size){
  *port_handle = shm_open(port_name, O_RDONLY, 0);
  void* port_area = mmap(0, port_size, PROT_READ, MAP_SHARED, *port_handle, 0);

  return port_area;
}

int close_port(char* port_name, void* port_area, unsigned int port_size){
  int result = munmap(port_area, port_size);

  result = shm_unlink(port_name);

  return result;
}
