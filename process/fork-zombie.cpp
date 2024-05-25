/* When fork() is called, it is expected that wait() is called in the 
   parent to get access to the exit code of the child process. 
   A zombie process is a child process that has exited,
   but the parent hasn't called wait() yet. So, the child process
   remains in a zombie state which has basic information about the
   child process (its exit status, etc). Once wait() is called, the
   zombie process exits.
   Here, wait() is never called. However, the zombie process
   will be killed once the parent process exits.

   See: https://en.wikipedia.org/wiki/Zombie_process
*/


#include <iostream>     
#include <unistd.h>    

using namespace std;

int main()
{
	pid_t pid = fork();
	if(pid < 0){
		perror("pipe");
		exit(EXIT_FAILURE);
	}else if(pid == 0)
	{
		cout<<"CHILD process with PID : "<<getpid()<<"\n";
		_exit(EXIT_SUCCESS);
	}else
	{
		cout<<"PARENT Started with pid "<<getpid()<<"\n";
		cout<<"PARENT: Starting infinite loop. Press Ctrl+C to exit.\n";
		cout<<"Use 'ps' to see the zombie process\n";
		while(1)
		{
			sleep(1);
		}
	}
}