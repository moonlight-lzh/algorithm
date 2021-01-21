#include <stdlib.h>

/// 归并排序
/// \param arr 待排数组
/// \param start 起始索引
/// \param end 终止索引
void MergeSort(int *arr, int start, int end) {
    int len = end - start + 1;
    if (arr == NULL || len < 2) {
        return;
    }

    // 辅助数组
    int *temp = (int *) malloc(sizeof(int) * len);
    if (temp == NULL) {
        return;
    }

    // 拆分
    int mid = (start + end) >> 1;
    MergeSort(arr, start, mid);
    MergeSort(arr, mid + 1, end);

    // 合并
    int k = 0;
    int i = start, j = mid + 1;        // 左右侧指针
    while (i <= mid && j <= end) {
        temp[k++] = arr[i] < arr[j] ? arr[i++] : arr[j++];        // 对比左右侧元素
    }
    while (i <= mid && k < len) {
        temp[k++] = arr[i++];   // 左侧未填充的元素
    }
    while (j <= end) {
        temp[k++] = arr[j++];   // 右侧未填充的元素
    }
    for (i = 0; i < len; i++) {
        arr[start + i] = temp[i];   // 归并排序的结果复制给原数组
    }
    free(temp);        // 释放申请的堆空间
}