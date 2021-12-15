#include <stdio.h>
#include <string.h>

typedef unsigned long long int uint64;
typedef signed long long int int64;

int main(int argc, char** argv)
{
    int64 depth = 0, horizontal = 0, aim = 0;
    while (1)
    {
        char command[25];
        int64 value = 0;
        
        int result = scanf_s("%24s %lld", command, 10, &value);
        // printf("Read %s %llu\n", command, value);
        if (result != 2 || result == EOF)
        {
            break;
        }

        if (strcmp(command, "forward") == 0)
        {
            horizontal += value;
            depth += aim * value;
            if (depth < 0)
            {
                depth = 0;
            }
        } else if (strcmp(command, "down") == 0)
        {
            aim += value;
        } else if (strcmp(command, "up") == 0)
        {
            aim -= value;
        }

        printf("New values: %lld %lld / aim %lld \n", depth, horizontal, aim);
    }
    printf_s("%llu", depth * horizontal);
    return 0;
}
