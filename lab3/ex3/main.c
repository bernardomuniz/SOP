//Implemente um terminal que leia caminhos completos de programas e execute-os usando fork() e
//execve(). Utilize wait() ou não dependendo se o comando termina com &. O laço deve continuar
//até que o usuário digite sair.

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <string.h>


int main(){
    int pid;
    char in[256];
    bool teste = true;
    bool background = false;



    while (teste){
        printf("\nEntre com o comando: ");
        fgets(in,sizeof(in),stdin);
        in[strcspn(in, "\n")] = '\0';

        if (strcmp(in, "sair") == 0){
            teste = false;
        }

        char ultimo = in[strlen(in) - 1];


        if(ultimo == '&' && strlen(in) > 0){
            background = true;
            in[strlen(in) - 1] = '\0';
        }

        pid = fork();
        
        if (pid == -1) {
            perror("fork falhou!");
            exit(-1);
        }else if(pid == 0){
            char *args[] = {in, NULL}; 
            execvp(in, args);
            perror("Erro ao executar execvp");
            exit(-1);
        }else{
             // pai
            if (!background) {
                wait(NULL); // foreground
            } else {
                printf("Processo rodando em background (PID: %d)\n\n", pid);
            }
        }
        
        
    }

    return 0; 
}

//libera se usa & e espera se não usar &