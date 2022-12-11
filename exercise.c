#include <stdio.h>
#include <string.h>

#include "globals.h"


/* external variable declarations */
extern void show_all_concepts(void);
extern void scan_concepts(char str[], signed char concepts[]);
extern void show_concepts(signed char concepts[]);

void show_diff_info(void);
void map_diff(signed char diff, char str[]);
void init_add_exercise(void);
void add_exercise(ex_t ex, int ex_num);
void init_update_exercise(void);
void init_show_exercise(void);
void show_all_exercises(void);
void show_exercises(int ex_nums[], int ex_count);
void show_exercise(int ex_num);


void show_diff_info(void)
{
   printf("Difficulty mapping:\n");
   printf("  1) Very easy");
   printf("  2) Easy");
   printf("  3) Average");
   printf("  4) Hard");
   printf("  5) Very hard");
   printf("  6) Aficianado\n");
}



void map_diff(signed char diff, char str[])
{
   char diff_map[6][15] = {"Very easy", "Easy", "Average", "Hard",
                           "Very hard", "Aficianado"};
   strcpy(str, diff_map[diff - 1]);
}



void init_add_exercise(void)
{
   if (app.c_count == 0) {
      printf("Not enough concepts!\n");
      return;
   }
   ex_t ex;
   int diff;
   char temp_str[MAX_EX_NAME_LENGTH];

   printf("Adding exercise...\n");
   PRINT_NEWLINE;

   /* ask for name */
   printf("Name\n>> ");
   gets(ex.name);
   PRINT_NEWLINE;

   /* ask for diff rating */
   show_diff_info();
   PRINT_NEWLINE;
   printf("Difficulty rating\n>> ");
   gets(temp_str);
   sscanf(temp_str, "%i", &diff);
   ex.diff = (signed char) diff;
   PRINT_NEWLINE;

   /* ask for concepts */
   show_all_concepts();
   PRINT_NEWLINE;
   printf("Concepts (space-delimited integers)\n>> ");
   gets(temp_str);
   scan_concepts(temp_str, ex.concepts);
   PRINT_NEWLINE;

   /* once all data has been accumulated, add the exercise */
   add_exercise(ex, app.ex_count++);
}



void add_exercise(ex_t ex, int ex_num)
{
   /* first get done with main memory write operation */
   app.exercises[ex_num] = ex;


   /* next, get done with disk write operation */
   FILE *data_file = fopen(FILENAME, "rb+");

   /* seek to the position in the data.bin file where the ex_num exercise
      appears. The position is calculated as follows:

      sizeof (int) + sizeof (int) + sizeof(app.concepts) 
   */
   int pos = sizeof app.ex_count +
             sizeof app.c_count +
             sizeof app.concepts +
             sizeof (ex_t) * ex_num;
   
   fwrite(&app.ex_count, sizeof (int), 1, data_file); /* update ex_count in disk */
   fseek(data_file, pos, SEEK_SET);
   fwrite(&ex, sizeof (ex_t), 1, data_file);
   fclose(data_file);
}



void init_update_exercise(void)
{
   printf("Updating exercise...\n");
   printf("\n");

   char temp_str[MAX_EX_NAME_LENGTH];
   int ex_num;

   printf("Exercise # >> ");
   gets(temp_str);
   sscanf(temp_str, "%i", &ex_num);

   ex_num--;

   /* temporarily load the exercise at position ex_num into local variable */
   ex_t ex = app.exercises[ex_num];


   printf("Name (%s) >> ", ex.name);
   gets(temp_str);
   /* if got something input, update the respective entry */
   if (temp_str[0] != 0) {
      strcpy(ex.name, temp_str);
   }


   printf("Difficulty rating (%i) >> ", ex.diff);
   gets(temp_str);
   /* if got something input, update the respective entry */
   if (temp_str[0] != 0) {
      sscanf(temp_str, "%i", &ex.diff);
   }


   show_all_concepts();
   printf("Concepts (space-delimited integers) >> ");
   gets(temp_str);
   /* if got something input, update the respective entry */
   if (temp_str[0] != 0) {
      scan_concepts(temp_str, ex.concepts);
   }

   add_exercise(ex, ex_num);
}



void init_show_exercise(void)
{
   printf("Showing exercise...\n");
   printf("\n");

   char temp_str[MAX_COMMAND_LENGTH];
   int ex_num;

   printf("Exercise # >> ");
   gets(temp_str);

   if (strcmp(temp_str, "all") == 0) {
      show_all_exercises();
   }
   else {
      sscanf(temp_str, "%i", &ex_num);
      ex_num--; /* normalize ex_num */
      show_exercise(ex_num);
   }

}



void show_all_exercises(void)
{
   printf("\n");

   int i;

   /* for each exercises, print its name on a new line */
   for (i = 0; i < app.ex_count; i++) {
      printf("%5i) %s\n", i + 1, app.exercises[i].name);
   }

   printf("\n");
}



void show_exercises(int ex_nums[], int ex_count)
{
   H_LINE(110);
   printf("\n");

   int i;

   /* for each exercises, print its name on a new line */
   for (i = 0; i < ex_count; i++) {
      printf("%5i) %s\n", ex_nums[i] + 1, app.exercises[ex_nums[i]].name);
   }

   H_LINE(110);
   printf("\n");
}



void show_exercise(int ex_num)
{
   printf("\n");
   H_LINE(110);

   /* print number */
   printf("Exercise # %i\n\n", ex_num + 1);

   /* print name */
   printf("%s\n", app.exercises[ex_num].name);

   /* print difficulty rating */
   char diff_str[15];
   map_diff(app.exercises[ex_num].diff, diff_str);
   printf("(%s)\n\n", diff_str);

   /* print concepts */
   show_concepts(app.exercises[ex_num].concepts);

   H_LINE(110);
}