/*
 * Author: Alexander Rajula
 * E-mail: superrajula@gmail.com
 * 
 * Kudos to: The T5Suite guys and gals
 *
 * Explanation:
 * The Trionic 5 flash binary contains a lookup table.
 * This lookup table points to where in the SRAM in Trionic a certain kind of variable resides in RAM.
 * The binary identifier in the lookup table which separates symbols is 0x0d0a (carriage return and newline).
 * The following two bytes tells us where we may find the data in SRAM, and the following two bytes gives us the length of the variable.
 * The following bytes is a null-terminated string giving a textual name of the data variable.
 *
 * struct{
 *   char 	separator[2];		// 0x0d0a
 *   char 	address[2];
 *   char 	length[2];
 *   char*	variable_name;
 * };
 *
 */

#include <stdio.h>
#include <string.h>

void find_separator(FILE* fp);
void get_address(FILE* fp, char* addr);
void get_length(FILE* fp, char* len);
void get_variable_name(FILE* fp, char* name);
void print_usage(void);

void write_code_header(FILE* fp);
void write_code_footer(FILE* fp);
void write_generic_sram_response(FILE* fp);

int main(int argc, char** argv){
	if(argc != 3){
		print_usage();
		return;
	}

	FILE* trionicbinary = fopen(argv[1], "rb");
	FILE* code_file			=	fopen(argv[2], "w");

  char name[256];
	char addr[4];
	char len[4];

	write_code_header(code_file);

	while(!feof(trionicbinary)){
		memset(name, 0, 256);
		memset(addr, 0, 4);
		memset(len, 0, 4);

  	find_separator(trionicbinary);
		get_address(trionicbinary, addr);
		get_length(trionicbinary, len);
		get_variable_name(trionicbinary, name);

		unsigned int start_addr_high = 0x0;
		unsigned int start_addr_low = 0x0;
		start_addr_high = addr[0] & 0x000000FF;
		start_addr_low = addr[1] & 0x000000FF;
		unsigned int start_addr = start_addr_low | (start_addr_high << 8);

		unsigned int len_one = 0x0;
		unsigned int len_two = 0x0;
		len_one = len[0] & 0x000000FF;
		len_two = len[1] & 0x000000FF;
		unsigned int len_t = len_two | (len_one << 8);

		unsigned int end_addr = start_addr+len_t;
		unsigned int end_addr_low = end_addr & 0x000000FF;
		unsigned int end_addr_high = (end_addr >> 8) & 0x000000FF;

		fprintf(code_file, "  struct can_frame %s = {0x005, 8, {0xC7, 0x%x, 0x%x, 0x%x, 0x%x, 0x00, 0x00, 0x00} };\n", name, end_addr_high, end_addr_low, start_addr_high, start_addr_low);

	}

	write_generic_sram_response(code_file);
	write_code_footer(code_file);
}

void write_code_header(FILE* fp){
	fprintf(fp, "#ifndef _messages_hpp_\n");
	fprintf(fp, "#define _messages_hpp_\n");
	fprintf(fp, "\n");
	fprintf(fp, "#include <linux/can.h>\n");
	fprintf(fp, "\n");
	fprintf(fp, "namespace trionic5net{\n");
}

void write_code_footer(FILE* fp){
	fprintf(fp, "}\n");
	fprintf(fp, "\n");
	fprintf(fp, "#endif\n");
}

void write_generic_sram_response(FILE* fp){
	fprintf(fp, "  struct can_frame generic_sram_response = {0x000, 8, {0xC6, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00} };\n");
}

void print_usage(void){
	printf("This tool extracts the symbol table in Trionic 5 and outputs code.\n");
	printf("Usage: symbolextract <trionic5_binary> <output_file>\n");
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

void get_address(FILE* fp, char* addr){
	fread(addr, 1, 2, fp);
}

void get_length(FILE* fp, char* len){
	fread(len, 1, 2, fp);
}

void get_variable_name(FILE* fp, char* name){
	char buf[1];

	unsigned int i;
	for(i = 0; i < 256; i++){
		fread(buf, 1, 1, fp);
		if(*buf != '\r'){
			if(*buf == '!'){
				*buf = '\0';
			}
			  memcpy(name+i, buf, 1);
		}
		else{
			// We found carriage return - reverse the stream by one byte.
			fseek(fp, -1, SEEK_CUR);
			break;
		}
	}
}
