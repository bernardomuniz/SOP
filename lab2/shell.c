#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <linux/limits.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
 
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
 
int mymkdir(char *pathname){
 
    if (mkdir(pathname, 0700) != 0)
    {
        perror("mkdir() error\n");
        return 1;
    }
   
    return 0;
}
 
int myrmdir(char *pathname){
 
    if (rmdir(pathname) != 0)
    {
        perror("rmdir() error\n");
        return 1;
    }
   
    return 0;
}
 
int mycd(char *pathname){
 
    if (chdir(pathname) == 0)
    {
        printf("Entrou no diretório!\n");
    }else{
        printf("bash: cd: Documento: Arquivo ou diretório inexistente\n");
    }
   
    return 0;
}
 
int myls(char *pathname){
    struct dirent *dir;
    DIR *d;
    int tot_files = 0;
 
    if(pathname == NULL){
        d = opendir(".");
    }else{
        d = opendir(pathname);
    }
   
    if (d == NULL)
    {
        perror("ls");
        return 1;
    }
 
    printf("\n");
    printf("Listando diretório atual: \n\n");
    
    while ((dir = readdir(d)) != NULL)
    {
        printf("%s\n", dir->d_name);
        tot_files++;
    }
    printf("Total de arquivos: %d\n", tot_files - 2);
    printf("\n");
    closedir(d);
 
    return 0;
}
 
int mystat(char *pathname){
    struct stat sb;
    char *namefile = pathname;
 
 
    if(lstat(pathname, &sb) != 0){
        perror("stat");
        return 1;
    }
 
    printf("\n");
    printf("Nome do arquivo:          %s\n", namefile);
    printf("Tamanho do arquivo:       %ld bytes\n", sb.st_size);
    printf("Último acesso ao arquivo:        %s", ctime(&sb.st_atime));
    printf("Última modificação ao arquivo:   %s", ctime(&sb.st_mtime));
    printf("\n");
 
    return 0;
}

void myhelp(){
    printf("\n=========== AJUDA DO SHELL ===========\n");
    printf("Comandos disponíveis:\n\n");

    printf("  cwd      - Mostra o diretório atual.\n");
    printf("  mkdir    - Cria um novo diretório.\n");
    printf("  rmdir    - Remove um diretório existente.\n");
    printf("  ls       - Lista o conteúdo de um diretório.\n");
    printf("  stat     - Exibe informações detalhadas de um arquivo.\n");
    printf("  help     - Mostra esta tela de ajuda.\n");
    printf("  exit     - Encerra o shell.\n");

    printf("\n======================================\n");
}
 
int main(int argc, char **argv){
    bool teste = true;
   
    while (teste)
    {
        char in[256];
        printf("[myshell]> ");
        fgets(in, sizeof(in), stdin);
 
        char *command = strtok(in, " ");
        char *pathname = strtok(NULL, "\n");
 
        if(strcmp(command, "\n") == 0){
            continue;
        }
        in[strcspn(in, "\n")] = '\0';
 
 
        if (strcmp(in, "exit") == 0)
        {
            teste = false;
        }else if (strcmp(in, "cwd") == 0)
        {
            mycwd();
        }else if (strcmp(in, "mkdir") == 0)
        {
            mymkdir(pathname);
        }else if (strcmp(in, "rmdir") == 0)
        {
            myrmdir(pathname);
        }else if (strcmp(in, "ls") == 0)
        {
            myls(pathname);
        }else if (strcmp(in, "stat") == 0)
        {
            mystat(pathname);
        }else if (strcmp(in, "cd") == 0)
        {
            mycd(pathname);
        }
        else if (strcmp(in, "myhelp") == 0)
        {
            myhelp();
        }
        else{
            printf("Comando inválido!\n");
        }
    }
 
    return 0;
}