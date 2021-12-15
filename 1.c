#include <stdio.h>

typedef unsigned long long int uint64;

int wrap_index(int index)
{
    return (index + 3) % 3;
}

int main(int argc, char** argv)
{
    uint64 depths[3] = { 0, 0, 0};
    int startIndex = 0;
    uint64 increasedCount = 0;
    int runsCount = 0;
    while (1)
    {
        runsCount++;
        uint64 newDepth;
        int result = scanf_s("%llu", &newDepth);
        if (result != 1)
        {
            break;
        }
        const uint64 lastDepth = depths[0] + depths[1] + depths[2];
        const uint64 depth = depths[wrap_index(startIndex + 1)] + depths[wrap_index(startIndex + 2)] + newDepth;
        depths[wrap_index(startIndex)] = newDepth;
        startIndex = wrap_index(startIndex + 1);
        if (depth > lastDepth && runsCount >= 3)
        {
            ++increasedCount;
        }
    }
    printf_s("%llu", increasedCount - 1);
    return 0;
}
