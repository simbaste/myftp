/*
** function.c for function in /home/simomb_s/semestre4/rendu_4/PSU_2015_myftp
**
** Made by stephanedarcy simomba
** Login   <simomb_s@epitech.net>
**
** Started on  Wed May  4 19:07:31 2016 stephanedarcy simomba
** Last update Fri May 13 13:15:18 2016 stephanedarcy simomba
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/wait.h>
#include "ftp.h"

int	func_port(t_ftp *ftp)
{
  if (ftp->log != 2)
    return (dprintf(ftp->client_socket, "530 login with USER and PASS\r\n"), 0);
  printf("port : %s\n", ftp->cmd);
  return (0);
}

int	func_noop(t_ftp *ftp)
{
  if (ftp->log != 2)
    return (dprintf(ftp->client_socket,
		    "530 login with USER and PASS.\r\n"), 0);
  dprintf(ftp->client_socket, "220 Service ready for new user.\r\n");
  return (0);
}

int	func_stor(t_ftp *ftp)
{
  if (ftp->log != 2)
    return (dprintf(ftp->client_socket,
		    "530 login with USER and PASS.\r\n"), -1);
  printf("stor : %s\n", ftp->cmd);
  return (0);
}
