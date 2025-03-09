#include<stdio.h>
#include<malloc.h>


int main()
{

    ///#########ACCESSING POINTERS##########////
//    int count = 10, x;
//    int *int_pointer;
//
//    int_pointer = &count;
//    x = *int_pointer;
//
//    printf("count= %i, x = %i\n", count, x);
//    printf("int_pointer value = %p\n", int_pointer);
//    printf("count address= %p\n", &count);
//    printf("int_pointer address = %p\n", (void*) &int_pointer);
//    printf("int_pointer size in bytes = %d\n", (int)sizeof(int_pointer));
//
//    return 0;

//    int number = 0;
//    int *pnumber = NULL;
//
//    number = 10;
//    printf("number's address: %p\n", &number);
//    printf("number's value: %d\n", number);
//
//    pnumber = &number;
//    printf("pnumber's address: %p\n", (void*) &pnumber);
//    printf("pnumber's size: %d\n", (int)sizeof(pnumber));
//    printf("pnumber's value: %p\n", pnumber);
//    printf("value pnumber's pointing at: %d\n", *pnumber);
//
//    return 0;

    ///#########USING POINTERS##########////
//1. Assign an address to a pointer
//2. Dereference a pointer
//3. Take a pointer address
//4. Pointer arithmetic

//int number = 0;
//int *pnumber = NULL;
//number = 10;
//pnumber = &number;
//*pnumber += 25; //increments the value of the number variable by 25
////use of *pointer in an expression is identical to the use of x in the same expression
//printf("address pnumber's pointing at = %p\n", pnumber);
//printf("pnumber's value = %d\n", *pnumber);
//int value = 999;
//pnumber = &value;
//*pnumber += 25;
//printf("address pnumber's pointing at = %p\n", pnumber);
//printf("pnumber's value = %d\n", *pnumber);

long num1 = 0L;
long num2 = 0L;
long* pnum = NULL;

pnum = &num1; //get address of num1;
*pnum = 2L; // set num1 to 2;
++num2; //increment num2
num2+=*pnum; //add num1 to num2

pnum = &num2; //get address of num2
++*pnum; //increment num2 indirectly

    printf("num1 = %ld, num2 = %ld, *pnum = %ld, *pnum + num2 = %ld\n",
           num1, num2, *pnum, *pnum + num2);

    return 0;

}