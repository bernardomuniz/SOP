#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <linux/limits.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>


//man 3 cwd
int mycwd(){
    char cwd[PATH_MAX];

    if (getcwd(cwd, sizeof(cwd)) != 0){
        printf("%s\n", cwd);
    }else{
        perror("getcwd() error\n");
        return 1;
    }
    return 0;
}

int mymkdir(){

    char pathname[256];
    scanf("%s", pathname);
    if (mkdir(pathname, 0700) != 0)
    {
        perror("mkdir() error\n");
        return 1;
    }
    
    return 0;
}

int myrmdir(){
    char pathname[256];
    scanf("%s", pathname);

    if (rmdir(pathname) != 0)
    {
        perror("rmdir() error\n");
        return 1;
    }
    
    return 0;
}

int mycd(){
    return 0;
}

int mystat(){
    return 0;
}

int myls(){
    struct dirent *dir;
    DIR *d;

    char in[256];
    printf("Diretório a listar: ");
    scanf("%s", in);

    d = opendir(in);
    if (d != NULL){
        while ((dir = readdir(d)) != NULL)
        {
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    }else{

        printf("Diretório %s não encontrado!\n", in);
    }
    
    return 0;
}


int main(int argc, char **argv){
    bool teste = true;
    
    while (teste)
    {
        char in[256];
        printf("shell$ ");
        scanf("%s", in);
        
        if (strcmp(in, "exit") == 0)
        {
            teste = false;
        }else if (strcmp(in, "cwd") == 0)
        {
            mycwd();
        }else if (strcmp(in, "mkdir") == 0)
        {
            mymkdir();
        }else if (strcmp(in, "rmdir") == 0)
        {
            myrmdir();
        }else if (strcmp(in, "ls") == 0)
        {
            myls();
        }else if (strcmp(in, "stat") == 0)
        {
            mystat();
        }else if (strcmp(in, "cd") == 0)
        {
            mycd();
        }
        
        else{

            printf("Comando inválido!\n");
        }
        
    }
    

    return 0;
}