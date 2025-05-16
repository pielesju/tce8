#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

uint32_t HALT       = 0b10000000000000000000000000000000;
uint32_t PC_EN      = 0b01000000000000000000000000000000;
uint32_t PC_COUNT   = 0b00100000000000000000000000000000;
uint32_t PC_JUMP    = 0b00010000000000000000000000000000;
uint32_t ALU_EN     = 0b00001000000000000000000000000000;
uint32_t ALU_CTRL0  = 0b00000100000000000000000000000000;
uint32_t ALU_CTRL1  = 0b00000010000000000000000000000000;
uint32_t ALU_CTRL2  = 0b00000001000000000000000000000000;
uint32_t MEM_WRITE  = 0b00000000100000000000000000000000;
uint32_t MEM_READ   = 0b00000000010000000000000000000000;
uint32_t X_WRITE    = 0b00000000001000000000000000000000;
uint32_t X_READ     = 0b00000000000100000000000000000000;
uint32_t Y_WRITE    = 0b00000000000010000000000000000000;
uint32_t Y_READ     = 0b00000000000001000000000000000000;
uint32_t A_WRITE    = 0b00000000000000100000000000000000;
uint32_t A_READ     = 0b00000000000000010000000000000000;
uint32_t I_WRITE    = 0b00000000000000001000000000000000;
uint32_t I_READ     = 0b00000000000000000100000000000000;
uint32_t DATA_WRITE = 0b00000000000000000010000000000000;
uint32_t DATA_READ  = 0b00000000000000000001000000000000;
uint32_t ADDR_WRITE = 0b00000000000000000000100000000000;
uint32_t ADDR_READ  = 0b00000000000000000000010000000000;
uint32_t IN_WRITE   = 0b00000000000000000000001000000000;
uint32_t IN_READ    = 0b00000000000000000000000100000000;
uint32_t OUT_WRITE  = 0b00000000000000000000000010000000;
uint32_t OUT_READ   = 0b00000000000000000000000001000000;
uint32_t STEP_RESET = 0b00000000000000000000000000100000;
uint32_t JUMP       = 0b00000000000000000000000000010000;

uint8_t NOP  = 0b00000000;
uint8_t HLT  = 0b00000001;
uint8_t STD  = 0b00000010;
uint8_t LDD  = 0b00000011;
uint8_t STX  = 0b00000100;
uint8_t LDX  = 0b00000101;
uint8_t STY  = 0b00000110;
uint8_t LDY  = 0b00000111;
uint8_t LDA  = 0b00001000;
uint8_t ADD  = 0b00001001;
uint8_t SUB  = 0b00001010;
uint8_t AND  = 0b00001011;
uint8_t OR   = 0b00001100;
uint8_t XOR  = 0b00001101;
uint8_t NOT  = 0b00001110;
uint8_t JMP  = 0b00001111;
uint8_t JMPZ = 0b00010000;
uint8_t IN   = 0b00010001;
uint8_t OUT  = 0b00010010;

uint32_t decode(uint8_t instruction, uint8_t time) {
    /* BASE STATES */
    if(time == 0) return PC_EN | MEM_READ | I_WRITE; 	    /* FETCH         */
    if(time == 1) return PC_COUNT | I_READ;                 /* DECODE        */

    if(time == 2 && instruction == NOP)
        return PC_COUNT | STEP_RESET;                       /* NOP           */
    if(time == 2 && instruction == HALT)
        return HALT | STEP_RESET;                           /* HALT          */
}

int main(int argc, char** argv) {

	FILE* file = fopen("microcode.txt", "w");
	if(!file) return 1;

	fprintf(file, "v3.0 hex words addressed\n");
	uint32_t col = 0;
	uint32_t row = 0;

	for(uint8_t i = 0; i < 256; i++) {
	    uint8_t value = i;

	    uint8_t in = value & 0b11111000;
	    uint8_t tm = value & 0b00000111;

	    if(col == 0) {
	        fprintf(file, "%02x:", row);
	    } else {
	    	fprintf(file, " %08x", decode(in, tm));
	    }
	    
	    col++;

	    if(col == 8) {
                fprintf(file, "\n");
		col = 0;
            }
	    
	    row++;
	}
	
	fclose(file);
}
