
/**
 * 计算base的n次幂 base^n
 * @param base 底数
 * @param n N次幂
 * @param result 计算结果
 * @param resultSize 计算结果的长度
 */
void fastPow(char *base, long long n, char result[], int *resultSize) {
    *resultSize = 1;
    result[0] = '1';

    int bsize = 0;
    while (n > 0) {
        if (n & 1) {
            multiply(result, base, result, resultSize);
        }
        multiply(base, base, base, &bsize);
        n >>= 1;
    }
}
