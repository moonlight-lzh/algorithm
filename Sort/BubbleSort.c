#include <stdlib.h>

/// 交换
/// \param a 元素A
/// \param b 元素B
void Swap(int *a, int *b) {
    int tmp = *b;
    *b = *a;
    *a = tmp;
}

/// 冒泡排序
/// \param arr 待排数组
/// \param len 数组长度
void BubbleSort(int *arr, int len) {
    if (arr == NULL || len < 2) {
        return;
    }
    for (int i = 0; i < len - 1; i++) {
        int flag = 0;    // 标记本次排序是否有元素交替
        for (int j = 0; j < len - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                Swap(&arr[j], &arr[j + 1]);
                flag = 1;
            }
        }
        if (flag == 0) {
            return;
        }
    }
}