#include <stdlib.h>

/// 希尔排序
/// \param arr 待排数组
/// \param len 数组长度
void ShellSor(int *arr, int len) {
    if (arr == NULL || len < 2) {
        return;
    }
    for (int gap = len >> 1; gap > 0; gap >>= 1) {      // 增量，分组
        for (int i = gap; i < len; i++) {
            int j, tmp = arr[i];    // 待插入元素
            for (j = i - gap; j >= 0 && arr[j] > tmp; j -= gap) {
                arr[j + gap] = arr[j];      // 大的元素后移
            }
            arr[j + gap] = tmp;     // 插入位置
        }
    }
}