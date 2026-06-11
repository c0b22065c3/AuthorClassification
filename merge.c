// テキストファイルの結合
// コンパイル：gcc -o merge merge.c
// 実行：./pr ファイル名 ファイル名
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

int main(int argc, char *argv[1])
{
    FILE *fp1 = fopen(argv[1], "r");
    FILE *fp2 = fopen(argv[2], "r");

    char line[MAX_LINE_LENGTH]; 

    if (fp1 == NULL || fp2 == NULL)
    {
        puts("ファイルが開けないんだが？\n");
        return 1;
    }

    while (fgets(line, sizeof(line), fp1) != NULL)
    {
        printf("%s", line);
    }
    
    while (fgets(line, sizeof(line), fp2) != NULL)
    {
        printf("%s", line);
    }

    fclose(fp1);
    fclose(fp2);

    return 0;
}