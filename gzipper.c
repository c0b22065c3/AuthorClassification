// gzipで圧縮するプログラム
// コンパイル：gcc -o gz gzipper.c -lz
// 実行：./gz ファイル名
#include <stdio.h>
#include <stdlib.h>
#include <zlib.h>

int main(int argc, char *argv[])
{
    FILE *in = fopen(argv[1], "rb");
    
    if (in == NULL)
    {
        puts("ファイルが開けないんだが？\n");
        return -1;
    }

    char dst_file[256] = "";

    sprintf(dst_file, "%s.gz", argv[1]);

    gzFile out = gzopen(dst_file, "wb9");

    if (out == NULL)
    {
        puts("圧縮先がないんだが？\n");
        return -1;
    }

    char buf[1024];
    int len;
    while ((len == fread(buf, 1, sizeof(buf), in)) > 0)
    {
        gzwrite(out, buf, len);
    }

    fclose(in);
    gzclose(out);

    return 0;
}