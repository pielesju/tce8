#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct {
    char instruction[8];
    unsigned char opcode;
    int param;
} Instruction;

Instruction instructions[] = {
    {"NOP",  0x00, -1},
    {"HLT",  0x01, -1},
    {"STD",  0x02,  0},
    {"LDD",  0x03,  0},
    {"STX",  0x04, -1},
    {"LDX",  0x05, -1},
    {"STY",  0x06, -1},
    {"LDY",  0x07, -1},
    {"LDA",  0x08, -1},
    {"ADD",  0x09, -1},
    {"SUB",  0x0A, -1},
    {"AND",  0x0B, -1},
    {"OR",   0x0C, -1},
    {"XOR",  0x0D, -1},
    {"NOT",  0x0E, -1},
    {"JMP",  0x0F,  0},
    {"JMPZ", 0x10,  0},
    {"JMPN", 0x11,  0},
    {"IN",   0x12, -1},
    {"OUT",  0x13, -1},
};

#define NUM_INSTRUCTIONS (sizeof(instructions) / sizeof(instructions[0]))

// Hilfsfunktion zur Überprüfung, ob ein String eine Zahl ist
int is_hex(const char *str) {
    if (*str == '\0') return 0; // Leerer String ist ungültig
    while (*str) {
        if (!isxdigit(*str)) return 0; // Nur Hex-Ziffern erlaubt
        str++;
    }
    return 1;
}

int main(int argc, char** argv) {
    if (argc != 3) return 1;

    const char *input_file_name = argv[1];
    const char *output_file_name = argv[2];

    FILE *input_file = fopen(input_file_name, "r");

    if (!input_file) return 1;

    FILE *output_file = fopen(output_file_name, "wb");

    if (!output_file) return 1;

    char line[256];  // Puffer zum Lesen einer Zeile
    char opcode[8];  // Puffer für den Opcode
    int param = -1;  // Standardwert für Parameter (falls keiner vorhanden ist)

    while (fgets(line, sizeof(line), input_file)) {
        // Entferne das Zeilenumbruchzeichen (falls vorhanden)
        line[strcspn(line, "\n")] = '\0'; 

        // Extrahiere den Opcode und optionalen Parameter
        int i = 0;
        while (line[i] != '\0' && line[i] != ' ' && line[i] != '\t') {
            opcode[i] = line[i];
            i++;
        }
        opcode[i] = '\0';  // Nullterminierung des Opcode

        // Überprüfe, ob ein Parameter vorhanden ist (nach dem Opcode)
        char *param_str = NULL;
        if (line[i] != '\0') {
            // Überspringe Leerzeichen oder Tabulator
            while (line[i] == ' ' || line[i] == '\t') {
                i++;
            }
            param_str = &line[i];  // Der Rest der Zeile könnte der Parameter sein
        }

        // Falls ein Parameter vorhanden ist und dieser ein Hex-String ist
        if (param_str != NULL && is_hex(param_str)) {
            param = strtol(param_str, NULL, 16);  // Hex-String in Zahl umwandeln
        }


        // Verarbeite den Opcode und Parameter
        for (int j = 0; j < NUM_INSTRUCTIONS; j++) {
            if (strcmp(opcode, instructions[j].instruction) == 0) {
		fwrite(&instructions[j].opcode, 1, 1, output_file);
		printf("%02x", instructions[j].opcode);
		if(instructions[j].param != -1) {
			unsigned char cparam = (unsigned char) param;
			fwrite(&cparam, 1, 1, output_file);
			printf("%02x", cparam);
		}
		printf("\n");
                break;
            }
        }
    }

    fclose(input_file);
    fclose(output_file);

    return 0;
}
