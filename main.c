#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "funcoes.h"
#include "comandosinternos.h"

#define TAMANHOCMD 1024

int
main(int argc, char **argv)
{
	//
	// Declarar as variáveis de controle, buffers e arrays para armazenar os
	// comandos digitados pelo usuário.
	//
	int argcont, i;
	char cmd[TAMANHOCMD];
	char **argumentos;
	bool comando_externo;

	//
	// Definir a variável de controle de comando externo como verdadeira.
	//
	comando_externo = true;

	//
	// Declarar e denifir as variáveis para acessar os comandos internos. 
	//
	char *comandos_internos[] =
	{ 
	  "list",
	  "cd",
	  "cls",
	  "help",
	  "exit"
	};

	typedef int (*funcao_comandos)(char **, int);

	funcao_comandos fcomandos[] = 
	{ 
	  &comando_list,
	  &comando_cd,
	  &comando_cls,
	  &comando_help,
	  &comando_exit
	 };
		 
	//
	// Limpar a tela.
	//
	limpar_tela();

	//
	// Iniciar o loop principal.
	//
	for (;;)
	{
		//	
		// Imprimir o prompt do usuário;
		//
		imprimir_prompt();
	
		//
		// Ler o comando digitado pelo usuário e armazenar o número de
		// argumentos na variável argcont.
		//
		argcont = ler_cmd(cmd);
		if (argcont == 0)
			continue;

		//
		// Armazenar o comando digitado no histórico.
		// 

		//
		// Alocar memória para a array **argumentos e separar os argumentos
		// digitados pelo usuário.
		//
		argumentos = malloc(sizeof(char *) * (argcont + 1));
		if (argumentos == NULL)
			perror("malloc");
		separar_argumentos(argumentos, cmd, argcont);

		//
		// DEBUG
		//
		// for (i = 0; i < argcont; i++)
		//	printf("DEBUG: argumento[%d] %s\n", i, argumentos[i]);

		//
		// Verificar se o comando digitado é um comando interno.
		// Verificar se foi solicitado redirecionamento de I/O.
		// Verificar se foi solicitado PIPE.
		// 

		//
		// Executar o comando digitado.
		//
		for (i = 0; i < (sizeof(comandos_internos) / sizeof(char *)); i++)
			if (strcmp(argumentos[0], comandos_internos[i]) == 0)
			{
				fcomandos[i](argumentos, argcont);
				comando_externo = false;
			}
		if (comando_externo)
			executar(argumentos);
		comando_externo = true;

		//
		// Liberar a memória alocada dinamicamente.
		//
		free(argumentos);
	}
	
	//
	// Não deverá ocorrer. 
	//
	exit(EXIT_FAILURE);
}
