#include <stdio.h>
#include <stdlib.h>

#include "../src/calculator.h"

int main()
{
    if(add(2,3)!=5)
        return EXIT_FAILURE;

    if(sub(5,3)!=2)
        return EXIT_FAILURE;

    if(mul(3,4)!=12)
        return EXIT_FAILURE;

    if(divide(10,2)!=5)
        return EXIT_FAILURE;

    printf("Unit Tests Passed\n");

    return EXIT_SUCCESS;
}
