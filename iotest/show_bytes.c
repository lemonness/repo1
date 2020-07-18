#include <stdio.h>
#include <string.h>

typedef unsigned char *byte_point;

void show_bytes(byte_point start, int len)
{
    int i;
    for (i = 0; i < len; i++)
        printf("%x-", start[i]);
    printf("\n");
}

void show_int(int a)
{
    show_bytes((byte_point)&a, sizeof(int));
}
void show_float(float a)
{
    show_bytes((byte_point)&a, sizeof(float));
}
void show_pointer(void *a)
{
    show_bytes((byte_point)&a, sizeof(void *));
}

int main()
{
    int val = 0x87654321;
    byte_point valp = (byte_point)&val;
    show_bytes(valp, 1);
    show_bytes(valp, 2);
    show_bytes(valp, 3);

    const char *s = "abcdef";
    show_bytes((byte_point)s, strlen(s));
}
