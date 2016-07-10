/*
** ftp.h for ftp in /home/simomb_s/semestre4/rendu_4/PSU_2015_myftp
**
** Made by stephanedarcy simomba
** Login   <simomb_s@epitech.net>
**
** Started on  Tue May  3 21:57:29 2016 stephanedarcy simomba
** Last update Sat May 14 19:12:09 2016 stephanedarcy simomba
*/

#ifndef FTP_H_
# define FTP_H_

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <signal.h>
# include <netdb.h>
# include <unistd.h>

# define SIZE 4096

typedef struct		s_ftp
{
  int			my_socket;
  int			data_socket;
  int			pasv_socket;
  int			client_socket;
  int			port;
  int			my_addr_len;
  int			log;
  int			pasv;
  int			p1;
  int			p2;
  unsigned char		add1;
  unsigned char		add2;
  unsigned char		add3;
  unsigned char		add4;
  char			*pwd;
  char			*path;
  char			*cmd;
  char			*ip;
  struct protoent	*pe;
  struct protoent	*pasv_pe;
  struct sockaddr_in	my_addr;
  struct sockaddr_in	pasv_addr;
  struct sockaddr_in	client_addr;
  struct sockaddr_in	data_addr;
}			t_ftp;

typedef struct		s_command
{
  char			*name;
  int			(*func)(t_ftp*);
}			t_command;

void			cmd_exec(char *, char *);
int			my_err(char *);
int			exec_command(char *, t_ftp *);
int			communication(t_ftp *);
char			*epur_str(char *);
int			accept_client(t_ftp *);
int			my_ftp(t_ftp *);
void			my_free(char **);
char			**my_word_tab(char *, int, int, int);
int			size_tab(char **);
int			func_user(t_ftp *);
int			func_pass(t_ftp *);
int			func_cwd(t_ftp *);
int			func_cdup(t_ftp *);
int			func_quit(t_ftp *);
int			func_dele(t_ftp *);
int			func_pwd(t_ftp *);
int			func_pasv(t_ftp *);
int			func_port(t_ftp *);
int			func_help(t_ftp *);
int			func_type(t_ftp *);
int			func_noop(t_ftp *);
int			func_retr(t_ftp *);
int			func_stor(t_ftp *);
int			func_list(t_ftp *);

#endif /* !FTP_H_ */
