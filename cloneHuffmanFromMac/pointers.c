#include <stdio.h>
/*
entrypoint function which is showcasing the usage of pointers 
*/
int main()
{
    // int x = 10;
    // int *y = &x;
    
    // printf("value of x: %d\n", x);
    // printf("address of x : %u\n", &x);
    // printf("address of x stored in y: %u\n", y);
    // printf("value of x through y : %d\n", *y);
    // printf("value of y: %u\n", &y);


    //array traversal using pointers

    int n = 5;
    int arr[] = {1,2,3,4,5};

    int *ptr;
    ptr = arr;

    for (int i = 0; i < n; i++)
    {
        printf("%d ", ptr[0]);
        ptr++;
    }
    printf("\n");



    return 0;
}