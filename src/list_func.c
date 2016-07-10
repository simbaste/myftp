/*
** list_func.c for  in /home/simomb_s/semestre4/rendu_4/PSU_2015_myftp
**
** Made by stephanedarcy simomba
** Login   <simomb_s@epitech.net>
**
** Started on  Fri May 13 12:09:32 2016 stephanedarcy simomba
** Last update Sat May 14 19:11:31 2016 stephanedarcy simomba
*/

#include <sys/types.h>
#include <sys/wait.h>
#include "ftp.h"

void		my_list(t_ftp *ftp, char **tab, int i)
{
  int		oldfd;
  pid_t		pid;

  oldfd = dup(1);
  dup2(ftp->data_socket, 1);
  if ((pid = fork()) == 0)
    {
      if (i == 1)
	execl("/bin/ls", "ls", "-l", NULL);
      else if (i == 2)
	execl("/bin/ls", "ls", "-l", tab[1], NULL);

    }
  else
    waitpid(pid, 0, WSTOPPED);
  dup2(oldfd, 1);
}

int		list_accept(t_ftp *ftp)
{
  socklen_t	data_len;

  data_len = sizeof(ftp->data_addr);
  dprintf(ftp->client_socket,
	  "150 File status okay; about to open data connection.\r\n");
  if ((ftp->data_socket = accept(ftp->pasv_socket,
				 (struct sockaddr *)&ftp->data_addr,
				 &data_len)) == -1)
    {
      if (close(ftp->pasv_socket) == -1)
	return (-1);
      return (my_err("Problem with accept.\n"));
    }
  return (0);
}

int		func_list(t_ftp *ftp)
{
  char		**tab;
  int		i;

  i = 0;
  if (ftp->log != 2)
    return (dprintf(ftp->client_socket,
		    "530 login with USER and PASS.\r\n"), -1);
  if (list_accept(ftp) == -1)
    return (-1);
  if ((tab = my_word_tab(ftp->cmd, 0, 0, 0)) == NULL)
    return (my_err("550 Invalid command.\r\n"));
  i = size_tab(tab);
  if (i == 2 || i == 1)
    my_list(ftp, tab, i);
  if (close(ftp->data_socket) == -1)
    {
      my_free(tab);
      return (-1);
    }
  dprintf(ftp->client_socket,
	  "226 Closing data connection.\r\n");
  my_free(tab);
  return (0);
}
