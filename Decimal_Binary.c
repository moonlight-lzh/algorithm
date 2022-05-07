/// <summary>
/// 十进制数转换成二进制数
/// </summary>
/// <param name="value">十进制数</param>
/// <param name="bits">二进制数的位数</param>
/// <returns>bits位的二进制数</returns>
int* decimal2binary(int value, int bits)
{
    int i, negative = 0;
    int* result;

    if (bits < 4)
    {
        return NULL;
    }

    result = (int*)malloc(sizeof(int) * bits);
    if (!result)
    {
        return NULL;
    }

    if (value < 0)      // 负数
    {
        negative = 1;
        value = -value;
    }

    for (i = 0; i < bits; i++)
    {
        result[bits - i - 1] = value >> i & 0x1;      // 原码
        if (negative)       // 负数反码
        {
            result[bits - i - 1] ^= 1;
        }
    }

    if (negative)       // 负数补码
    {
        result[bits - 1] += 1;
        for (i = bits - 2; i >= 0; i--)
        {
            if (result[i + 1] < 2)
            {
                break;
            }
            else
            {
                result[i + 1] = 0;
                result[i] += 1;
            }
        }
    }
    return result;
}
