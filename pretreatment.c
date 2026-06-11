// 前処理プログラム
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

//  文字列から特定の文字列をすべて削除する関数
void remove_substring(char *str, const char *target) {
    size_t target_len = strlen(target);
    if (target_len == 0) return; // 対象が空文字なら何もしない

    char *p = str;
    // 行内にに対象の文字列が見つかる限り繰り返す
    while ((p = strstr(p, target)) != NULL) {
        // 見つかった位置（p）に、その直後の文字列を上書き（左にシフト）する
        // 終端コード '\0' も一緒に移動させるため、+1 しています
        memmove(p, p + target_len, strlen(p + target_len) + 1);
    }
}

int main(int argc, char *argv[])
{
    FILE *fp = fopen(argv[1], "r");
    
    if (fp == NULL)
    {
        puts("ファイルが開けないんだが？\n");
        return 1;
    }

    char line[MAX_LINE_LENGTH]; 
    int line_count = 0;

    char workname[MAX_LINE_LENGTH];
    char authorname[MAX_LINE_LENGTH];

    int tag_flag = 0;

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        // 作品名と著者名を記録
        if (line_count == 0)
        {
            printf("%s", line);

            line[strcspn(line, "\r\n")] = '\0';
            strcpy(workname, line);
        }
        else if (line_count == 1)
        {
            printf("%s", line);

            line[strcspn(line, "\r\n")] = '\0';
            strcpy(authorname, line);
        }
        else
        {
            if (strstr(line, "---"))
            {
                // --------内の文言は含めない
                if (tag_flag)
                {
                    tag_flag = 0;
                }
                else
                {
                    tag_flag = 1;
                }
            }
            // タグが付いてるのは含めない
            else if (strstr(line, "［＃") == NULL)
            {
                // 底本：〜以降は含めない
                if (strstr(line, "底本：")) break;

                if (!tag_flag)
                {
                    // 何も余計な文字列がなければ出力
                    printf("%s", line);
                }
            }
        }

        line_count++;
    }

    // remove_substring(argv[1], "works/");
    // printf("%s, 著者名：%s, 作品名：%s\n", argv[1], authorname, workname);

    fclose(fp);

    return 0;
}