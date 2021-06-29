
#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <time.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include "message.h"

#define TAM  2048
#define PERMISSOES 0666
#define B_SIZE (TAM/2)

/*
Como funcina o servidor
  [1]  Gera um FIFO Publico que abre em read e write. 
  [2]  Fica a espera de um processo Cliente
  [3]  Lê a mensagem recebida plo FIFO Publico.
  [4]  Abre o FIFO Privado do cliente em modo de escrita.
  [5]  Executa o comando do Cliente com popen.
  [6]  Escreve o output no FIFO Privado do cliente.
*/

int main() {

int pipe_fd;
int privatefifo, dummyfifo, publicfifo, n, done;
struct message msg;
char buffer[TAM];
pid_t p; 



/* [1] 
  Gera um FIFO Publico que abre em read e write.
*/
mkfifo(PUBLIC, S_IFIFO | 0666);

/* [2]
O dummyfifo e para nao termo s de andar sempre a fechar e abrir um fifo sempre que um client se vai embora 
Fica a espera de um processo Cliente
*/
if( (publicfifo = open(PUBLIC, O_RDONLY)) < 0 ||
 (dummyfifo = open(PUBLIC, O_WRONLY | O_NDELAY)) < 0) {
   perror(PUBLIC);
   exit(1);
}

/*
 [3]  Lê a mensagem recebida pelo FIFO Publico.
*/

while(read(publicfifo, &msg, sizeof(msg)) > 0) {

n=0;
done=0;




do {
  /* 
  [4]  Abre o FIFO Privado do cliente em modo de escrita.
  */

  if ( (p = fork())<0 )
             printf("fork Failed"); 

  if ( p == 0 ){

            printf("CHILD\n");     


if ( (privatefifo = open(msg.fifo_name, O_WRONLY|O_NDELAY)) == -1) {
    sleep(5);
  }


  write(fileno(stdout), msg.comando, 8 ); //teste

    


      /* 
      [5]  Executa o comando do Cliente e envia resposta.
       */
  write(privatefifo, msg.comando , B_SIZE); 


    printf("CHILD2\n"); 


    if (privatefifo==-1)
        {
            printf("erro");
            exit(EXIT_FAILURE);
        }
        printf("CHILD3\n");  

    exit(EXIT_SUCCESS);
    }



    


  
  /* 
     [6]  Escreve o output no FIFO Privado do cliente.
  */

  

    
    close(privatefifo);
  


    done = 1;
  }

while(!done);
}

if(!done) {
  perror("Not accessed the private fifo\n");
  exit(1);


}
return 0;}
