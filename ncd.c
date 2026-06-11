// テキストファイルの結合
// コンパイル：gcc -o ncd ncd.c
// 実行：./ncd 数値ファイル
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *fp;
    int num;

    int count = 0;

    int cxy = 0;
    int cx = 0;
    int cy = 0;

    int c_max = 0;
    int c_min = 0;

    float ncd = 0;

    // 読み込み専用("r")でファイルを開く
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("ファイルが開けないんだが？。\n");
        return 1;
    }

    // ファイルの終端まで数値を1つずつ読み込む
    while (fscanf(fp, "%d", &num) != EOF) {

        switch (count)
        {
            case 0:
                cxy = num;
                break;

            case 1:
                cx = num;
                break;

            case 2:
                cy = num;
                break;
        }

        count++;
    }
    
    // printf("Cx,y: %d Cx: %d Cy: %d\n", cxy, cx, cy);

    if (cx > cy)
    {
        c_max = cx;
        c_min = cy;
    }
    else
    {
        c_max = cy;
        c_min = cx;
    }

    ncd = ((float)cxy - (float)c_min) / (float)c_max;

    printf("%f\n", ncd);

    fclose(fp); // ファイルを閉じる
    return 0;
}