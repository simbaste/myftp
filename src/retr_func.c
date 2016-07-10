/*
** retr_func.c for  in /home/simomb_s/semestre4/rendu_4/PSU_2015_myftp
**
** Made by stephanedarcy simomba
** Login   <simomb_s@epitech.net>
**
** Started on  Fri May 13 11:51:33 2016 stephanedarcy simomba
** Last update Sat May 14 19:11:26 2016 stephanedarcy simomba
*/

#include "ftp.h"

void		send_file(t_ftp *ftp, int i)
{
  char		**tab;
  char		*line;
  FILE		*fd;
  size_t	len;
  ssize_t	read;

  line = NULL;
  len = 0;
  if ((tab = my_word_tab(ftp->cmd, 0, 0, 0)) == NULL)
    {
      my_err("550 Invalid command.\r\n");
      return ;
    }
  i = size_tab(tab);
  if (i == 2)
    {
      fd = fopen(tab[1], "r");
      while ((read = getline(&line, &len, fd)) != -1)
	write(ftp->data_socket, line, read);
      dprintf(ftp->client_socket, "226 Closing data connection.\r\n");
      dprintf(ftp->client_socket, "Requested file action successful (for exam");
      dprintf(ftp->client_socket, "ple, file transfer or file abort)..\r\n");
      ftp->log = 1;
    }
  my_free(tab);
}

int		func_retr(t_ftp *ftp)
{
  int		i;
  socklen_t	data_len;

  i = 0;
  data_len = sizeof(ftp->data_addr);
  if (ftp->log != 2)
    return (dprintf(ftp->pasv_socket,
		    "530 login with USER and PASS.\r\n"), -1);
  if ((ftp->data_socket = accept(ftp->pasv_socket,
				 (struct sockaddr *)&ftp->data_addr,
				 &data_len)) == -1)
    {
      if (close(ftp->pasv_socket) == -1)
	return (-1);
      return (my_err("Problem with accept.\n"));
    }
  dprintf(ftp->client_socket, "150 File status okay; about to open data ");
  dprintf(ftp->client_socket, "connection.\r\n");
  send_file(ftp, i);
  if (close(ftp->data_socket) == -1)
    return (-1);
  return (0);
}
