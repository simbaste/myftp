/*
** quit_dele_func.c for  in /home/simomb_s/semestre4/rendu_4/PSU_2015_myftp
**
** Made by stephanedarcy simomba
** Login   <simomb_s@epitech.net>
**
** Started on  Fri May 13 12:25:04 2016 stephanedarcy simomba
** Last update Sun May 15 09:33:41 2016 stephanedarcy simomba
*/

#include "ftp.h"

int	func_quit(t_ftp *ftp)
{
  dprintf(ftp->client_socket, "221 Service closing control connection.\r\n");
  close(ftp->client_socket);
  return (3);
}

int	func_dele(t_ftp *ftp)
{
  if (ftp->log != 2)
    return (dprintf(ftp->client_socket, "530 login with USER and PASS\r\n"), 0);
  dprintf(ftp->client_socket, "250 Requested file action okay, completed.\r\n");
  return (0);
}

int	func_type(t_ftp *ftp)
{
  if (ftp->log != 2)
    return (dprintf(ftp->client_socket,
		    "530 login with USER and PASS.\r\n"), 0);
  dprintf(ftp->client_socket, "220 Type set to ASCII mode.\r\n");
  return (0);
}
