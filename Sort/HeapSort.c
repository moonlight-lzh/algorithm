#include <stdlib.h>

/// 交换
/// \param a 元素A
/// \param b 元素B
void Swap(int *a, int *b) {
    int tmp = *b;
    *b = *a;
    *a = tmp;
}

/// 向下进行堆调整
/// \param arr 待排数组
/// \param len 数组长度
void AdjustHeap(int *arr, int len) {
    if (arr == NULL || len < 2) {
        return;
    }
    for (int parent = (len >> 1) - 1; parent >= 0; parent--) {        // 从最后一个父节点往前调整到根节点
        int child = (parent << 1) + 1;     // 左孩子
        if (child + 1 < len && arr[child + 1] > arr[child]) {    // 右孩子存在，且大于左孩子
            child++;
        }
        if (arr[child] > arr[parent]) {
            Swap(&arr[parent], &arr[child]);    // 交换父子节点
        }
    }
}

/// 堆排序
/// \param arr 待排数组
/// \param len 数组长度
void HeapSort(int *arr, int len) {
    if (arr == NULL || len < 2) {
        return;
    }
    for (; len > 1; len--) {
        AdjustHeap(arr, len);        // 堆调整，构建大顶堆，堆中最大值调整到堆顶
        Swap(&arr[0], &arr[len - 1]);        // 将第一个元素（堆中最大值）与最后一个交换
    }
}
