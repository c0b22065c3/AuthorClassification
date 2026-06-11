#include <stdio.h>
#include <time.h>

#include "ncd_list.h" // 計算したNCDの配列

#define N 21 // データ数 = 21

int main()
{
    clock_t start_clock, end_clock;

    /* 処理開始前のクロックを取得 */
    start_clock = clock();

    // 正解ラベル（0：萩原朔太郎、1：宮沢賢治、2：夏目漱石）
    int labels[N] = {
        0, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 1, 1,
        2, 2, 2, 2, 2, 2, 2
    };

    int correct_count = 0;

    char works[N][64] = {
        "蝶を夢む", "月に吠える", "青猫", "猫町", "追憶", "老年と人生", "ものごころ",
        "風の又三郎", "よだかの星", "銀河鉄道の夜", "オツベルと象", "やまなし", "疾中", "セロ弾きのゴーシュ",
        "夢十夜", "こころ", "吾輩は猫である", "坊ちゃん", "それから", "三四郎", "手紙"
    };

    char authors[3][64] = {"萩原朔太郎", "宮沢賢治", "夏目漱石"};

    printf("--- Leave-One-Out Cross Validation ---\n");

    // i番目のデータをテストデータとして1つ抜く
    for (int i = 0; i < N; i++)
    {
        int test_index = i;
        double min_dist = -1.0;
        int nearest_label = -1;

        // テストデータ以外で、最もNCDが近いデータを探す
        for (int j = 0; j < N; j++)
        {
            if (j == test_index)
            {
                continue; // 自分自身は除外
            }

            // すでに計算済みの行列からNCDを引っ張ってくるだけ
            double dist = distance_matrix[test_index][j];

            // 一番似てるデータを更新
            if (min_dist < 0 || dist < min_dist)
            {
                min_dist = dist;
                nearest_label = labels[j]; // 一番近かったデータのラベルを記憶
            }
        }

        // 予測結果と正解の比較
        int predicted = nearest_label;
        int actual = labels[test_index];

        printf("%s (著：%s): 予測：%s -> ", works[test_index], authors[actual], authors[predicted]);
        if (predicted == actual)
        {
            printf("〇 正解\n");
            correct_count++;
        } else
        {
            printf("× 不正解\n");
        }
    }

    // 最終正解率の算出
    double accuracy = (double)correct_count / N;

    printf("----------------------------------------\n");
    printf("全データ数: %d\n", N);
    printf("正解数    : %d\n", correct_count);
    printf("最終正解率: %.1f%%\n", accuracy * 100.0);
    
    /* 処理終了後のクロックを取得 */
    end_clock = clock();

    /* 計測時間を表示 */
    printf(
        "掛かった時間：%f\n", 
        (double)(end_clock - start_clock) / CLOCKS_PER_SEC
    );

    return 0;
}