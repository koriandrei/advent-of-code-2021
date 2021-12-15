#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef unsigned char bool;

bool is_opening_brace(char symbol)
{
    return symbol == '(' || symbol == '[' || symbol == '{' || symbol == '<';
}

bool is_matching_closing_brace(char opening, char testSymbol)
{
    return opening == '(' && testSymbol == ')' 
        || opening == '[' && testSymbol == ']' 
        || opening == '{' && testSymbol == '}' 
        || opening == '<' && testSymbol == '>';
}

int get_error_symbol_cost(char symbol)
{
    switch (symbol)
    {
        case ')':
            return 3;
            case ']':
            return 57;
            case '}':
            return 1197;
            case '>':
            return 25137;
    }
    return -1;
}

int get_incomplete_symbol_cost(char symbol)
{
    switch (symbol)
    {
        case '(':
        return 1;
        case '[':
        return 2;
        case '{':
        return 3;
        case '<':
        return 4;
    }
    return -1;
}

typedef long long int int64;

int64 calculate_incomplete_line_score(const char* line, int lastSymbolIndex)
{
    int64 incompleteLineScore = 0;
    for (int incompleteSymbolIndex = lastSymbolIndex; incompleteSymbolIndex >= 0; --incompleteSymbolIndex)
    {
        incompleteLineScore *= 5;
        incompleteLineScore += get_incomplete_symbol_cost(line[incompleteSymbolIndex]);
    }
    return incompleteLineScore;
}

int comparison(const void* lhsPtr, const void* rhsPtr)
{
    int64 lhs = *(int64*)(lhsPtr);
    int64 rhs = *(int64*)(rhsPtr);
    if (lhs > rhs)
    {
        return 1;
    }
    if (lhs < rhs)
    {
        return -1;
    }
    return 0;
}

int main(int argc, char** argv)
{
    int sum = 0;
    int64 incompleteScores[1024] = {0, };
    int incompleteScoresCount = 0;

    while (1)
    {
        char line[1024];
        if (scanf("%s", line) != 1)
        {
            break;
        }
        if (strcmp(line, "exit") == 0)
        {
            break;
        }
        char parser[1024];
        int currentParserIndex = -1;
        
        char errorSymbol = '\0';
        for (int currentSymbolIndex = 0; currentSymbolIndex < 1024 && line[currentSymbolIndex] != 0; ++currentSymbolIndex)
        {
            char currentSymbol = line[currentSymbolIndex];
            bool opens = is_opening_brace(currentSymbol);
            if (opens)
            {
                parser[++currentParserIndex] = currentSymbol;
            }
            else if (currentParserIndex < 0)
            {
                // Ignore incomplete lines...
                break;
            }
            else if (is_matching_closing_brace(parser[currentParserIndex], currentSymbol))
            {
                --currentParserIndex;
                if (currentParserIndex < -1)
                {
                    // Ignore incomplete lines...
                    break;
                }
            }
            else
            {
                // Brace doesn't match last one - error!
                errorSymbol = currentSymbol;
                break;
            }
        }
        if (errorSymbol != '\0')
        {
            printf("Error symbol is %c\n", errorSymbol);
            sum += get_error_symbol_cost(errorSymbol);
        }
        else    
        if (currentParserIndex > 0)
        {
            // Line incomplete.
            int64 incompleteLineScore = calculate_incomplete_line_score(parser, currentParserIndex);;
            printf("Line score %lld\n", incompleteLineScore);
            incompleteScores[incompleteScoresCount++] = incompleteLineScore;
        }
        else
        {
            printf("No errors\n");
        }
    }

    printf("Total cost of errors %d\n", sum);
    qsort(incompleteScores, incompleteScoresCount, sizeof(incompleteScores[0]), &comparison);

    if (incompleteScoresCount > 0)
    {
        printf("Incomplete scores: %lld\n",incompleteScores[(incompleteScoresCount / 2)]);
    }
    return 0;
}
