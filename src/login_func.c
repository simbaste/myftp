/*
** login_func.c for  in /home/simomb_s/semestre4/rendu_4/PSU_2015_myftp
**
** Made by stephanedarcy simomba
** Login   <simomb_s@epitech.net>
**
** Started on  Thu May 12 16:59:37 2016 stephanedarcy simomba
** Last update Sun May 15 21:32:26 2016 stephanedarcy simomba
*/

#include "ftp.h"

int	func_user(t_ftp *ftp)
{
  char	**tab;
  int	i;

  i = 0;
  if (ftp->log == 2)
    return (dprintf(ftp->client_socket,
		    "530 Can't change from guest user.\r\n"), 0);
  if ((tab = my_word_tab(ftp->cmd, 0, 0, 0)) == NULL)
    return (my_err("550 Invalid command.\r\n"));
  i = size_tab(tab);
  if (i == 2)
    {
      dprintf(ftp->client_socket, "331 User name okay, need password.\r\n");
      if (strcasecmp(tab[1], "anonymous") == 0)
	ftp->log = 1;
    }
  else
    dprintf(ftp->client_socket, "530 Permission denied.\r\n");
  my_free(tab);
  return (0);
}

int	func_pass(t_ftp *ftp)
{
  char	**tab;
  int	i;

  i = 0;
  if (ftp->log == 2)
    {
      dprintf(ftp->client_socket, "230 Already logged in.\r\n");
      return (0);
    }
  if ((tab = my_word_tab(ftp->cmd, 0, 0, 0)) == NULL)
    return (my_err("550 Invalid command.\r\n"));
  i = size_tab(tab);
  if (i == 1)
    {
      dprintf(ftp->client_socket, "230 Login successful.\r\n");
      chdir(ftp->path);
      ftp->log = 2;
      return (0);
    }
  else
    dprintf(ftp->client_socket, "530 Login incorrect.\r\n");
  ftp->log = 0;
  my_free(tab);
  return (0);
}
