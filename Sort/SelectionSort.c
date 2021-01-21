#include <stdlib.h>

/// 交换
/// \param a 元素A
/// \param b 元素B
void Swap(int *a, int *b) {
    int tmp = *b;
    *b = *a;
    *a = tmp;
}

/// 选择排序
/// \param arr 待排数组
/// \param len 数组长度
void SelectionSort(int *arr, int len) {
    if (arr == NULL || len < 2) {
        return;
    }
    for (int i = 0; i < len; i++) {
        int minIndex = i;    // 后序最小元素的索引
        for (int j = i + 1; j < len; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            Swap(&arr[i], &arr[minIndex]);
        }
    }
}