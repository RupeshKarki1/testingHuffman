#include <stdio.h>
#include <string.h>

int main()
{
    struct student
    {
        int age;
        char name[20];
    };

    struct student x,y;
    x.age = 10;
    strcpy (x.name, "Rajesh dai");

    //printf("%s\n", x.name);
    
    // structure  as pointer
    //nnn

    struct ex
    {
        
    }




    return 0;
    
}