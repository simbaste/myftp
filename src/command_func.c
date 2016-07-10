/*
** command_func.c for  in /home/simomb_s/semestre4/rendu_4/PSU_2015_myftp
**
** Made by stephanedarcy simomba
** Login   <simomb_s@epitech.net>
**
** Started on  Thu May 12 16:02:11 2016 stephanedarcy simomba
** Last update Sun May 15 17:08:58 2016 stephanedarcy simomba
*/

#include <stdlib.h>
#include <ftp.h>

t_command	g_tab[] = {
  {"CWD", func_cwd},
  {"PWD", func_pwd},
  {"USER", func_user},
  {"PASS", func_pass},
  {"CDUP", func_cdup},
  {"QUIT", func_quit},
  {"DELE", func_dele},
  {"PASV", func_pasv},
  {"PORT", func_port},
  {"HELP", func_help},
  {"TYPE", func_type},
  {"NOOP", func_noop},
  {"RETR", func_retr},
  {"STOR", func_stor},
  {"LIST", func_list},
};

void		success_cmp(t_ftp *ftp, int i)
{
  if (i == 5)
    g_tab[i].func(ftp);
  else if ((ftp->log == 0 && i != 2) || (ftp->log == 1 && i != 3))
    dprintf(ftp->client_socket, "530 Please login with USER and PASS.\r\n");
  else
    if (g_tab[i].func(ftp) == 3)
      exit(EXIT_SUCCESS);
}

void		command_err(t_ftp *ftp)
{
  if (ftp->log != 2)
    dprintf(ftp->client_socket, "530 Please login with USER and PASS.\r\n");
  else
    dprintf(ftp->client_socket, "500 Unknown command.\r\n");
}

int		exec_command(char *command, t_ftp *ftp)
{
  int		i;
  int		n;

  i = 0;
  while ((ftp->cmd = strtok(command, "\n")) != NULL)
    {
      n = -1;
      command = &command[strlen(ftp->cmd) + 1];
      ftp->cmd = epur_str(ftp->cmd);
      while (i < 15)
	{
	  if ((n = strncasecmp(ftp->cmd, g_tab[i].name,
			       strlen(g_tab[i].name))) == 0)
	    {
	      success_cmp(ftp, i);
	      break ;
	    }
	  i++;
	}
      if (n != 0)
	command_err(ftp);
      bzero(ftp->cmd, SIZE);
    }
  return (0);
}

char		*my_getline(t_ftp *ftp)
{
  char		*str;
  char		buff[2];
  int		i;
  int		j;
  int		n;

  i = 0;
  j = 0;
  if ((str = malloc(sizeof(char) * SIZE)) == NULL)
    return (NULL);
  while ((n = read(ftp->client_socket, buff, 1)) > 0)
    {
      if (buff[0] == '\0' || buff[i] == '\r' || buff[i] == '\n')
	{
	  str[j] = '\0';
	  return (str);
	}
      str[j++] = buff[0];
    }
  return (NULL);
}

int		communication(t_ftp * ftp)
{
  char		*str;

  if (close(ftp->my_socket) == -1)
    return (my_err("Closed fd fail.\n"));
  dprintf(ftp->client_socket, "220 Service ready for new user.\r\n");
  while ((str = my_getline(ftp)))
    {
      exec_command(str, ftp);
      free(str);
    }
  return (0);
}
