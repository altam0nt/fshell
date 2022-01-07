#ifndef FUNCOES_H
#define FUNCOES_H

void limpar_tela(void);
void imprimir_prompt(void);
int  ler_cmd(char *s);
void separar_argumentos(char **s, char *t, int n);
void executar(char **s);

#endif
