#include <stdio.h>
#include <string.h>

typedef unsigned long long int uint64;

int main(int argc, char** argv)
{
    uint64 depth = 0, horizontal = 0;
    while (1)
    {
        char command[25];
        uint64 value = 0;
        
        int result = scanf_s("%24s %llu", command, 10, &value);
        // printf("Read %s %llu\n", command, value);
        if (result != 2 || result == EOF)
        {
            break;
        }

        if (strcmp(command, "forward") == 0)
        {
            horizontal += value;
        } else if (strcmp(command, "down") == 0)
        {
            depth += value;
        } else if (strcmp(command, "up") == 0)
        {
            if (depth < value)
            {
                depth = 0;
            }
            else
            {
                depth -= value;
            }
        }

        printf("New values: %llu %lld\n", depth, horizontal);
    }
    printf_s("%llu", depth * horizontal);
    return 0;
}
