#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <string.h>


int main(){
    int pid,status;
    char in[256];
    bool teste = true;


    while (teste){
        printf("Entre com o caminho a ser procurado: ");
        fgets(in,sizeof(in),stdin);
        in[strcspn(in, "\n")] = '\0';

        if (strcmp(in, "sair") == 0){
            teste = false;
        }
        
        pid = fork();


        if (pid == -1){
            perror("fork falhou");
            exit(-1);
        }else if (pid == 0){
            
        }else {
            wait(&status);
            printf("Eu sou o processo %d, pai de %d\n", getpid(), getppid());
            sleep(1);
            exit(0);
        }
    }

    return 0; 
}

//libera se usa & e espera se não usar &