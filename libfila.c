#include <stdio.h>
#include <stdlib.h>
#include "libfila.h"
/*
 * Cria uma fila vazia e a retorna, se falhar retorna NULL.
 */
fila_t *fila_cria()
{
    fila_t *f;
    f = malloc(sizeof(fila_t));
    if (!f)
        return NULL;
    f->tamanho = 0;
    f->ini = 0;
    f->fim = 0;
    return f;
}

/*
 * Remove todos os elementos da fila, libera espaco e devolve NULL.
 */
fila_t *fila_destroi(fila_t *f)
{
    free(f);
    f = NULL;
    return NULL;
}

/*
 * Retorna 1 se a fila esta vazia e 0 caso contrario.
 */
int fila_vazia(fila_t *f)
{
    if (f->tamanho == 0)
        return 1;
    return 0;
}

/*
 * Retorna o tamanho da fila, isto eh, o numero de elementos presentes nela.
 */
int fila_tamanho(fila_t *f)
{
    return f->tamanho;
}

/*
 * Insere o elemento no final da fila (politica FIFO).
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
 */
int queue(fila_t *f, int elemento)
{
    if (f->tamanho == 0)
    {
        f->ini = (nodo_f_t *)malloc(sizeof(nodo_f_t));
        if (!f->ini)
            return 0;
        f->ini->chave = elemento;
        f->fim = f->ini;
        f->tamanho++;
    }
    else
    {
        f->fim->prox = (nodo_f_t *)malloc(sizeof(nodo_f_t));
        if (!f->fim->prox)
            return 0;
        f->fim->prox->chave = elemento;
        f->fim->prox->prox = NULL;
        f->fim = f->fim->prox;
        f->tamanho++;
    }
    return 1;
}
/*
 * Remove elemento do inicio da fila (politica FIFO) e o retorna.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
 */
int dequeue(fila_t *f, int *elemento)
{
    nodo_f_t *aux;
    if (fila_vazia(f))
        return 0;
    *elemento = f->ini->chave;
    aux = f->ini;
    f->ini = f->ini->prox;
    free(aux);
    f->tamanho--;
    return 1;
}

/*
 * Imprime a fila, do inicio ate o fim, este por ultimo, sem espaco no final.
 * Quando a fila estiver vazia, nao imprime nada, nem um \n.
 * Esta funcao eh somente para facilitar teus testes.
 * Normalmente ela nao existe nas implementacoes de um TAD fila.
 */
void fila_imprime(fila_t *f)
{
    if (!f || fila_vazia(f))
        return;
    nodo_f_t *ptr;
    ptr = f->ini;
    printf("Fila: ");
    for (int i = 0; i < f->tamanho; i++)
    {
        printf("%d ", ptr->chave);
        ptr = ptr->prox;
    }
    printf("\n");
}
