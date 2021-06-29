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
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "message.h"
#define TAM  2048
#define PERMISSOES 0666


#define B_SIZE (TAM/2)

/*
Passos que o Client vai ter.
  [1]  criar um nome unicao para o seu FIFO Privado e invoca-lo
  [2]  Abrir um FIFO Publico para escrever para o servidor.
  [3]  Esperar e receber comando do utilizador.
  [4]  escreve o comando no FIFO Publico para o servidor processar.
  [5]  Abrir o FIFO Privado em modo de leitura para ler a resposta do servidor.

*/

int main()
{
printf("Inicia app \n");

int publicfifo, privatefifo, n;
char buffer[TAM];
struct message msg;

  
/*   [1.1]
tou a usar sprintf to para criar um nome unico do fifo com o getpid que vai usar o Id do processo

*/

sprintf(msg.fifo_name, "/tmp/fifo%d", getpid());

/*  [1.2]
invoca fifo Privado*/
if(mkfifo(msg.fifo_name, S_IFIFO | PERMISSOES) < 0) {
  perror(msg.fifo_name);
  exit(1);
}

/*  [2]  
Abrir um FIFO Publico para escrever para o servidor. (este so escreve)
*/
if((publicfifo = open(PUBLIC,O_WRONLY)) < 0) {
  unlink(msg.fifo_name);
  perror(PUBLIC);
exit(1);
}
/*  [3]
    Esperar e receber comando do utilizador.
*/

while(1) {

  write(fileno(stdout), "\n cmd>", 6);
  memset(msg.comando, 0x0, B_SIZE);
  n = read(fileno(stdin), msg.comando, B_SIZE);

if(strncmp("quit", msg.comando, n-1) == 0) {
  break;
}

/*  [4]
   escreve o comando no FIFO Publico para o servidor processar.
*/

write(publicfifo, &msg, sizeof(msg));

write(fileno(stdout),msg.comando,B_SIZE);  // teste


if((privatefifo = open(msg.fifo_name, O_RDONLY)) < 0) {
  printf("1\n");
  perror(msg.fifo_name);
  write(fileno(stdout), "\n cen>", 6);
  goto CLEANUP;
}




/*  [5]
    Abrir o FIFO Privado em modo de leitura para ler a resposta do servidor.
*/

while((n = read(privatefifo, buffer, TAM)) > 0) {
  write(fileno(stdout), buffer, n);
  write(fileno(stdout), "\n ack>", 6);
}


close(privatefifo);
}
CLEANUP:
close(publicfifo);
unlink(msg.fifo_name);

return 0;
}


