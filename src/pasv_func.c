/*
** pasv_func.c for  in /home/simomb_s/semestre4/rendu_4/PSU_2015_myftp
**
** Made by stephanedarcy simomba
** Login   <simomb_s@epitech.net>
**
** Started on  Fri May 13 11:27:34 2016 stephanedarcy simomba
** Last update Fri May 13 11:29:38 2016 stephanedarcy simomba
*/

#include "ftp.h"

int	get_port(t_ftp *ftp)
{
  int	port;

  port = 1000;
  while (port < 5000)
    {
      ftp->pasv_addr.sin_port = htons(port);
      if (bind(ftp->pasv_socket, (const struct sockaddr *)&ftp->pasv_addr,
	       sizeof(ftp->pasv_addr)) == 0)
	break ;
      port++;
    }
  return (port);
}

int	xlisten(t_ftp * ftp)
{
  if (listen(ftp->pasv_socket, 1) == -1)
    {
      if (close(ftp->pasv_socket) == -1)
	return (-1);
      return (my_err("listen failed.\n"));
    }
  return (0);
}

int	func_pasv(t_ftp *ftp)
{
  int	port;
  char	buff[SIZE];

  if (ftp->log != 2)
    return (dprintf(ftp->client_socket,
		    "530 login with USER and PASS.\r\n"), -1);
  ftp->pasv_pe = getprotobyname("TCP");
  if ((ftp->pasv_socket = socket(AF_INET, SOCK_STREAM,
				 ftp->pasv_pe->p_proto)) == -1)
    return (fprintf(stderr, "pasv socket failed.\n"), -1);
  ftp->pasv_addr.sin_family = AF_INET;
  ftp->pasv_addr.sin_addr.s_addr = ftp->client_addr.sin_addr.s_addr;
  port = get_port(ftp);
  ftp->add1 = (&ftp->pasv_addr.sin_addr.s_addr)[0];
  ftp->add2 = (&ftp->pasv_addr.sin_addr.s_addr)[1];
  ftp->add3 = (&ftp->pasv_addr.sin_addr.s_addr)[2];
  ftp->add4 = (&ftp->pasv_addr.sin_addr.s_addr)[3];
  ftp->p1 = port / 250;
  ftp->p2 = port % 256;
  sprintf(buff, "227 Entering Passive Mode (%d,%d,%d,%d,%d,%d).\r\n",
	  127, 0, 0, 1, ftp->p1, ftp->p2);
  if (xlisten(ftp) == -1)
    return (-1);
  write(ftp->client_socket, buff, strlen(buff));
  return (0);
}
