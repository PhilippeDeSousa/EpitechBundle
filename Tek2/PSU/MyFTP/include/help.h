/*
** EPITECH PROJECT, 2018
** MyFTP
** File description:
** Header
*/

#ifndef HELP_H
# define HELP_H

# define HELPER_MESSAGE "214 The following commands are recognized:\n"
# define USER "USER:\tSpecifies user for authentication\n"
# define PASS "PASS:\tSpecifies password for authentication\n"
# define CWD "CWD:\tChanges working directory\n"
# define CDUP "CDUP:\tChanges working directory to parent\n"
# define QUIT "QUIT:\tDisconnection\n"
# define DELE "DELE:\tDelete file on the server\n"
# define PWD "PWD:\tPrint working directory\n"
# define PASV "PASV:\tEnable passive mode for data transfer\n"
# define PORT "PORT:\tEnable active mode for data transfer\n"
# define HELP "HELP:\tList available commands\n"
# define NOOP "NOOP:\tDo nothing\n"
# define RETR "RETR:\tDownload file from server to client\n"
# define STOR "STOR:\tUpload file from client to server\n"
# define LIST "LIST:\tList files in the current working directory\n"

#endif /* HELP_H */
