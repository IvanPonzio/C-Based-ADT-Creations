#include "dna.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef TEST

int main()
{
    dna_t A;
    A = dna_A();
    dna_t H;
    H = dna_T();
    // dna_t H2;
    // H2 = dna_A();
    dna_t JUNTO;
    JUNTO = dna_join(A,H);
    dna_print(JUNTO);
    //printf("%c" , JUNTO);

    dna_destroy(H);
    dna_destroy(A);
    dna_destroy(JUNTO);
    return (0);
}

#endif
