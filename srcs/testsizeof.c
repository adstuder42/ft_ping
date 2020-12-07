
#include <stdio.h>
int main(int argc, char**argv)
{
    printf("%d\n", (int)sizeof(argv[1])/8 -1);
    return (0);
}
