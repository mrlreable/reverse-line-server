#include <stdio.h>
#include <stdlib.h>

int main()
{
    long int lineSize = 1000;
    char line[lineSize];
    char reversedLine[lineSize];
    printf("Enter a line: ");
    fgets(line, lineSize, stdin);

    int count, i = 0;
    while(line[count] != '\0'){
        count++;
    }

    for(i = 0; i < count; i++){
        reversedLine[i] = line[count - 1 - i];
    }
    reversedLine[i] = '\0';
    printf("%s", reversedLine);

    return 0;
}
