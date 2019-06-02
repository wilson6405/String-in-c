#include <safe_str_lib.h>

int main(void) {
    char x[] = {0x42, 0x61, 0x64, 0x20, 0x50, 0x57, 0x44, 0x20, 0x65, 0x76, 0x74, '\0'};
    char y[12] = {0};
    char z[6] = {0};
    int offset = 6;
    int ret = 0;

    printf("x: %s\n", x);
    ret = strcpy_s(y, sizeof(y), x);
    if (ret != 0)
    {
        printf("Return value: %d\n", ret);
        return ret;
    }

    printf("y: %s\n", y);
    ret = strncpy_s(y, sizeof(y), x + offset, 3);
    if (ret != 0)
    {
        printf("Return value: %d\n", ret);
        return ret;
    }

    printf("y: %s\n", y);
    ret = strncpy_s(z, sizeof(z), x, 5);
    if (ret != 0)
    {
        printf("Return value: %d\n", ret);
        return ret;
    }

    printf("z: %s\n", z);
    return ret;
}