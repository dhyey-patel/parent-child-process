#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char **argv)
{
	/************************************************** command line arguments ***********************************************
		For the purposes of this explanation, assume that "external_program.out" is located in /home/usr/A1/external_program.out 

		When you are testing your program, replace "/home/usr/A1/external_program.out" with the path to the executable file 
		generated when you compile "external_program.c"
		
		To compile assignment1.c: gcc assignment1.c -o assignment1
		To run your program: ./assignment1 /home/usr/A1/external_program.out
		argv[0] = "./assignment1"
		argv[1] = "/home/usr/A1/external_program.out"

		Number of arguments (argc) = 2

		In this assignment, the path to the external program is in argv[1]
	*************************************************************************************************************************/

	// If the path of external_program.out isn't provided by the user, the program will terminate
	if (argc != 2)
	{
		printf("Invalid arguments\n");
		exit(0);
	}

	// You must insert the following into your code (Replace zeros with the appropriate values/variables)
	/*
	printf("parent process (PID %d) created child_1 (PID %d) \n", 0, 0);
	printf("parent (PID %d) is waiting for child_1 (PID %d) to complete before creating child_2\n", 0, 0);
	printf("child_1 (PID %d) created child_1.1 (PID %d)\n", 0, 0);
	printf("child_1 (PID %d) is now complete\n", 0);
	printf("parent (PID %d) created child_2 (PID %d)\n", 0, 0);
	printf("child_2 (PID %d) is calling an external program external_program.out and leaving child_2..\n", 0);
	*/
	// Hint: You might find snprintf() helpful in this assignment



	/***************************************************************************************************
	 * 										 YOUR CODE GOES HERE										
	 ***************************************************************************************************/
	pid_t pid1, pid2;
	
	// Execute the first fork
	pid1 = fork();

	// If we are inside the parent
	if (pid1 > 0){
		printf("parent process (PID %d) created child_1 (PID %d) \n", getpid(), pid1);
		printf("parent (PID %d) is waiting for child_1 (PID %d) to complete before creating child_2\n", getpid(), pid1);
		wait(NULL);		
	}

	// Execute the second fork
	pid2 = fork();
	//If we are in child 1
	if (pid1 == 0){
		// If we are in child 1.1
		if (pid2 == 0){
			printf("child_1 (PID %d) created child_1.1 (PID %d)\n", getppid(), getpid());
		} else{
			wait(NULL);
			printf("child_1 (PID %d) is now complete\n", getpid());
		}
	} 
	
	// Only excecute if you are not in child 1 (This code wont be excecuted for child 1.1)
	else{
		// If you are in child 2
		if(pid2 == 0){
			//convert the pid of child 2 to string to pass through the execl function
			char strPID[8];
			sprintf(strPID, "%d", getpid());
			execl(argv[1],argv[1], strPID, NULL);
		} else{
			printf("parent (PID %d) created child_2 (PID %d)\n", getpid(), pid2);
			wait(NULL);
		}
	}

	return 0;
}
