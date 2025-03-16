#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>

void square(int *x){
    *x = (*x) * (*x);
}

int main(){
    //1. write a program that creates an integer variable with a hard-coded value.
    // assign that variable's address to a pointer variable;
    //display the address of the pointer, the value of the pointer,
    // and the value of what the pointer is pointing to.

//    int number = 10;
//    int* pNumber = NULL; //c allocates memory for the pointer, not for what its pointing to
//    pNumber = &number; //assigning address to pointer using address of operator
//    printf("value of pointer address: %p\n", &pNumber);
//    printf("value of variable address: %p\n", &number);
//    printf("value inside pointer variable(should match variable address): %p\n", pNumber);
//    printf("value of what the pointer's pointing to : %d\n", * pNumber);

    //2. write a function that squares a number by itself
    //the function should define as a parameter an int pointer

    int num = 10;
    printf("Original value of num: %d\n", num);
    square(&num);
    printf("Updated value of num: %d\n", num);


    return 0;
}