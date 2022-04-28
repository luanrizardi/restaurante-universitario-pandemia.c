#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "liblista.h"
#include "libfila.h"
#include "libpilha.h"
#include <math.h>

typedef struct
{
    int ticket; /* identifica pessoa na fila */
    int vacina; /* 0 - n vacinado , 1 - vacinado */
    int masc;   /* 0 - sem mascara , 1 - com mascara */
    float dinheiro; /* 1.30 ou 3.80 */
} pessoa_t;

typedef struct
{
    double mascara;  /* dinheiro em mascara */
    double refeicao; /* dinheiro em refeicao */
} din_t;

pessoa_t **pessoa_cria(int x)
{

    int i;
    pessoa_t **pessoa;
    pessoa = malloc(x * sizeof(pessoa_t *));
    if (!pessoa)
        return NULL;
    for (i = 0; i < x; i++)
        pessoa[i] = malloc(sizeof(pessoa_t));

    srand(time(NULL));
    int z = 0;
    for (i = 0; i < x; i++)
    {
        pessoa[i]->ticket = z;
        pessoa[i]->vacina = rand() % 2;
        pessoa[i]->masc = rand() % 2;
        int x = 1 + (rand() % 10);
        if (x <= 6)
            pessoa[i]->dinheiro = 1.30;
        else
            pessoa[i]->dinheiro = 3.80;

        z++;
    }

    return pessoa;
}

din_t *din_cria()
{
    din_t *din;
    din = malloc(sizeof(din_t));
    din->refeicao = 0;
    din->mascara = 0;
    return din;
}

int main()
{

    srand(time(NULL));
    int x = 1 + (rand() % 100);
    int y = 500 + (rand() % 500);
    int z = 1000;
    int aux;

    // 1 E 2

    pilha_t *pilha_masc = pilha_cria(x);
    pilha_t *pilha_ref = pilha_cria(y);
    pessoa_t **pessoa = pessoa_cria(z);
    din_t *din = din_cria();
    int i;
    for (i = 0; i < x; i++)
        push(pilha_masc, i);

    for (i = 0; i < y; i++)
        push(pilha_ref, i);

    // 4
    fila_t *fila = fila_cria();
    for (i = 0; i < 1000; i++)
        queue(fila, pessoa[i]->ticket);

    // 5
    lista_t *lista = lista_cria();
    i = 0;

    printf("tamanho ref: %d \n", pilha_tamanho(pilha_ref));

    while (!fila_vazia(fila) && !pilha_vazia(pilha_ref))
    {
        // se não esta vacinada
        if (pessoa[fila->ini->chave]->vacina == 0)
        {
            lista_insere_fim(lista, pessoa[fila->ini->chave]->ticket);
            //printf("ticket 1: %d \n", pessoa[fila->ini->chave]->ticket);
            dequeue(fila, &aux);
        }
        // se esta com mascara
        else if (pessoa[fila->ini->chave]->masc == 1 && !pilha_vazia(pilha_ref))
        {
            //printf("ticket 2: %d \n", pessoa[fila->ini->chave]->ticket);
            pessoa[fila->ini->chave]->dinheiro = pessoa[fila->ini->chave]->dinheiro - 1.30;
            din->refeicao = din->refeicao + 1.30;
            dequeue(fila, &aux);
            pop(pilha_ref);
        }
        else if (!pessoa[fila->ini->chave]->vacina == 0 && pessoa[fila->ini->chave]->dinheiro >= 2.50 && !pilha_vazia(pilha_masc)) //&& pessoa[fila->ini->chave]->vacina == 1)
        {
            //printf("ticket 3: %d \n", pessoa[fila->ini->chave]->ticket);
            pessoa[fila->ini->chave]->dinheiro = pessoa[fila->ini->chave]->dinheiro - 2.50;
            din->mascara = din->mascara + 2.50;
            pessoa[fila->ini->chave]->masc = 1;
            queue(fila, pessoa[fila->ini->chave]->ticket);
            dequeue(fila, &aux);
        }    
            // acabarama as mascaras ou nao tem dinheiro
        else
        {
            //printf("ticket 4: %d \n", pessoa[fila->ini->chave]->ticket);
            lista_insere_fim(lista, pessoa[fila->ini->chave]->ticket);
            dequeue(fila, &aux);
        }
        
        // fila_imprime(fila);
    }
    // fila_destroi(fila);

    printf("Dinheiro ganho com refeição: %f \n", din->refeicao);
    printf("Dinheiro ganho com mascara: %f \n", din->mascara);
    printf("Dinheiro ganho total: %f \n", din->mascara + din->refeicao);

    lista_imprime(lista);
    printf("tamanho da lista: %d \n", lista_tamanho(lista));
    printf("tamanho ref: %d \n", pilha_tamanho(pilha_ref));

    return 0;
}
