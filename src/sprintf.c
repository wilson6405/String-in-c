#include <stdio.h>
#include <stdlib.h>

int main(void) {
    unsigned char s[] = {0x42, 0x61, 0x64, 0x20, 0x50, 0x57, 0x44, 0x20, 0x65, 0x76, 0x74, '\0'};
    unsigned char *temp = NULL;

    temp = (unsigned char *)malloc(sizeof(s));
    sprintf(temp, "%s\n", s);
    printf("%s", temp);

    return 0;
}
