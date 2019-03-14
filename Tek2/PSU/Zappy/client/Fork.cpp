
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include "Fork.hpp"
#include "Errors.hpp"

pid_t EggFork::CreateEgg()
{
	pid_t pid;

	pid = fork();
	if (pid == -1) {
		//je n'arrive pas a compiler avec ce throw :/
		//throw(Exceptions("Can't create the Child process\n"));
	} else if (pid == 0) {
		//Temps d'attente et connection de l'ia
		exit(0);
	}
	return pid;
}
