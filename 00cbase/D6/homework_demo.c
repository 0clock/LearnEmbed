#include <stdio.h>

// 判断一个数是否为素数
int is_prime(int num) {
    if (num < 2) {
        return 0; // 不是素数
    }
    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0) {
            return 0; // 不是素数
        }
    }
    return 1; // 是素数
}

// 计算数组中素数的个数
int count_primes_in_array(int arr[], int size) {
    int count = 0;
    for (int i = 0; i < size; ++i) {
        if (is_prime(arr[i])) {
            count++;
        }
    }
    return count;
}

int main() {
    int n;

    // 输入 n
    printf("请输入整数个数 n: ");
    scanf("%d", &n);

    // 循环输入 n 个元素存到数组
    int nums[n];
    for (int i = 0; i < n; ++i) {
        printf("请输入第 %d 个整数: ", i + 1);
        scanf("%d", &nums[i]);
    }

    // 计算数组中素数的个数
    int prime_count = count_primes_in_array(nums, n);

    printf("数组中素数的个数是: %d\n", prime_count);

    return 0;
}

