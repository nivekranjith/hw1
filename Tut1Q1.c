#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#include <termios.h>
#include <sys/types.h>
#include <sys/wait.h>

int
foo(int n){
if (n < 2) {
exit(n);
} else {
int v1;
int v2;
pid_t pid = fork();
if (pid == 0)
foo(n - 1);
pid_t pid2 = fork();
if (pid2 == 0)
foo(n - 2);
waitpid(pid,&v1,0);
waitpid(pid2,&v2,0);
exit(WEXITSTATUS(v1) + WEXITSTATUS(v2));
}
}
int
main( void ) {
foo(10);
}
