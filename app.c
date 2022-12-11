/* app.c
 *
 * Contains all the core functionality related to powering an exercise 
 * management application
 * 
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#include "globals.h"


/* external function declarations */
extern void init_add_exercise(void);
extern void init_add_concept();
extern void init_update_exercise(void);
extern void init_update_concept(void);
extern void init_show_exercise(void);
extern void show_all_concepts(void);
extern void init_search_exercise(void);
extern void init_search_concept(void);



void start_program(void);
void show_info(void);
int scan_command(void);
void arr_fill(signed char arr[], int count);
void load_data_file(void);
void check_data_file(void);



/* Main function that starts the program */
void start_program(void)
{
   check_data_file();
   load_data_file();
   
   printf("Exercise count: %i\n", app.ex_count);
   printf("Concepts count: %i\n", app.c_count);

   int quit;

   do {
      show_info();
      quit = scan_command();
   }
   while (!quit);
}



/* Show all the necessary information for each prompt */
void show_info(void)
{
   printf("\n");
   printf("Enter a command or 'q' to quit.\n");
   printf(">> ");
}



/* Scan the current command */
/* Return 1 if the program should be quit, otherwise return 0 */
int scan_command(void)
{
   char temp_str[20];
   char command[10], subcommand;
   
   gets(temp_str);
   sscanf(temp_str, "%s %c", command, &subcommand);

   /* if command is "q", signal calling routine to quit */
   if (strcmp(command, "q") == 0)
      return 1;

   if (strcmp(command, "add") == 0) {
      if (subcommand == 'e') {
         init_add_exercise();
      }
      else if (subcommand == 'c') {
         init_add_concept();
      }
   }

   else if (strcmp(command, "update") == 0) {
      if (subcommand == 'e') {
         init_update_exercise();
      }
      else if (subcommand == 'c') {
         init_update_concept();
      }
   }

   else if (strcmp(command, "show") == 0) {
      if (subcommand == 'e') {
         init_show_exercise();
      }
      else if (subcommand == 'c') {
         show_all_concepts();
      }
   }

   else if (strcmp(command, "search") == 0) {
      if (subcommand == 'e') {
         init_search_exercise();
      }
      else if (subcommand == 'c') {
         init_search_concept();
      }
   }

   /* signal calling routine to NOT quit */
   return 0;
}



/* Fill the given array with all -1s */
void arr_fill(signed char arr[], int count)
{
   int i;

   for (i = 0; i < count; i++)
      arr[i] = (signed char) -1;
}



/* Checks whether the file data.bin exists. If not, it's created. */
void check_data_file(void)
{
   FILE *data_file;

   /* if file does not exist, create it and fill it with given data */
   if (access(FILENAME, F_OK) != 0) {
      data_file = fopen(FILENAME, "wb");

      /* before writing the file, make sure that app.ex_count and app.c_count
         are both 0 */
      app.ex_count = 0;
      app.c_count = 0;

      fwrite(&app, sizeof app, 1, data_file);
      fclose(data_file);
   }
}



/* Load data from data.bin into app */
void load_data_file(void)
{
   FILE *data_file = fopen(FILENAME, "rb");
   fread(&app, sizeof app, 1, data_file);
   fclose(data_file);
}