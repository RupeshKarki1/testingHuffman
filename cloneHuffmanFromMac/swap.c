#include <stdio.h>

int main()
{
    int m = 5;
    int n = 6;
    swap(&m, &n);
    printf("m: %d, n: %d\n", m, n);
    return 0;
}

void swap(int *a, int *b)
{
    int temp;

    temp = *a;
    *a = *b;
    *b = temp;
   
}
