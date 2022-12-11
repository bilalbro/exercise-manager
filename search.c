#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "globals.h"

/* external variable declarations */
extern void show_diff_info(void);
extern void show_all_concepts(void);
extern void show_concepts(signed char concepts[]);
extern void scan_concepts(char str[], signed char concepts[]);
extern void show_exercises(int ex_nums[], int ex_count);


void init_search_exercise(void);
int search_exercise(int results[], ex_t *ex);
int match_name(char s[], char t[]);
int match_diff(signed char s, signed char t);
int match_concepts(signed char s[], signed char t[]);
void init_search_concept(void);
void search_concept(signed char results[], char str[]);



void init_search_exercise(void)
{
   printf("Searching exercise...\n");
   printf("\n");

   char temp_str[MAX_EX_NAME_LENGTH];
   ex_t temp_ex;
   int diff;

   /* defaults */
   temp_ex.name[0] = 0;                               /* empty string "" */
   temp_ex.diff = -1;                                 /* impossible value -1 */
   arr_fill(temp_ex.concepts, MAX_EX_C_COUNT);        /* all -1s */

   /* ask for name */
   printf("Pattern in name (optional)\n>> ");
   gets(temp_str);
   /* if something was input, store it */
   if (temp_str[0] != 0) {
      strcpy(temp_ex.name, temp_str);
   }

   /* ask for diff */
   printf("\n");
   show_diff_info();
   printf("\n");
   printf("Difficulty (optional)\n>> ");
   gets(temp_str);
   /* if something was input, store it */
   if (temp_str[0] != 0) {
      sscanf(temp_str, "%i", &diff);
      temp_ex.diff = (signed char) diff;
   }

   /* ask for diff */
   printf("\n");
   show_all_concepts();
   printf("\n");
   printf("Concepts (optional)\n>> ");
   gets(temp_str);
   /* if something was input, store it */
   if (temp_str[0] != 0) {
      printf("---------WE ARE HERE--------------\n");
      scan_concepts(temp_str, temp_ex.concepts);
   }

   /* finally search for all exercises meeting these parameters, and then save
      the indices of all the matched entries in this array */
   int results[MAX_EX_COUNT];

   int ex_count = search_exercise(results, &temp_ex);

   show_exercises(results, ex_count);
}



int search_exercise(int results[], ex_t *ex)
{
   // DEBUG_INT(ex->concepts[0]);
   int i, r;

   r = 0;

   for (i = 0; i < app.ex_count; i++) {
      if (
      match_name(app.exercises[i].name, ex->name) &&
      match_diff(app.exercises[i].diff, ex->diff) &&
      match_concepts(app.exercises[i].concepts, ex->concepts)) {
         results[r++] = i;
      }
   }

   return r;
}



/* do a case-insensitive search of t in s */
int match_name(char s[], char t[])
{
   int _s, _s2, _t;

   /* go over the entire string s */
   for (_s = 0; s[_s] != 0; _s++) {
      /* look for the substring t starting at position _s */
      for (
      _s2 = _s, _t = 0;
      t[_t] != 0 && tolower(s[_s2]) == tolower(t[_t]);
      _t++, _s2++)
         ;

      /* if the string t was fully traversed, it means that it was found */
      if (t[_t] == 0) {
         return 1;
      }
   }

   return 0;
}



int match_diff(signed char s, signed char t)
{
   if (t == -1 || t == s)
      return 1;

   return 0;
}



int match_concepts(signed char s[], signed char t[])
{
   int i, j, found;

   for (i = 0; t[i] != -1 && i < MAX_EX_C_COUNT; i++) {
      /* initially, the current concept in t in not found */
      found = 0;

      for (j = 0; s[j] != -1 && j < MAX_EX_C_COUNT; j++) {
         if (t[i] == s[j]) {
            found = 1;
            break;
         }
      }

      /* if t[i] wasn't found, return 0 to signal failure */
      if (!found)
         return 0;
   }
   return 1;
}



void init_search_concept(void)
{
   printf("Searching concept...\n");
   printf("\n");

   char str[MAX_C_NAME_LENGTH];

   printf("Pattern in name\n>> ");
   gets(str);

   /* search for concept */
   signed char results[MAX_C_COUNT];
   arr_fill(results, MAX_C_COUNT);

   search_concept(results, str);

   show_concepts(results);
}



/* collect all the entries of concept names that match the given substring str
   and put them in results */
void search_concept(signed char results[], char str[])
{
   int i, r;

   r = 0;

   for (i = 0; i < app.c_count; i++) {
      if (match_name(app.concepts[i], str)) {
         results[r++] = i;
      }
   }
}