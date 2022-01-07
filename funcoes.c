#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/wait.h>
#include "funcoes.h"

void
limpar_tela(void)
{
        if (write(STDOUT_FILENO, "\e[1;1H\e[2J", 10) != 10)
                perror("limpar_tela");
}

void
imprimir_prompt(void)
{
        struct passwd *usuario;
        char host[256];
        char diretorio[256];

        usuario = getpwuid(getuid());
        if (usuario == NULL)
                perror("imprimir_prompt");

        if (gethostname(host, sizeof host) == -1)
                perror("imprimir_prompt");

        if (getcwd(diretorio, sizeof diretorio) == NULL)
                perror("imprimir_prompt");

        printf("%s@%s:%s%%> ", usuario->pw_name, host, diretorio);
}

int
ler_cmd(char *s)
{
        int c, contador, contadorarg;
        bool dentro;

        contadorarg = contador = 0;

        dentro = false;

        while ((c = getchar()) != EOF && c != '\n')
        {
                if (c == ' ' || c == '\t')
                {
                        s[contador] = c;
                        dentro = false;
                }
                else if (!dentro)
                {
                        s[contador] = c;
                        dentro = true;
                        contadorarg++;
                }
                else
                        s[contador] = c;

                contador++;
        }

        s[contador] = '\0';

        return contadorarg;
}

void
separar_argumentos(char **s, char *t, int n)
{
        int i;

        s[0] = strtok(t, " ");

        for (i = 1; i < n; i++)
                if ((s[i] = strtok(NULL, " ")) != NULL)
                        continue;
                else
                        break;

        s[i] = NULL;
}

void
executar(char **s)
{
        pid_t pid;
        int status;

        if ((pid = fork()) < 0)
                perror("executar_comando");
        else if (pid == 0)
        {
                (execvp(s[0], s));

                perror("executar_comando");
                exit(EXIT_FAILURE);
        }

        if ((pid = waitpid(pid, &status, 0)) < 0)
                perror("executar_comando");
}

