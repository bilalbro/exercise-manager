#include <stdio.h>
#include <string.h>

#include "globals.h"


void show_all_concepts(void);
void show_concepts(signed char concepts[]);
void scan_concepts(char str[], signed char concepts[]);
void init_add_concept();
void add_concept(char c_name[], int c_num);
void init_update_concept(void);



/* show all the current concepts, as saved in app.concepts*/
void show_all_concepts(void)
{
   printf("Concepts:\n");
   
   int i;

   for (i = 0; i < app.c_count; i++) {
      printf("%5i) ", i + 1);
      printf("%-50s", app.concepts[i]);
      printf("   ");
      /* if i is odd, add newline at the end */
      if (i % 2 == 1) {
         printf("\n");
      }
   }

   /* add newline if the last entry was an even entry */
   if (i % 2 == 1) {
      printf("\n");
   }
}



/* given an array of signed char integers, whose each element represents the 
   index of a given concept, print its list */
void show_concepts(signed char concepts[])
{   
   int i;

   for (i = 0; concepts[i] != -1 && i < MAX_C_COUNT; i++) {
      printf("%5i) ", concepts[i] + 1);
      printf("%-50s", app.concepts[concepts[i]]);
      printf("   ");
      /* if i is odd, add newline at the end */
      if (i % 2 == 1) {
         printf("\n");
      }
   }

   /* add newline if the last entry was an even entry */
   if (i % 2 == 1) {
      printf("\n");
   }
}



/* Given a string, parse all integers out of it and save them in the given
   concepts array */
void scan_concepts(char str[], signed char concepts[])
{
   char *substr;
   int i = 0;
   int c_num;

   arr_fill(concepts, MAX_EX_C_COUNT);

   substr = strtok(str, " ");
   while (substr != NULL) {
      sscanf(substr, "%i", &c_num);
      concepts[i++] = (signed char) (c_num - 1);
      substr = strtok(NULL, " ");
   }

}



/* initiate the process of calling add_concept() */
void init_add_concept()
{
   char c_name[MAX_C_NAME_LENGTH];

   printf("Adding concept...\n");
   printf("\n");

   printf("Enter concept name\n>> ");
   gets(c_name);

   add_concept(c_name, app.c_count++);
}



/* add a new concept to the program */
void add_concept(char c_name[], int c_num)
{
   /* first get done with main memory write operation */
   strcpy(app.concepts[c_num], c_name);

   /* next, get done with disk write operation */
   FILE *data_file = fopen(FILENAME, "rb+");

   int pos = sizeof (int) + sizeof (int) + MAX_C_NAME_LENGTH * c_num;

   fseek(data_file, sizeof (int), SEEK_SET);
   fwrite(&app.c_count, sizeof (int), 1, data_file); /* update c_count in disk */

   fseek(data_file, pos, SEEK_SET);
   fwrite(c_name, MAX_C_NAME_LENGTH, 1, data_file);

   fclose(data_file);
}



/* initiate the process of updating a concept */
void init_update_concept(void)
{
   char str[MAX_C_NAME_LENGTH];
   int c_num;

   printf("Updating concept...\n");
   printf("\n");

   printf("Enter concept #\n>> ");
   gets(str);
   sscanf(str, "%i", &c_num);

   c_num--; /* normalize c_num */

   printf("Name (%s)\n>> ", app.concepts[c_num]);
   gets(str);

   if (str[0] != 0) {
      add_concept(str, c_num);
   }
}