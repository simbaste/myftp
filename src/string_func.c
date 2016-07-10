/*
** string_func.c for  in /home/simomb_s/semestre4/rendu_4/PSU_2015_myftp
**
** Made by stephanedarcy simomba
** Login   <simomb_s@epitech.net>
**
** Started on  Thu May 12 15:56:54 2016 stephanedarcy simomba
** Last update Sat May 14 23:42:45 2016 stephanedarcy simomba
*/

#include <stdio.h>
#include <stdlib.h>
#include "ftp.h"

int	my_err(char *str)
{
  fprintf(stderr, "%s", str);
  return (-1);
}

char	*epur_str(char *str)
{
  int	i;
  int	j;

  i = 0;
  j = 0;
  while (str && str[i] != 0)
    {
      if (str[i] == ' ' || str[i] == '\t')
	{
	  while (str[i] == ' ' || str[i] == '\t')
	    i++;
	  if (str[i] != 0 && j > 0)
	    str[j++] = ' ';
	}
      str[j++] = str[i++];
    }
  str[j] = 0;
  return (str);
}

char	**my_word_tab(char *str, int i, int j, int k)
{
  char	**tab;

  if ((tab = malloc(SIZE * sizeof(char*))) == NULL ||
      (tab[0] = malloc(SIZE * sizeof(char))) == NULL)
    return (my_err("Malloc failed.\n"), NULL);
  while (str && str[i] != '\0' && str[i] != '\r')
    {
      if (str[i] == ' ')
	{
	  i++;
	  tab[j][k] = 0;
	  if (str[i] == '\0' || str[i] == '\r')
	    break ;
	  k = 0;
	  j++;
	  if ((tab[j] = malloc(SIZE * sizeof(char))) == NULL)
	    return (my_err("Malloc failed.\n"), NULL);
	}
      tab[j][k++] = str[i++];
    }
  tab[j++][k] = 0;
  if ((tab[j] = malloc(SIZE * sizeof(char))) == NULL)
    return (my_err("Malloc failed.\n"), NULL);
  tab[j] = NULL;
  return (tab);
}

int	size_tab(char **tab)
{
  int	i;

  i = 0;
  while (tab && tab[i] != NULL)
    i++;
  return (i);
}

void	my_free(char **tab)
{
  int	i;

  i = 0;
  while (tab && tab[i])
    {
      free(tab[i]);
      tab[i] = NULL;
      ++i;
    }
  if (tab)
    free(tab);
}
