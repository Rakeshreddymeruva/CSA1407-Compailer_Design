#include <stdio.h>
#include <string.h>

const char *input;
int pos = 0;

int parse_E();
int parse_T();
int parse_F();

int parse_F() {
    int saved_pos = pos;
    if (input[pos] == '(') {
        pos++;
        if (parse_E()) {
            if (input[pos] == ')') {
                pos++;
                return 1;
            }
        }
        pos = saved_pos;
    }
    
    if (input[pos] == 'i' && input[pos+1] == 'd') {
        pos += 2;
        return 1;
    }
    return 0;
}

int parse_T() {
    int saved_pos = pos;
    if (parse_F()) {
        while (1) {
            int inner_pos = pos;
            if (input[pos] == '*') {
                pos++;
                if (parse_F()) {
                    continue;
                } else {
                    pos = inner_pos;
                    break;
                }
            } else {
                break;
            }
        }
        return 1;
    }
    pos = saved_pos;
    return 0;
}

int parse_E() {
    int saved_pos = pos;
    if (parse_T()) {
        while (1) {
            int inner_pos = pos;
            if (input[pos] == '+') {
                pos++;
                if (parse_T()) {
                    continue;
                } else {
                    pos = inner_pos;
                    break;
                }
            } else {
                break;
            }
        }
        return 1;
    }
    pos = saved_pos;
    return 0;
}

int main() {
    input = "id+id*id";
    pos = 0;

    printf("Input Expression: %s\n", input);
    
    if (parse_E() && input[pos] == '\0') {
        printf("PEG Result: String Accepted (Matched completely via Ordered Choice)\n");
    } else {
        printf("PEG Result: String Rejected\n");
    }

    return 0;
}