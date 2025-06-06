# C74 - Trivial Computation Engine (8bit Computer)

The C74 is a concept for a really simple real 8 bit computer. Real 8 bits because
both busses (data and address) are 8 bit.
I had the idea for this project while developing an emulator for this imaginary machine.

## Project Roadmap

- Creating the logic
- Building and testing the components (memory, alu, etc.) in Hardware one by one
- Building the whole system

_Another sideproject could be developing an Assembler and maybe a programming language_

## OP Codes

```
00000000 NOP
00000001 HLT
00000010 STD
00000011 LDD
00000100 STX
00000101 LDX
00000110 STY
00000111 LDY
00001000 LDA
00001001 ADD
00001010 SUB
00001011 AND
00001100 OR
00001101 XOR
00001110 NOT
00001111 JMP
00010000 IN
00010001 OUT
```

## Microinstructions

```
00000 HALT

PROGRAM COUNTER INSTRUCTIONS
00001 PC_EN
00010 PC_COUNT
00011 PC_JUMP

ALU INSTRUCTIONS
00100 ALU_EN
00101 ALU_CTRL0
00110 ALU_CTRL1
00111 ALU_CTRL2

MEMORY INSTRUCTIONS
01000 MEM_WRITE
01001 MEM_READ

REGISTER INSTRUCTIONS
01010 X_WRITE
01011 X_READ
01100 Y_WRITE
01101 Y_READ
01110 A_WRITE
01111 A_READ
10000 I_WRITE
10001 I_READ
10010 DATA_WRITE
10011 DATA_READ
10100 ADDR_WRITE
10101 ADDR_READ
10110 IN_WRITE
10111 IN_READ
11000 OUT_WRITE
11001 OUT_READ

CU INSTRUCTIONS
11010 STEP_RESET
```
