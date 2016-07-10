/*
** main.c for main in /home/simomb_s/semestre4/rendu_4/PSU_2015_myftp
**
** Made by stephanedarcy simomba
** Login   <simomb_s@epitech.net>
**
** Started on  Tue May  3 21:56:06 2016 stephanedarcy simomba
** Last update Sun May 15 09:28:18 2016 stephanedarcy simomba
*/

#include <unistd.h>
#include "ftp.h"

int		main(int ac, char **av)
{
  t_ftp		ftp;
  char		my_pwd[SIZE];

  if (ac != 3)
    {
      fprintf(stderr, "USAGE : %s [Port] [Path]\n", av[0]);
      return (1);
    }
  ftp.port = atoi(av[1]);
  if (chdir(av[2]) == -1)
    return (my_err("invalid path.\n"));
  getcwd(my_pwd, SIZE);
  ftp.path = my_pwd;
  ftp.pwd = my_pwd;
  ftp.pe = getprotobyname("TCP");
  ftp.my_addr.sin_port = htons(ftp.port);
  ftp.my_addr.sin_family = AF_INET;
  ftp.my_addr.sin_addr.s_addr = INADDR_ANY;
  ftp.log = 0;
  ftp.pasv = 0;
  my_ftp(&ftp);
  return (0);
}
