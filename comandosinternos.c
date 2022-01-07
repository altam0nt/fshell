#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <dirent.h>
#include <unistd.h>
#include "funcoes.h"

int
comando_list(char **s, int n)
{
        DIR *diretorio;
        struct dirent *diret;

        if(s[1] == NULL)
        {
                fprintf(stderr, "%s: digite o nome de um diretório\n", s[0]);
                return 1;
        }
        diretorio = opendir(s[1]);
        if (diretorio == NULL)
                perror("comando_list");

        while ((diret = readdir(diretorio)) != NULL)
                printf("%s\n", diret->d_name);

        closedir(diretorio);
}

int
comando_cd(char **s, int n)
{
        if (n < 2)
                fprintf(stderr, "%s: necessário argumento\n", s[0]);
        else if (chdir(s[1]) != 0)
                perror("comando_cd");
}

int
comando_cls(char **s, int n)
{
        limpar_tela();
}

int
comando_help(char **s, int n)
{
        printf("Digite o nome do programa que deseja executar junto com seus argumentos\n");
}

int
comando_exit(char **s, int n)
{
        exit(EXIT_SUCCESS);
}
