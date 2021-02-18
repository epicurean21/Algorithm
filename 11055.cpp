#include<stdio.h>

int main() {
    int i, j, n, a[1001], d[1001], max = 0; scanf("%d", &n);
    for (i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (i = 1; i <= n; i++) {
        d[i] = a[i];
        for (j = 1; j < i; j++)
            if (a[j] < a[i] && d[i] < d[j] + a[i])
                d[i] = d[j] + a[i];
        if (max < d[i]) max = d[i];
    }
    printf("%d", max);
}