#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <linux/limits.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>

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
    char in[256];
    scanf("%s", in);

    if (chdir(in) == 0)
    {
        printf("Entrou no diretório!\n");
    }else{
        printf("bash: cd: Documento: Arquivo ou diretório inexistente\n");
    }
    
    return 0;
}

int myls(){
    struct dirent *dir;
    DIR *d;
    d = opendir(".");

    if (d == NULL)
    {
        perror("ls");
        return 1;
    }

    while ((dir = readdir(d)) != NULL)
    {
        printf("%s\n", dir->d_name);
    }
    closedir(d);

    return 0;
}

int mystat(){



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