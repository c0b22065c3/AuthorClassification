#include <stdio.h>
#include <string.h>

#define N 4 // 全データ数

// データの構造体（今回は座標ではなく「テキストデータ」そのもの）
typedef struct {
    char text[100];
    int label;
} DataPoint;

// 【ステップ1&2&3】擬似的な圧縮サイズを返す関数
// （共通の文字が多いほど、連結したときにサイズが小さくなる簡易ロジック）
int compress_size(const char *str) {
    int len = strlen(str);
    int unique_count = 0;
    int flags[256] = {0};
    
    for (int i = 0; i < len; i++) {
        unsigned char c = str[i];
        if (!flags[c]) {
            unique_count++;
            flags[c] = 1;
        }
    }
    return (len + unique_count) / 2 + 1; // 圧縮後の想定サイズ
}

// 【ステップ4】NCD（正規化圧縮距離）を計算する関数
double calculate_ncd(const char *x, const char *y) {
    int cx = compress_size(x); // C(x)
    int cy = compress_size(y); // C(y)
    
    // xとyを連結した文字列 xy を作成
    char xy[200];
    sprintf(xy, "%s%s", x, y);
    int cxy = compress_size(xy); // C(xy)
    
    // NCDの計算式を適用
    int min_c = (cx < cy) ? cx : cy;
    int max_c = (cx > cy) ? cx : cy;
    
    return (double)(cxy - min_c) / max_c;
}

int main() {
    // 今回のサンプルデータ（テキストと、そのカテゴリラベル）
    // ラベル 0: 犬関連、 ラベル 1: 果物関連
    DataPoint dataset[N] = {
        {"dog puppy pet", 0},     // データ0
        {"apple banana fruit", 1},// データ1
        {"puppy dog animal", 0},  // データ2
        {"banana apple orange", 1}// データ3
    };

    // 【ステップ5】距離行列（すべての組み合わせのNCD）を作る
    double distance_matrix[N][N];
    printf("--- 【ステップ5】距離行列（NCD）の算出 ---\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            distance_matrix[i][j] = calculate_ncd(dataset[i].text, dataset[j].text);
            printf("%.3f  ", distance_matrix[i][j]);
        }
        printf("\n");
    }
    printf("----------------------------------------\n\n");

    // 【ステップ6】LOOCV（一つ抜き交差検証）と1-NNを用いて分類する
    printf("--- 【ステップ6】LOOCVによる分類開始 ---\n");
    int correct_count = 0;

    for (int i = 0; i < N; i++) {
        int test_index = i;
        double min_dist = -1.0;
        int nearest_label = -1;

        // 自分（test_index）以外の学習データから、NCDが最も近いものを探す
        for (int j = 0; j < N; j++) {
            if (j == test_index) continue; // 一つ抜き

            double dist = distance_matrix[test_index][j]; // 事前に作った距離行列から取得
            
            if (min_dist < 0 || dist < min_dist) {
                min_dist = dist;
                nearest_label = dataset[j].label;
            }
        }

        int predicted = nearest_label;
        int actual = dataset[test_index].label;

        printf("データ [%d] 予測: %d, 正解: %d -> ", test_index, predicted, actual);
        if (predicted == actual) {
            printf("〇 正解\n");
            correct_count++;
        } else {
            printf("× 不正解\n");
        }
    }

    printf("----------------------------------------\n");
    printf("最終正解率: %.1f%%\n", ((double)correct_count / N) * 100.0);

    return 0;
}