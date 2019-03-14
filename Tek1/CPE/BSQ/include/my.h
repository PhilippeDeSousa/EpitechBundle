/*
** my.h for BSQ in /home/philippe/Projects/CPE_2016_BSQ
** 
** Made by Philippe De Sousa
** Login   <philippe.de-sousa-violante@epitech.eu>
** 
** Started on  Tue May  2 14:40:35 2017 Philippe De Sousa
** Last update Sun May  7 22:39:11 2017 Philippe De Sousa
*/

#ifndef MY_H
#define MY_H

typedef struct  s_square {
    int x;
    int y;
    int val;
}               t_square;

void my_putstr(int, const char *);
void check_square(char **, t_square *);

int my_strlen(const char *);
int bsq(char **);

char **str_to_tab(const char *);

#endif /*MY_H*/
