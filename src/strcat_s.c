#include <safe_str_lib.h>

int main(void) {
    char string_1[12] = {0x42, 0x61, 0x64, 0x20, '\0'};
    char string_2[] = {0x50, 0x57, 0x44, 0x20, '\0'};
    char string_3[] = {0x65, 0x76, 0x74, '\0'};
    char string[25] = {0};

    strcat_s(string_1, sizeof(string_1), string_2);
    strcat_s(string_1, sizeof(string_1), string_3);

    strncat_s(string, sizeof(string), string_1 + 1, 2);
    printf("%s\n", string_1);
    printf("%s\n", string);
}