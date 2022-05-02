#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "liblista.h"
#include "libfila.h"
#include "libpilha.h"
#include <math.h>

typedef struct
{
    int ticket;     /* identifica pessoa na fila */
    int vacina;     /* 0 - n vacinado , 1 - vacinado */
    int masc;       /* 0 - sem mascara , 1 - com mascara */
    float dinheiro; /* 1.30 ou 3.80 */
} pessoa_t;

typedef struct
{
    int ticket;
    int motivo;

} ticket_nu_t;

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
        //pessoa[i]->vacina = rand() % 2;
        int v = 1 + (rand() % 10);
        if (v <= 8)
            pessoa[i]->vacina = 1;
        else
            pessoa[i]->vacina = 0;
        
        //pessoa[i]->masc = rand() % 2;
        int m = 1 + (rand() % 10);
        if (m <= 8)
            pessoa[i]->masc = 1;
        else
            pessoa[i]->masc = 0;
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

ticket_nu_t **tickets_nu_cria(int x)
{
    int i;
    ticket_nu_t **tickets_nu;
    tickets_nu = malloc(x * sizeof(ticket_nu_t *));
    if (!tickets_nu)
        return NULL;
    for (i = 0; i < x; i++)
        tickets_nu[i] = malloc(sizeof(ticket_nu_t));
    return tickets_nu;
}

void lista_imprimir(lista_t *l, ticket_nu_t **tickets_nu, din_t *din)
{
    printf("Lista: \n");
    for (int i = 0; i < l->tamanho; i++)
    {
        if (tickets_nu[i]->motivo == 1)
            printf("%d - Não está vacinada \n", tickets_nu[i]->ticket);
        else if (tickets_nu[i]->motivo == 2)
            printf("%d - Não tem dinheiro suficiente para máscara \n", tickets_nu[i]->ticket);
        else if (tickets_nu[i]->motivo == 3)
            printf("%d - Não há máscara para comprar \n", tickets_nu[i]->ticket);
        else if (tickets_nu[i]->motivo == 4)
            printf("%d - Acabaram as refeições \n", tickets_nu[i]->ticket);
    }
    printf("\n");
}

void empilhar_pilhas(pilha_t *pilha, int tam)
{
    int i;
    for (i = 0; i < tam; i++)
        push(pilha, i);
}

void enfileirar(fila_t *fila, pessoa_t **pessoa)
{
    int i;
    for (i = 0; i < 1000; i++)
        queue(fila, pessoa[i]->ticket);
}

void dispensar(fila_t *fila, ticket_nu_t **tickets_nu, pessoa_t **pessoa, lista_t *lista, int i){
    int aux;
    while (!fila_vazia(fila)){
        printf("%d \n", i);
        tickets_nu[i]->motivo = 4;
        tickets_nu[i]->ticket = pessoa[fila->ini->chave]->ticket;
        lista_insere_fim(lista, pessoa[fila->ini->chave]->ticket);
        dequeue(fila, &aux);
        i++;
    }

}

void atendimento(pilha_t *pilha_ref, pilha_t *pilha_masc, pessoa_t **pessoa, ticket_nu_t **tickets_nu, din_t *din, fila_t *fila, lista_t *lista)
{
    int i = 0;
    int aux;
    while (!fila_vazia(fila) && !pilha_vazia(pilha_ref))
    {
        // se não esta vacinada
        if (pessoa[fila->ini->chave]->vacina == 0)
        {
            lista_insere_fim(lista, pessoa[fila->ini->chave]->ticket);
            tickets_nu[i]->motivo = 1;
            tickets_nu[i]->ticket = pessoa[fila->ini->chave]->ticket;
            i = i + 1;
            dequeue(fila, &aux);
        }
        // se esta com mascara
        else if (pessoa[fila->ini->chave]->masc == 1 && !pilha_vazia(pilha_ref))
        {
            pessoa[fila->ini->chave]->dinheiro = pessoa[fila->ini->chave]->dinheiro - 1.30;
            din->refeicao = din->refeicao + 1.30;
            dequeue(fila, &aux);
            pop(pilha_ref);
            if (pilha_vazia(pilha_ref))
                dispensar(fila, tickets_nu, pessoa, lista, i);
        }
        else if (pessoa[fila->ini->chave]->dinheiro >= 2.50 && !pilha_vazia(pilha_masc))
        {
            pessoa[fila->ini->chave]->dinheiro = pessoa[fila->ini->chave]->dinheiro - 2.50;
            din->mascara = din->mascara + 2.50;
            pessoa[fila->ini->chave]->masc = 1;
            queue(fila, pessoa[fila->ini->chave]->ticket);
            dequeue(fila, &aux);
            pop(pilha_masc);
        }
        // acabarama as mascaras ou nao tem dinheiro
        else
        {
            lista_insere_fim(lista, pessoa[fila->ini->chave]->ticket);
            if (pessoa[fila->ini->chave]->dinheiro < 2.50)
            {
                tickets_nu[i]->motivo = 2;
                tickets_nu[i]->ticket = pessoa[fila->ini->chave]->ticket;
            }
            else
            {
                tickets_nu[i]->motivo = 3;
                tickets_nu[i]->ticket = pessoa[fila->ini->chave]->ticket;
            }
            i = i + 1;
            dequeue(fila, &aux);
        }
    }
}

int main()
{
    srand(time(NULL));
    int x = 1 + (rand() % 100);
    int y = 500 + (rand() % 500);
    int z = 1000;
    pilha_t *pilha_masc = pilha_cria(x);
    pilha_t *pilha_ref = pilha_cria(y);
    pessoa_t **pessoa = pessoa_cria(z);
    ticket_nu_t **tickets_nu = tickets_nu_cria(z);
    din_t *din = din_cria();
    fila_t *fila = fila_cria();
    lista_t *lista = lista_cria();
    empilhar_pilhas(pilha_masc, x);
    empilhar_pilhas(pilha_ref, y);
    printf("%d \n", pilha_tamanho(pilha_masc));
    printf("%d \n", pilha_tamanho(pilha_ref));
    enfileirar(fila, pessoa);
    printf("tamanho masc: %d \n", pilha_tamanho(pilha_ref));

    atendimento(pilha_ref, pilha_masc, pessoa, tickets_nu, din, fila, lista);
    
    
    fila_destroi(fila);
    printf("Dinheiro ganho total: %f \n", din->mascara + din->refeicao);
    printf("Dinheiro ganho com refeição: %f \n", din->refeicao);
    printf("Dinheiro ganho com mascara: %f \n", din->mascara);
    lista_imprimir(lista, tickets_nu, din);
    printf("Número de tickets nao utilizados: %d \n", lista_tamanho(lista));
    printf("tamanho masc: %d \n", pilha_tamanho(pilha_masc));
    printf("tamanho masc: %d \n", pilha_tamanho(pilha_ref));

    return 0;
}
