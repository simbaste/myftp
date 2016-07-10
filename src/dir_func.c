/*
** dir_func.c for  in /home/simomb_s/semestre4/rendu_4/PSU_2015_myftp
**
** Made by stephanedarcy simomba
** Login   <simomb_s@epitech.net>
**
** Started on  Thu May 12 17:31:37 2016 stephanedarcy simomba
** Last update Sun May 15 21:38:47 2016 stephanedarcy simomba
*/

#include "ftp.h"

int	root_dir(t_ftp *ftp, char **tab)
{
  char	path[SIZE];
  char	*pth;

  if (strlen(tab[1]) >= 1 && tab[1][0] == '/')
    {
      if (strlen(tab[1]) == 1 && chdir(ftp->path) == 0)
	{
	  dprintf(ftp->client_socket,
		  "250 Requested file action okay, completed.\r\n");
	}
      else
	{
	  tab[1] = &tab[1][1];
	  pth = strcpy(path, ftp->path);
	  pth = strcat(pth, "/");
	  pth = strcat(pth, tab[1]);
	  if (chdir(pth) != 0)
	    return (dprintf(ftp->client_socket,
			    "550 Can't changed directory.\r\n"), -1);
	  dprintf(ftp->client_socket,
		  "250 Requested file action okay, completed.\r\n");
	}
      return (1);
    }
  return (0);
}

int	change_dir(t_ftp *ftp, char **tab)
{
  char	path[SIZE];
  char	*pth;

  if ((pth = realpath(tab[1], path)) != NULL)
    {
      if (root_dir(ftp, tab) == 0)
	{
	  if (strncmp(ftp->path, pth, strlen(ftp->path)) == 0 &&
	      strlen(ftp->path) <= strlen(pth))
	    {
	      if (chdir(pth) != 0)
		return (dprintf(ftp->client_socket,
				"550 Can't changed directory.\r\n"), -1);
	      dprintf(ftp->client_socket,
		      "250 Requested file action okay, completed.\r\n");
	    }
	  else
	    dprintf(ftp->client_socket, "550 Can't changed directory.\r\n");
	}
    }
  else
    dprintf(ftp->client_socket, "550 Can't changed directory.\r\n");
  return (0);
}

int	func_cwd(t_ftp *ftp)
{
  char	**tab;
  int	i;

  i = 0;
  (void)tab;
  if (ftp->log != 2)
    return (dprintf(ftp->client_socket, "530 login with USER and PASS\r\n"), 0);
  if ((tab = my_word_tab(ftp->cmd, 0, 0, 0)) == NULL)
    return (my_err("550 Invalid command.\r\n"));
  i = size_tab(tab);
  (i == 2) ? change_dir(ftp, tab) :
    dprintf(ftp->client_socket, "550 Failed to change directory.\r\n");
  my_free(tab);
  return (0);
}

int	func_cdup(t_ftp *ftp)
{
  char	**tab;
  int	i;

  i = 0;
  if (ftp->log != 2)
    return (dprintf(ftp->client_socket, "530 login with USER and PASS\r\n"), 0);
  if ((tab = my_word_tab(ftp->cmd, 0, 0, 0)) == NULL)
    return (my_err("550 Invalid command.\r\n"));
  i = size_tab(tab);
  ((strlen(ftp->pwd) > strlen(ftp->path)) && (i == 1) && (chdir("..") == 0)) ?
    dprintf(ftp->client_socket, "200 Command okay.\r\n")
    : dprintf(ftp->client_socket, "550 Failed to change directory.\r\n");
  my_free(tab);
  return (0);
}

int	func_pwd(t_ftp *ftp)
{
  char	pwd[SIZE];

  if (ftp->log != 2)
    return (dprintf(ftp->client_socket,
		    "530 login with USER and PASS.\r\n"), 0);
  getcwd(pwd, SIZE);
  if (strcmp(ftp->path, pwd) == 0)
    dprintf(ftp->client_socket, "257 \"/\" created.\n");
  else if ((strlen(ftp->path) < strlen(pwd)) &&
	   strncmp(ftp->path, pwd, strlen(ftp->path)) == 0)
    dprintf(ftp->client_socket, "257 \"%s\" created.\n",
	    &pwd[strlen(ftp->path)]);
  ftp->pwd = pwd;
  return (0);
}
