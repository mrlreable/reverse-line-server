#include <stdio.h>
#include <stdlib.h>

const long int lineSize = 1000;

void reverseLine(char line[]){
    char reversedLine[lineSize];
    int count, i = 0;
    while(line[count] != '\0'){
        count++;
    }

    for(i = 0; i < count; i++){
        reversedLine[i] = line[count - 1 - i];
    }
    reversedLine[i] = '\0';
    printf("%s", reversedLine);
}

int main()
{
    char line[lineSize];
    printf("Enter a line: ");
    fgets(line, lineSize, stdin);

    reverseLine(line);

    return 0;
}
