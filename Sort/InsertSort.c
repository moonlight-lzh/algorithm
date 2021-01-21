#include <stdlib.h>

/// 插入排序
/// \param arr 待排数组
/// \param len 数组长度
void InsertSort(int *arr, int len) {
    if (arr == NULL || len < 2) {
        return;
    }
    for (int i = 1; i < len; i++) {
        int temp = arr[i];    // 保存当前的值
        int j;
        for (j = i - 1; j >= 0 && arr[j] > temp; j--)    // 比当前值大的数全部后移
        {
            arr[j + 1] = arr[j];    // 后移
        }
        arr[j + 1] = temp;    // 后移完成，将j+1处赋值temp
    }
}