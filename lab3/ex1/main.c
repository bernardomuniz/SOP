// Implemente um programa que crie uma árvore de 3 processos com chamadas encadeadas de fork().
// Cada processo deve imprimir "Eu sou o processo XXX, filho de YYY"usando getpid() e getppid(),
// e os wait() devem garantir a ordem: C antes de B, B antes de A. Use sleep(1) entre as mensagens.
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

//neto, filho, pai

int main(){
    int pid, pid2,status;

    //processo A
    pid = fork();

    if (pid == -1)
    {
        perror("fork falhou");
        exit(-1);
    }else if (pid == 0){ //código executado pelo filho
    
        pid2 = fork();
        if (pid2 == -1){ 
            perror("fork falhou");
            exit(-1); 
        }else if (pid2 == 0){ //código executado pelo neto
            printf("Eu sou o processo %d, neto de %d\n", getpid(), getppid());
        }else{//código executado pelo filho (pai do neto)
            wait(&status);
            printf("Eu sou o processo %d, filho de %d\n", getpid(), getppid());
            sleep(1);
        }
        
    }else {//ultimo a ser impresso
        wait(&status);
        printf("Eu sou o processo %d, pai de %d\n", getpid(), getppid());
        sleep(1);
        exit(0);
    }

    return 0;
}