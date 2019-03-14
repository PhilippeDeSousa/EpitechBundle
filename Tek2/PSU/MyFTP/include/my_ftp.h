/*
** EPITECH PROJECT, 2018
** MyFTP
** File description:
** Header
*/

#ifndef MY_FTP_H
# define MY_FTP_H

# include <stdio.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>

# define CONNECT_NUMBER 10
# define DIRECTORY_MAX_SIZE 2048
# define ROOT "/home"
# define LOGIN_CAP "Anonymous"
# define LOGIN_LOW "anonymous"

/* Server values */

# define PASSIVE (227)
# define ACTIVE (228)

# define AUTH_SUCCESS "220 Service ready for new user.\n"
# define COMMAND_CORRECT "200 %s okay.\n"
# define HELP_MESSAGE "214\n"
# define PORT_ERROR "500 Illegal PORT command\n"
# define EXIT_MESSAGE "221 Service closing control connection.\n"
# define PASSW_SUCCESS "230 User logged in, proceed.\n"
# define PASSW_EMPTY "230 User logged in without a password.\n"
# define PASV_MODE "227 Entering Passive Mode "
# define LOGIN_SUCCESS "331 User name okay, need password.\n"
# define UNKNOWN_COMMAND "500 Unknown command.\n"
# define PASSW_ERROR "503 Login with USER first.\n"
# define LOGIN_ERROR "530 Login incorrect.\n"
# define LIST_ERROR "425 Select passive or active mode first.\n"
# define NOT_LOGGED "530 Please login with USER and PASS.\n"
# define FILE_ACTION_SUCCESS "250 Requested file action okay, completed.\n"
# define PERM_DENIED "550 Permission denied.\n"
# define PORT_FORMAT "550 Wrong format\n"
# define LIST_DIR "150 Here comes the directory listing.\n"
# define STOR_DIR "150 Here comes the new directory.\n"
# define DIR_OK "226 Directory send OK.\n"

typedef struct 	s_transfert
{
	int	sock;
	int	port;
	int	fport;
	int	sport;
}		t_transfert;

typedef struct 	s_client
{
	char	*root;
	char 	*ip;
	char	*name;
	char	*dir;
	int	sock;
	int	mode;
	bool	log;
	bool	usr;
	t_transfert transfert;
}		t_client;

void xwrite(int, char *);
void transf_pass(t_client *);
void transf_act(t_client *, char *);
void login(t_client *, char *);
void passw(t_client *, char *);
void ignore(void);
void cwd(t_client *, char *);
void set_root(t_client *, char *);
void cdup(t_client *);
void print_dir(t_client *, char *, char *);
void print_helper(t_client *);
void list(t_client *, char *);
void download(t_client *, char *);
void upload(t_client *, char *);
void delete(t_client *, char *);
void noop(t_client *);
void unknown_command(t_client *, char *);

int check_client(t_client *);
int create_server(int, char *);
int print_error(char *);
int client_creater(int, struct in_addr, char *);
int accept_client(int, struct sockaddr_in,
	socklen_t);

char *read_line(int);

#endif /* MY_FTP_H */
