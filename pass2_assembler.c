#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    FILE *f1, *f2, *f3, *f4;
    char s[100], lab[30], opcode[30], opa[30], opcode1[30], opa1[30];
    int locctr = 0, x;

    f1 = fopen("input.txt", "r");
    f2 = fopen("opcode.txt", "r");
    f3 = fopen("out1.txt", "w");
    f4 = fopen("sym1.txt", "w");

    if (!f1 || !f2 || !f3 || !f4) {
        printf("Error opening files.\n");
        return 1;
    }

    while (fscanf(f1, "%s%s%s", lab, opcode, opa) != EOF) {
        if (strcmp(opcode, "START") == 0) {
            fprintf(f3, "%s %s %s\n", lab, opcode, opa);
            locctr = atoi(opa);
            continue;
        }

        rewind(f2);
        x = 0;

        while (fscanf(f2, "%s %s", opcode1, opa1) != EOF) {
            if (strcmp(opcode, opcode1) == 0) {
                fprintf(f3, "%d %s %s %s\n", locctr, lab, opcode, opa);
                fprintf(f4, "%d %s\n", locctr, lab);
                locctr += 3;
                x = 1;
                break;
            }
        }

        if (x == 0) {
            if (strcmp(opcode, "RESW") == 0) {
                fprintf(f3, "%d %s %s %s\n", locctr, lab, opcode, opa);
                fprintf(f4, "%d %s\n", locctr, lab);
                locctr += 3 * atoi(opa);
            } else if (strcmp(opcode, "WORD") == 0) {
                fprintf(f3, "%d %s %s %s\n", locctr, lab, opcode, opa);
                fprintf(f4, "%d %s\n", locctr, lab);
                locctr += 3;
            } else if (strcmp(opcode, "BYTE") == 0) {
                fprintf(f3, "%d %s %s %s\n", locctr, lab, opcode, opa);
                fprintf(f4, "%d %s\n", locctr, lab);
                locctr += 1;
            } else if (strcmp(opcode, "RESB") == 0) {
                fprintf(f3, "%d %s %s %s\n", locctr, lab, opcode, opa);
                fprintf(f4, "%d %s\n", locctr, lab);
                locctr += atoi(opa);
            } else {
                // Unknown opcode
                fprintf(f3, "%d %s %s %s\n", locctr, lab, opcode, opa);
                fprintf(stderr, "Warning: Unknown opcode '%s'\n", opcode);
                locctr += 3;  // Default increment
            }
        }
    }

    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);

    return 0;
}
