/*
** main.c for test in /home/simomb_s/semestre4/rendu_4/PSU_2015_myftp/test
**
** Made by stephanedarcy simomba
** Login   <simomb_s@epitech.net>
**
** Started on  Wed May  4 17:27:14 2016 stephanedarcy simomba
** Last update Wed May  4 17:40:20 2016 stephanedarcy simomba
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	main()
{
  char	*str = malloc(5000);
  char	*dest;

  //sprintf(str, "%s", "bonjour\nsimba\nje suis\nfière\nmatin");
  sprintf(str, "%s", "matin");
  while ((dest = strtok(str, "\n")) != NULL)
    {
      str = &str[strlen(dest) + 1];
      printf("%s\n", dest);
    }
  return (0);
}
