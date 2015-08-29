#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#include <termios.h>
#include <sys/types.h>
#include <sys/wait.h>

#define FALSE 0
#define TRUE 1
#define INPUT_STRING_SIZE 80

#include "io.h"
#include "parse.h"
#include "process.h"
#include "shell.h"
#include "paths.h"


struct process process1 ;

char cwd[1024] ;

int cmd_quit(tok_t arg[]) {
  printf("Bye\n");
  exit(0);
  return 1;
}

int cmd_help(tok_t arg[]);


int cmd_cd(tok_t arg[])
{
 
  if  (chdir(arg[0]) ==0)
   {
      getcwd(cwd,sizeof(cwd));

    }
else
{
   fprintf(stdout, "%s Error\n") ;
}
  
   return 1 ;
     
}


/* Command Lookup table */
typedef int cmd_fun_t (tok_t args[]); /* cmd functions take token array and return int */
typedef struct fun_desc {
  cmd_fun_t *fun;
  char *cmd;
  char *doc;
} fun_desc_t;

fun_desc_t cmd_table[] = {
  {cmd_help, "?", "show this help menu"},
  {cmd_quit, "quit", "quit the command shell"},
  {cmd_cd, "cd" , "change working directory"},
};

int cmd_help(tok_t arg[]) {
  int i;
  for (i=0; i < (sizeof(cmd_table)/sizeof(fun_desc_t)); i++) {
    printf("%s - %s\n",cmd_table[i].cmd, cmd_table[i].doc);
  }
  return 1;
}


int lookup(char cmd[]) {
  int i;
  for (i=0; i < (sizeof(cmd_table)/sizeof(fun_desc_t)); i++) {
    if (cmd && (strcmp(cmd_table[i].cmd, cmd) == 0)) return i;
  }
  return -1;
}

void init_shell()
{
  /* Check if we are running interactively */
  shell_terminal = STDIN_FILENO;

  /** Note that we cannot take control of the terminal if the shell
      is not interactive */
  shell_is_interactive = isatty(shell_terminal);

  if(shell_is_interactive){

    /* force into foreground */
    while(tcgetpgrp (shell_terminal) != (shell_pgid = getpgrp()))
      kill( - shell_pgid, SIGTTIN);

    shell_pgid = getpid();
    /* Put shell in its own process group */
    if(setpgid(shell_pgid, shell_pgid) < 0){
      perror("Couldn't put the shell in its own process group");
      exit(1);
    }

    /* Take control of the terminal */
    tcsetpgrp(shell_terminal, shell_pgid);
    tcgetattr(shell_terminal, &shell_tmodes);
  }
  /** YOUR CODE HERE */

   
}

/**
 * Add a process to our process list
 */
void add_process(process* p)
{
  
    
  

}

/**
 * Creates a process given the inputString from stdin
 */
process* create_process(char* inputString)
{
 
}



int shell (int argc, char *argv[]) {
  char *s = malloc(INPUT_STRING_SIZE+1);			/* user input string */
  tok_t *t;
  tok_t *b ;			/* tokens parsed from input */
  int lineNum = 0;
  int fundex = -1;
  pid_t pid = getpid();		/* get current processes PID */
  pid_t ppid = getppid();	/* get parents PID */
  pid_t cpid, tcpid, cpgid;

  init_shell();

  printf("%s running as PID %d under %d\n",argv[0],pid,ppid);
 
//char* cwd ;
long size ;



size = pathconf(".",_PC_PATH_MAX) ;
  getcwd(cwd,sizeof(cwd)) ;

  lineNum=0;
  fprintf(stdout, "%d: ", lineNum );
 fprintf(stdout, "%s ", cwd) ;
  while ((s = freadln(stdin))){
   
    t = getToks(s); /* break the line into tokens */
   b = getToksB(s) ;
    fundex = lookup(t[0]); /* Is first token a shell literal */
    if(fundex >= 0) cmd_table[fundex].fun(&t[1]);
    else {
     cpid  = fork() ;
    //int status ;

   



      int i=0 ;
      int countWord = 0 ;
      
       while(t[i] != NULL)
       {
        
         countWord++ ;
         i++ ;
       
       }

     
      
         char* test[countWord] ;

      int j =0 ;
      for(j; j<= countWord ;j++)
       {
         
       //  countWord++ ;
        test[j] = t[j] ;
       }


  
        if(pid==0)// parent
          {

    process process1 ;
     process1.next ;
     process1.pid = getpid() ;
       wait(&process1.status) ;
           fprintf(stdout,"parent\n") ;

        if(WIFSTOPPED(process1.status) != 0)
    {
          process1.stopped = 'T' ;
    }
        else
          process1.stopped = 'F' ;
    
    
if(WIFEXITED(process1.status) != 0)
 process1.completed = 'T' ;
else
process1.completed = 'F' ;
               


           }
        else if(pid>0)
            {
              

                 if(countWord==2)
                     {
                       execv(t[0], test);  
                    //    fprintf(stdout,"child1\n");
                       }
                  else if(countWord ==1){
                  execlp(test[0],test) ;
                  }
                  else if(countWord==3)
                    {  char *c ; int k=0 ; int l=0 ;
                        

                        if(strcmp(test[1],">")==0)
                             {
                                    
                              FILE *f = fopen(test[2], "w");
                            dup2(fileno(f), STDOUT_FILENO) ;
                               fclose(f) ;                             

                               execv(t[0], test); 
                                                                           
                              }

                         if(strcmp(test[1],"<")==0)
                             {
                                 char *s1 = malloc(INPUT_STRING_SIZE+1);
                                 FILE *f = fopen(t[2], "r");
                                    if(f==NULL)
                                  {
                                      fprintf(stdout, "Error reading file\n") ;
                               }
                                else{

                                  while (s1 = freadln(f))
                                {

                                   tok_t *t1;
                                   t1 = getToks(s1);
                                    fprintf(stdout, t1[1]) ; 



                                 int i1=0 ;
                                int countWord1 = 0 ;
      
                                 while(t1[i1] != NULL)
                                   {
        
                                   countWord1++ ;
                                    i1++ ;
       
                                      }

     
      
                                char* test1[countWord1] ;

                                int j1 =0 ;
                                 test1[0]= test[0] ; 
                               for(j1; j1<= countWord1+1 ;j1++)
                                  {
         
       
                                   test1[j1+1] = t1[j1] ;
                                      }


                                   execv(t[0], test1);
                                      
                                 }
                            
                                    }

                                 
                                    

                                }
                                  
                       }
                   else if(countWord==4)
                    {  char *c ; int k=0 ; int l=0 ;
                        

                        if(strcmp(test[2],">")==0)
                             {
                                    
                              FILE *f = fopen(test[3], "w");
                            dup2(fileno(f), STDOUT_FILENO) ;
                               fclose(f) ;                             

                               execv(t[0], test); 
                                                                           
                              }

                       }
                  
                 }
               

          
        else if(pid<0)
            {fprintf(stdout,"problems\n") ;}

             
    }
     lineNum = lineNum + 1 ;
    fprintf(stdout, "%d: ", lineNum);

fprintf(stdout, "%s ", cwd) ;

  }
  return 0;
free (cwd) ;
}
