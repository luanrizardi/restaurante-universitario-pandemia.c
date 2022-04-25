/*
 * TAD fila
 * Autores:
 *    André Ricardo Abed Gregio
 *    Marcos Alexandre Castilho
 *    Luis Carlos Erpen de Bona
 *    Luiz Carlos Pessoa Albini
 *
 * Versao 1.0.0 de 04/04/2022
*/

#ifndef _LIBfila_t_H
#define _LIBfila_t_H

struct nodo_f {
    int chave;            /* fila de numeros inteiros */
    struct nodo_f *prox;  /* ponteiro para o proximo  */
};
typedef struct nodo_f nodo_f_t;

struct fila {
    nodo_f_t* ini;        /* ponteiro para o inicio da lista */
    nodo_f_t* fim;        /* ponteiro para o fim da lista    */
    int tamanho;          /* numero de elementos na lista    */
};
typedef struct fila fila_t;

/*
 * Cria uma fila vazia e a retorna, se falhar retorna NULL.
*/
fila_t* fila_cria ();

/*
 * Remove todos os elementos da fila, libera espaco e devolve NULL.
*/
fila_t* fila_destroi (fila_t* f);

/*
 * Retorna 1 se a fila esta vazia e 0 caso contrario.
*/
int fila_vazia (fila_t* f);

/*
 * Retorna o tamanho da fila, isto eh, o numero de elementos presentes nela.
*/
int fila_tamanho (fila_t* f);

/*
 * Insere o elemento no final da fila (politica FIFO).
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
*/
int queue (fila_t* f, int elemento);

/*
 * Remove elemento do inicio da fila (politica FIFO) e o retorna.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
*/
int dequeue (fila_t* f, int* elemento);

/*
 * Imprime a fila, do inicio ate o fim, este por ultimo, sem espaco no final.
 * Quando a fila estiver vazia, nao imprime nada, nem um \n.
 * Esta funcao eh somente para facilitar teus testes.
 * Normalmente ela nao existe nas implementacoes de um TAD fila.
*/
void fila_imprime (fila_t* f);

#endif
