/* When fork() is called, it is possible for the parent process to
   exit before a child process. The remaining child process has no
   parent and is therefore an "orphan" process.

   https://en.wikipedia.org/wiki/Orphan_process
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
		cout<<"Child PID : "<<getpid()<<"\n";
		cout<<"Parent PID before becoming orphan "<<getppid()<<"\n";
		sleep(2);
		cout<<"CHILD: I should be an orphan now.\n";
		cout<<"CHILD: My parent pid is "<<getppid()<<"\n";
		_exit(EXIT_SUCCESS);
	}else{
		sleep(1); /* sleep for a second to ensure that child has chance
		             to call getppid() before we exit. */
		printf("PARENT: I'm out of here.\n");
		exit(EXIT_SUCCESS);
	}
}