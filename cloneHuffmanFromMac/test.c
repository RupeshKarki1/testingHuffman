#include <stdio.h>

int result;

int fact(int n)
{
    if(n >= 1){
     result = n * fact(n-1);
     return result;
    }else
    {
        return 1;
    }
}

int main()
{
    fact(5);
    printf("%d\n", result);
    return 0;
}