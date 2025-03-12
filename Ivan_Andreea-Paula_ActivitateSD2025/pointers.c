#include<stdio.h>
#include<malloc.h>

//void swap(int a, int b){
//    int temp;
//    temp = a;
//    a = b;
//    b = temp;
//}

//void swapWithPointerArgs(int *a, int *b){
//    int temp;
//    temp = *a; //save the value at address a;
//    *a = *b; //put b into a;
//    *b = temp; //put temp into b;
//}

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

//long num1 = 0L;
//long num2 = 0L;
//long* pnum = NULL;
//
//pnum = &num1; //get address of num1;
//*pnum = 2L; // set num1 to 2;
//++num2; //increment num2
//num2+=*pnum; //add num1 to num2
//
//pnum = &num2; //get address of num2
//++*pnum; //increment num2 indirectly
//
//    printf("num1 = %ld, num2 = %ld, *pnum = %ld, *pnum + num2 = %ld\n",
//           num1, num2, *pnum, *pnum + num2);
//
//    return 0;

    ///#########POINTER TO CONSTANTS##########////
//the value the pointer's pointing to must not be change
// you can still modify value (you have only applied const to the pointer),
//the address the pointer is storing
//long value = 9999L;
//const long *pvalue = &value;
//
//
//long number = 8888L;
//pvalue = &number; // OK - Changing the address in pvalue;
//using the pointer to change the value pointed to is not allowed,
//event after you have changed the address stored in the pointer


//Constant pointers
// you might want to ensure that the address stored in a pointer cannot be changed
// you can do this by using the const keyword in the declaration of the pointer

//int count = 43;
//int *const pcount = &count;
//defines a constant pointer; this ensures that a pointer
//always points to the same thing (the address stored must not be changed)


//void pointers
//a pointer of type void* can contain the address of a data item of any type
    ///#########PASS BY REFERENCE VS PASS BY VALUE##########////

//Ways you can pass data to a function
// - pass by reference
// - pass by value - when a function copies the actual value of an
// argument into the formal parameter of the function
// changes made to the parameter inside the function have no effect on the argument
//C programming uses call by value to pass arguments
// - means the code within a function cannot alter the arguments used to call the function
// - there are no changes in the values, though they had been changed inside the function
//when you pass a copy of an address, you can mimic pass by reference

//int a = 100;
//int b = 200;
//
//printf("Before swap, value of a: %d\n", a);
//printf("Before swap, value of b: %d\n", b);
//
//swap(a, b);
//
//printf("After swap, value of a: %d\n", a);
//printf("After swap, value of b: %d\n", b);

//Passing data using copies of pointers
// - Pass by reference copies the address of an argument into the formal parameter
// - the address is used to access the actual argument used in the call
// - means the changes made to the parameter affect the passed argument
// - still pass by value because you re copying the address, but C mimics pass by reference
// <= when you copy an int = pass by value, but when you copy an address = pass by refecence, changes are being made to
//to that address; in the case of pass by reference, we are still passing by value,
// but the value in this case is a copy of an address
//to pass a value by reference, argument pointers are passed to the function like any other value;
// you need to declare the function parameters as pointer types
// changes inside the function are reflected outside the function as well
// unlike pass by value where the changes do not reflect outside the function

//    int a = 100;
//    int b = 200;
//
//    printf("Before swap, value of a: %d\n", a);
//    printf("Before swap, value of b: %d\n", b);
//
//    swapWithPointerArgs(&a, &b); //a and b are not pointers but the function expects pointers as arguments, so we have to pass in the address using the address of operator
//
//    printf("After swap, value of a: %d\n", a);
//    printf("After swap, value of b: %d\n", b);

    //int function(int* ptr);
    //when you want to invoke a function that requires a pointer, you have to pass the address in using the address of operator
    //function(&x);
    //you can apply the const keyword to a parameter that is a pointer to specify that a function will not change the value to which the argument points
//bool SendMessage(const char* pmessage){
//    return true;
//} // it's the char value thats const, not its address;

//Returning pointers from a function
// it provides a way for you to return not just a single value, but a whole set of values
//int * myFunction(){}

///#########DYNAMIC MEMORY ALLOCATION##########////

}