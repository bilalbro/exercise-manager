#ifndef GLOBALS_INCLUDED
   
#define GLOBALS_INCLUDED

#define MAX_EX_COUNT 500               /* maximum exercises for the language */
#define MAX_C_COUNT 100                /* maximum concepts for the language */
#define MAX_EX_NAME_LENGTH 100         /* maximum length of exercise's name */
#define MAX_C_NAME_LENGTH 50           /* maximum length of concept's name */
#define MAX_EX_C_COUNT 20              /* maximum concepts per exercise */
#define MAX_COMMAND_LENGTH 20          /* maximum command string length */

#define H_LINE(len) for (int h = 0; h < len; h++) printf("_");printf("\n")

#define FILENAME "data.bin"

#define DEBUG_STRING(var) printf(#var ": %s\n\n", var)
#define DEBUG_INT(var) printf(#var ": %i\n\n", var)
#define PRINT_NEWLINE printf("\n")


typedef struct {
   char name[MAX_EX_NAME_LENGTH];
   signed char diff;
   signed char concepts[MAX_EX_C_COUNT];
}
ex_t;


typedef struct {
   unsigned int ex_count;
   unsigned int c_count;
   char concepts[MAX_C_COUNT][MAX_C_NAME_LENGTH];
   ex_t exercises[MAX_EX_COUNT];
}
app_t;


/* global var definitions */
app_t app;

void arr_fill(signed char arr[], int count);
void strlower(char str[]);

#endif