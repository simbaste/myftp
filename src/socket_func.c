/*
** socket_func.c for  in /home/simomb_s/semestre4/rendu_4/PSU_2015_myftp
**
** Made by stephanedarcy simomba
** Login   <simomb_s@epitech.net>
**
** Started on  Thu May 12 16:22:47 2016 stephanedarcy simomba
** Last update Sun May 15 12:20:26 2016 stephanedarcy simomba
*/

#include <ftp.h>

int		accept_client(t_ftp *ftp)
{
  pid_t		pid;
  socklen_t	my_addr_len;

  my_addr_len = sizeof(ftp->client_addr);
  while (1)
    {
      if ((ftp->client_socket = accept(ftp->my_socket,
				       (struct sockaddr *)&ftp->client_addr,
				       &my_addr_len)) == -1)
	{
	  if (close(ftp->my_socket) == -1)
	    return (-1);
	  my_err("Problem with accept.\n");
	  exit(EXIT_FAILURE);
	}
      if ((pid = fork()) == 0)
	{
	  communication(ftp);
	  shutdown(ftp->client_socket, 2);
	  exit(EXIT_FAILURE);
	}
    }
  return (-1);
}

int		my_ftp(t_ftp *ftp)
{
  if ((ftp->my_socket = socket(AF_INET, SOCK_STREAM, ftp->pe->p_proto)) == -1)
    return (my_err("Creation of the socket failed.\n"));
  if (bind(ftp->my_socket, (const struct sockaddr *)&ftp->my_addr,
	   sizeof(ftp->my_addr)) == -1)
    return (my_err("Bind failed.\n"));
  if (listen(ftp->my_socket, 42) == -1)
    {
      if (close(ftp->my_socket) == -1)
	return (-1);
      return (my_err("listen failed.\n"));
    }
  if (accept_client(ftp) == -1)
    return (-1);
  return (0);
}
