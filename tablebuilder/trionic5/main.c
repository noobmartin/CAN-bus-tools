/*
 * Author: Alexander Rajula
 * E-mail: superrajula@gmail.com
 * 
 * Kudos to: The T5Suite guys and gals
 *
 * Explanation:
 * The Trionic 5 flash binary contains a lookup table.
 * This lookup table points to where in the SRAM in Trionic a certain kind of variable resides.
 * The binary identifier in the lookup table which separates symbols is 0x0d0a.
 * The following two bytes tells us where we may find the data in SRAM, and the following two bytes gives us the length of the variable.
 * The following bytes is a null-terminated string giving a textual name of the data variable.
 *
 */

#include <stdio.h>
#include <string.h>

char separator[2] = {0x0d, 0x0a};

void find_separator(FILE* fp);

void print_address(FILE* fp, char* addr);
void print_length(FILE* fp, char* len);
void print_variable_name(FILE* fp, char* name);

int main(void){
	FILE* trionicbinary = fopen("t5.bin", "rb");
 
  char name[256];
	char addr[4];
	char len[4];
	
	while(!feof(trionicbinary)){
		memset(name, 0, 256);
		memset(addr, 0, 4);
		memset(len, 0, 4);

  	find_separator(trionicbinary);
		print_address(trionicbinary, addr);
		print_length(trionicbinary, len);
		print_variable_name(trionicbinary, name);

		unsigned int start_addr_one = 0x0;
		unsigned int start_addr_two = 0x0;
		start_addr_one = addr[0] & 0x000000FF;
		start_addr_two = addr[1] & 0x000000FF;

		unsigned int start_addr = start_addr_two | (start_addr_one << 8);
		
		unsigned int len_one = 0x0;
		unsigned int len_two = 0x0;
		len_one = len[0] & 0x000000FF;
		len_two = len[1] & 0x000000FF;
		unsigned int len_t = len_two | (len_one << 8);

		printf("struct can_frame %s = {0x000, 8, {0xC7, 0x00, 0x00, 0x%x, 0x%x, 0x00, 0x00, 0x00} }\n", name, start_addr, start_addr+len_t );
	}
}

void find_separator(FILE* fp){
  char buf[2];

	do{
		fread(buf, 1, 1, fp);
		if(buf[0] == 0x0d){
			fread(&buf[1], 1, 1, fp);
			if(buf[1] == 0x0a){
				// Carriage return and newline found.
				return;
			}
		}
	}while(!feof(fp));

}

void print_address(FILE* fp, char* addr){
	fread(addr, 1, 2, fp);
	printf("Addr: %#hhx %#hhx ", addr[0], addr[1]);
}

void print_length(FILE* fp, char* len){
	fread(len, 1, 2, fp);
	printf("Len: %#hhx %#hhx ", len[0], len[1]);
}

void print_variable_name(FILE* fp, char* name){
	char buf[1];

	unsigned int i;
	for(i = 0; i < 256; i++){
		fread(buf, 1, 1, fp);
		if(*buf != '\r'){
			memcpy(name+i, buf, 1);
		}
		else{
			printf("Name: %s\n", name);
			// We found carriage return - reverse the stream by one byte.
			fseek(fp, -1, SEEK_CUR);
			break;
		}
	}
}
