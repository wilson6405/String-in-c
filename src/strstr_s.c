#include <safe_str_lib.h>

int main(void) {
    const char *string = "Bad PWD evt";
    char character1 = 'P';
    char character2 = 'B';

    if (strstr_s(string, strlen(string), character1, strlen(character1)))
}