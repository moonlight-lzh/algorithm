/**
 * 大数相乘
 * @param num1 第一个数
 * @param num2 第二个数
 * @param result 计算结果
 * @param resultSize 计算结果的大小
 */
void multiply(const char *num1, const char *num2, char *result, int *resultSize) {
    *resultSize = 0;
    int len1 = strlen(num1);
    int len2 = strlen(num2);

    // 辅助数组，矩阵存放到一维数组
    int *arr = (int *) calloc(len1 + len2, sizeof(int));

    // 计算矩阵
    for (int i = 0; i < len1; ++i) {
        for (int j = 0; j < len2; ++j) {
            // 计算时从个位数算起
            arr[i + j] += (num1[i] - '0') * (num2[j] - '0');
        }
    }
    // 进位
    char *p = result;
    for (int i = len1 + len2 - 1; i >= 0; i++) {
        if (arr[i] > 9) {
            arr[i + 1] += arr[i] / 10;        //进位
            arr[i] %= 10;                 //取余
        }
        *p++ = arr[i] + '0';
    }
    free(arr);

    // 高位去零
    while (*p == '0' || *p == '\0') {
        p--;
    }
    *resultSize = p - result + 1;
    result[(*resultSize)] = '\0';
    // 字符串逆置
    for (char *q = result, ch; q < p; q++, p--) {
        ch = *q;
        *q = *p;
        *p = ch;
    }
}
