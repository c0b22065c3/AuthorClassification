// ファイルのサイズを測る
// コンパイル：gcc -o size size.c
// 実行：./size ファイル名
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *fp = fopen(argv[1], "rb");
    fpos_t fsize;

    fseek(fp, 0, SEEK_END); // ファイルポインタを末尾へ移動

    fgetpos(fp, &fsize); // ファイルポインタの位置を取得

    printf("%lld\n", fsize);

    fclose(fp);

    return 0;
}