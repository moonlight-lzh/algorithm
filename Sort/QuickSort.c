#include <stdlib.h>

/// 快速排序—划分
/// \param arr 待排数组
/// \param low 起始索引
/// \param high 终止索引
/// \return 枢轴元素索引
int Partition(int *arr, int low, int high) {
    if (arr == NULL || low >= high) {
        return low;
    }
    int pivot = arr[low];    // 第一个元素作为枢轴
    while (low < high) {    // 左右指针移动
        while (low < high && arr[high] >= pivot) {
            high--;        // 右指针左移，找到比枢轴小的元素
        }
        arr[low] = arr[high];
        while (low < high && arr[low] <= pivot) {
            low++;        // 左指针右移，找到比枢轴大的元素
        }
        arr[high] = arr[low];
    }
    arr[low] = pivot;    // 左右指针指向的位置就是枢轴元素的索引
    return low;
}

/// 快速排序
/// \param arr 待排数组
/// \param low 起始索引
/// \param high 终止索引
void QuickSort(int *arr, int low, int high) {
    if (arr == NULL || low >= high) {
        return;
    }
    int pivotIndex = Partition(arr, low, high);        // 划分，枢轴元素的索引
    QuickSort(arr, low, pivotIndex - 1);        // 枢轴左侧快排
    QuickSort(arr, pivotIndex + 1, high);        // 枢轴右侧快排
}