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
#define TAM  2048
#define PERMISSOES 0666
#define FIFO_SERV "server"
#define FIFO_CLI "cliente"
#define B_SIZE (TAM/2)



const char *PUBLIC = "/tmp/PUBLIC";

struct message {
   char fifo_name[B_SIZE];
   char comando[B_SIZE];
};




// fifo_name - guarda o nome do fifo provado que o servidor vai criar ao enviar a resposta para o respetico cliente 
//  comando: e o comando que vai ser executado pelo servidor




