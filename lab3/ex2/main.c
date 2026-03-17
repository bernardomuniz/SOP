// Investigue WIFEXITED(status) e WEXITSTATUS(status) e modifique o exercício anterior para calcular
// 5!, com cada processo realizando uma multiplicação e retornando o resultado parcia

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    int pid,status;
    int resp = 1;
    int i = 5;

    while (i > 0)
    {
        pid = fork();

        if (pid == -1){
            perror("fork falhou");
            exit(-1);
        }else if (pid == 0){
            resp *= i;
            return resp;
        }else{
            wait(&status);
            if (WIFEXITED(status)){
                resp = WEXITSTATUS(status);
                i--;
            }
        }

    }

    printf("5! = %d\n", resp);
    return 0;
}


//filho tem que retornar a multiplicação e o pai tem que pegar a resposta do filho