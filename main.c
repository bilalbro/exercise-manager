#include <stdio.h>
#include "globals.h"

extern void start_program(void);

int main(void)
{
   printf("Copyright 2021 (Developer: Bilal)\n");
   printf("EXERCISE MANAGER v1.0\n");
   H_LINE(110);
   start_program();
}