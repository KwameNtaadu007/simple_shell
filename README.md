The project's goal is to teach the following:

Who designed and implemented the original Unix operating system
Who wrote the first version of the UNIX shell
Who invented the B programming language (the direct predecessor to the C programming language)
Who is Ken Thompson
How does a shell work
What is a pid and a ppid
How to manipulate the environment of the current process
What is the difference between a function and a system call
How to create processes
What are the three prototypes of main
How does the shell use the PATH to find the programs
How to execute another program with the execve system call
How to suspend the execution of a process until one of its children terminates
What is EOF / “end-of-file”?



The original Unix operating system was designed and implemented by a team of programmers at Bell Labs, including Ken Thompson, Dennis Ritchie, and others.

The first version of the Unix shell was written by Ken Thompson.

The B programming language was invented by Ken Thompson in the early 1970s.

Ken Thompson is a computer scientist who is best known for his work on the Unix operating system, the B programming language, and the development of the C programming language with Dennis Ritchie. He received the Turing Award in 1983 for his contributions to computer science.

A shell is a program that provides an interface for users to interact with the operating system. It interprets user commands and executes them as operating system functions or calls to other programs.

A pid (process identifier) is a unique numerical identifier assigned to a process by the operating system. A ppid (parent process identifier) is the pid of the process that created the current process.

The environment of the current process can be manipulated using environment variables, which are key-value pairs that hold information about the system environment. The 'export' command can be used to create or modify environment variables.

A function is a self-contained block of code that performs a specific task and returns a value. A system call, on the other hand, is a request made by a program to the operating system to perform a specific task on its behalf.

Processes can be created using the fork system call, which creates a new process by duplicating the calling process. The exec family of system calls can be used to replace the current process image with a new program.

The three prototypes of the main function in C are:
int main(void);
int main(int argc, char *argv[]);
int main(int argc, char *argv[], char *envp[]);

The shell uses the PATH environment variable to find the location of programs. The PATH variable is a list of directories that the shell searches for programs when a command is entered.

The execve system call is used to execute another program. It replaces the current process image with a new program and provides arguments to the new program.

The wait system call can be used to suspend the execution of a process until one of its children terminates.

EOF (end-of-file) is a special character that indicates the end of a file or input stream. It is commonly used in programming to signal the end of a data stream.
