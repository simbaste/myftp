/*
** help_func.c for  in /home/simomb_s/semestre4/rendu_4/PSU_2015_myftp
**
** Made by stephanedarcy simomba
** Login   <simomb_s@epitech.net>
**
** Started on  Fri May 13 11:31:27 2016 stephanedarcy simomba
** Last update Sun May 15 20:13:44 2016 stephanedarcy simomba
*/

#include "ftp.h"

char	*g_tab_cmd[] = {
  "USER",
  "PASS",
  "CWD",
  "PWD",
  "CDUP",
  "QUIT",
  "DELE",
  "PASV",
  "PORT",
  "HELP",
  "TYPE",
  "NOOP",
  "RETR",
  "STOR",
  "LIST",
};

int	help_func(t_ftp *ftp, char *func)
{
  int	i;
  char	buff[SIZE];

  i = 0;
  while (i < 15)
    {
      if (strcasecmp(func, g_tab_cmd[i]) == 0)
	{
	  sprintf(buff,
		  "214 Help message.\n help for %s function.", func);
	  dprintf(ftp->client_socket, "%s\r\n", buff);
	}
      i++;
    }
  return (0);
}

int	help_g(t_ftp *ftp)
{
  dprintf(ftp->client_socket, "214 Help message.\r\n");
  return (0);
}

int	func_help(t_ftp *ftp)
{
  char	**tab;
  int	i;

  i = 0;
  if ((tab = my_word_tab(ftp->cmd, 0, 0, 0)) == NULL)
    return (my_err("550 Invalid command.\r\n"));
  i = size_tab(tab);
  (i == 2) ? help_func(ftp, tab[1]) : help_g(ftp);
  my_free(tab);
  return (0);
}
