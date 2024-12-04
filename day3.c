#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUM_INSTRUCTIONS (4096U)

typedef enum {
	STATE_D,
	STATE_O,
	STATE_N,
	STATE_APOSTROPHE,
	STATE_T,

	STATE_OPEN_PAREN_DO,
	STATE_OPEN_PAREN_DONT,
	STATE_CLOSE_PAREN_DO,
	STATE_CLOSE_PAREN_DONT,

	STATE_START,
	STATE_U,
	STATE_L,
	STATE_OPEN_PAREN,
	STATE_FIRST_NUM,
	STATE_SECOND_NUM,
	STATE_CLOSE_PAREN,
} State;

typedef struct {
	int n1;
	int n2;
} MulInstruction;

int main(void) {
	FILE *input = fopen("day3_input.txt", "r");
	if (input == NULL) {
		fprintf(stderr, "Could not open input file\n");
		return 1;
	}

	size_t instruction_idx = 0;
	MulInstruction instructions[MAX_NUM_INSTRUCTIONS];
	State state = STATE_START;

	// Max size of number is three digits
	int num_str_index = 0;
	char num_str[3];

    int n1;
    int n2;
    bool enabled = true;

	for (int next = fgetc(input); next != EOF; next = fgetc(input)) {
		char c = (char)next;

		switch (state) {
			case STATE_D:
				if (c == 'o') {
                    state = STATE_O;
				} else {
                    state = STATE_START;
                }
				break;
			case STATE_O:
				if (c == '(') {
                    state = STATE_OPEN_PAREN_DO;
				} else if (c == 'n') {
                    state = STATE_N;
                } else {
                    state = STATE_START;
                }
				break;
			case STATE_N:
				if (c == '\'') {
                    state = STATE_APOSTROPHE;
				} else {
                    state = STATE_START;
                }
				break;
			case STATE_APOSTROPHE:
				if (c == 't') {
                    state = STATE_T;
				} else {
                    state = STATE_START;
                }
				break;
			case STATE_T:
				if (c == '(') {
                    state = STATE_OPEN_PAREN_DONT;
				} else {
                    state = STATE_START;
                }
				break;

			case STATE_OPEN_PAREN_DO:
				if (c == ')') {
                    printf("Enabled!\n");
                    enabled = true;
                }
                state = STATE_START;
				break;

			case STATE_OPEN_PAREN_DONT:
                if (c == ')') {
                    printf("Disabled!\n");
                    enabled = false;
                }
                state = STATE_START;
				break;

			case STATE_START:
				if (enabled && c == 'm') {
					state = STATE_U;
				} else if (c == 'd') {
					state = STATE_D;
				} else {
					state = STATE_START;
				}
				break;
			case STATE_U:
				if (c == 'u') {
					state = STATE_L;
				} else {
					state = STATE_START;
				}
				break;
			case STATE_L:
				if (c == 'l') {
					state = STATE_OPEN_PAREN;
				} else {
					state = STATE_START;
				}
				break;
            case STATE_OPEN_PAREN:
				if (c == '(') {
					state = STATE_FIRST_NUM;
				} else {
					state = STATE_START;
				}
				break;
			case STATE_FIRST_NUM:
				if (c == ',') {
					n1 = atoi(num_str);
					memset(num_str, '\0', 3);
					num_str_index = 0;
					state = STATE_SECOND_NUM;
				} else if (isdigit(c)) {
					num_str[num_str_index++] = c;
				} else {
					memset(num_str, '\0', 3);
					num_str_index = 0;
					state = STATE_START;
				}
				break;
			case STATE_SECOND_NUM:
				if (c == ')') {
					n2 = atoi(num_str);
                    instructions[instruction_idx].n1 = n1;
                    instructions[instruction_idx].n2 = n2;
                    printf("Found instruction with args %d, %d\n", n1, n2);
                    instruction_idx++;
					memset(num_str, '\0', 3);
					num_str_index = 0;
					state = STATE_START;
				} else if (isdigit(c)) {
					num_str[num_str_index++] = c;
				} else {
					memset(num_str, '\0', 3);
					num_str_index = 0;
					state = STATE_START;
				}
				break;
		}
	}

    size_t total_sum = 0;
    for (size_t i = 0; i < instruction_idx; i++) {
        printf("Adding %d * %d to total sum\n", instructions[i].n1, instructions[i].n2);
        total_sum += instructions[i].n1 * instructions[i].n2; 
    }

    printf("Total Sum: %ld\n", total_sum);

    return 0;
}
