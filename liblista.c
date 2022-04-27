#include <stdio.h>
#include <stdlib.h>
#include "liblista.h"

/*
 * Cria uma lista vazia e a retorna, se falhar retorna NULL.
 */
lista_t *lista_cria()
{
    lista_t *l;
    l = malloc(sizeof(lista_t));
    if (!l)
        return NULL;
    l->tamanho = 0;
    l->ini = NULL;
    return l;
}

/*
 * Remove todos os elementos da lista, libera espaco e retorna NULL.
 */
lista_t *lista_destroi(lista_t *l)
{
    free(l);
    l = NULL;
    return NULL;
}

/*
 * Retorna 1 se a lista esta vazia e 0 caso contrario.
 */
int lista_vazia(lista_t *l)
{
    if (l->tamanho == 0)
        return 1;
    return 0;
}
/*
 * Retorna o tamanho da lista, isto eh, o numero de elementos presentes nela.
 */
int lista_tamanho(lista_t *l)
{
    return l->tamanho;
}

/*
 * Insere o elemento no inicio da lista.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
 */
int lista_insere_inicio(lista_t *l, int elemento)
{
    nodo_l_t *aux = malloc(sizeof(nodo_l_t));
    if (!aux)
        return 0;
    if (lista_vazia(l))
    {
        l->ini = malloc(sizeof(lista_t));
        l->ini->elemento = elemento;
        l->tamanho++;
        return 1;
    }
    aux->elemento = elemento;
    aux->prox = l->ini;
    l->ini = aux;
    l->tamanho++;
    return 1;
}

/*
 * Insere o elemento no final da lista.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
 */
int lista_insere_fim(lista_t *l, int elemento)
{
    nodo_l_t *aux = malloc(sizeof(nodo_l_t));
    if (!aux)
        return 0;
    if (lista_vazia(l))
    {
        l->ini = malloc(sizeof(lista_t));
        l->ini->elemento = elemento;
        l->tamanho++;
        return 1;
    }
    int i;
    aux = l->ini;
    for (i = 1; i < l->tamanho; i++)
    {
        aux = aux->prox;
    }
    nodo_l_t *novo = malloc(sizeof(nodo_l_t));
    if (!novo)
        return 0;
    novo->elemento = elemento;
    aux->prox = novo;
    l->tamanho++;
    return 1;
}

/*
 * Insere o elemento na lista garantindo ordenacao em ordem crescente.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
 */
int lista_insere_ordenado(lista_t *l, int elemento)
{
    nodo_l_t *aux = malloc(sizeof(nodo_l_t));
    nodo_l_t *anterior = malloc(sizeof(nodo_l_t));
    nodo_l_t *novo = malloc(sizeof(nodo_l_t));
    int i;
    aux = l->ini;
    for (i = 1; i <= l->tamanho; i++)
    {
        if (aux->elemento > elemento)
        {
            novo->elemento = elemento;
            anterior->prox = novo;
            novo->prox = aux;
            l->tamanho++;
            return 1;
        }
        anterior = aux;
        aux = aux->prox;
    }

    return 0;
}

/*
 * Remove o elemento do inicio da lista e o retorna em 'elemento'.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
 */
int lista_retira_inicio(lista_t *l, int *elemento)
{
    if (lista_vazia(l))
        return 0;
    *elemento = l->ini->elemento;
    l->ini = l->ini->prox;
    l->tamanho--;
    return 1;
}

/*
 * Remove o elemento do final da lista e o retorna em 'elemento'.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
 */
int lista_retira_fim(lista_t *l, int *elemento)
{
    nodo_l_t *aux = malloc(sizeof(nodo_l_t));
    if (!aux || lista_vazia(l))
        return 0;
    int i;
    aux = l->ini;
    for (i = 1; i < l->tamanho; i++)
    {
        aux = aux->prox;
    }
    *elemento = aux->elemento;
    aux->prox = aux;
    l->tamanho--;
    return 1;
}

/*
 * Remove o elemento 'elemento' caso ele exista na lista.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
 * Se o elemento nao for encontrado na lista tambem retorna 0.
 */
int lista_retira_elemento(lista_t *l, int *elemento)
{
    nodo_l_t *aux = malloc(sizeof(nodo_l_t));
    nodo_l_t *anterior = malloc(sizeof(nodo_l_t));
    int i;
    aux = l->ini;
    anterior = aux;
    for (i = 1; i < 2; i++)
    { /*para o primeiro elemento*/
        if (l->ini->elemento == *elemento)
        {
            l->ini = l->ini->prox;
            l->tamanho--;
            return 1;
        }
        for (i = 1; i <= l->tamanho; i++)
        {
            if (aux->elemento == *elemento)
            {
                anterior->prox = aux->prox;
                l->tamanho--;
                return 1;
            }
            anterior = aux;
            aux = aux->prox;
        }
        return 0;
    }
}

/*
 * Retorna 1 se o elemento existe na lista e 0 caso contrario.
 */
int lista_pertence(lista_t *l, int elemento)
{
    nodo_l_t *aux = malloc(sizeof(nodo_l_t));
    int i;
    aux = l->ini;
    for (i = 1; i <= l->tamanho; i++)
    {
        if (aux->elemento == elemento)
        {
            return 1;
        }
        aux = aux->prox;
    }
    return 0;
}

/*
 * Imprime a lista, do inicio ate o fim, este por ultimo, sem espaco no final.
 * Quando a lista estiver vazia, nao imprime nada, nem um \n.
 * Esta funcao eh somente para facilitar teus testes.
 * Normalmente ela nao existe nas implementacoes de um TAD lista.
 */
void lista_imprime(lista_t *l)
{
    if (!l || lista_vazia(l))
        return;
    nodo_l_t *ptr;
    ptr = l->ini;
    printf("Lista: ");
    for (int i = 0; i < l->tamanho; i++)
    {
        printf("%d ", ptr->elemento);
        ptr = ptr->prox;
    }
    printf("\n");
}
