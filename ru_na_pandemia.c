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
} pessoa_t;         /* estrutura das pessoas */

typedef struct
{
    int ticket; /* numero do ticket */
    int motivo; /* motivo de nao ter sido utilizado */

} ticket_nu_t; /* estrutura tickets nao utilizados */

typedef struct
{
    double mascara;  /* dinheiro em mascara */
    double refeicao; /* dinheiro em refeicao */

} din_t; /* estrutura dinheiro arrecadado */

/* funcao cria pessoa ja atribuindo valores a ticket, vacina, mascara e dinheiro */
pessoa_t **pessoa_cria(int x)
{
    int i;
    pessoa_t **pessoa;
    pessoa = malloc(x * sizeof(pessoa_t *));
    if (!pessoa)
        return NULL;
    for (i = 0; i < x; i++)
        pessoa[i] = malloc(sizeof(pessoa_t));

    int z = 0;
    for (i = 0; i < x; i++)
    {
        /*tickets vao de 0 a 999
        proporcao de pessoas vacinadas 8 a cada 10
        proporcao de pessoas com mascara 8 a cada 10
        proporcao dinheiro de 10 pessoas, 6 tem 1.30 e 4 tem 3.80 */
        pessoa[i]->ticket = z;

        int v = 1 + (rand() % 10);
        if (v <= 8)
            pessoa[i]->vacina = 1;
        else
            pessoa[i]->vacina = 0;

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

/* inicializa a struct din e aloca espaco */
din_t *din_cria()
{
    din_t *din;
    din = malloc(sizeof(din_t));
    din->refeicao = 0;
    din->mascara = 0;
    return din;
}

/* inicializa a struct tickets_nu e aloca espaco  */
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

/* imprime a lista dos tickets nao utilizados e seus motivos */
void lista_imprimir(lista_t *l, ticket_nu_t **tickets_nu, din_t *din)
{
    int i;
    printf("Lista: \n");
    for (i = 0; i < l->tamanho; i++)
    {
        if (tickets_nu[i]->motivo == 1)
            printf("Ticket: %d - Nao esta vacinada \n", tickets_nu[i]->ticket);
        else if (tickets_nu[i]->motivo == 2)
            printf("Ticket: %d - Nao ha mascara para comprar \n", tickets_nu[i]->ticket);
        else if (tickets_nu[i]->motivo == 3)
            printf("Ticket: %d - Nao tem dinheiro suficiente para mascara \n", tickets_nu[i]->ticket);
        else if (tickets_nu[i]->motivo == 4)
            printf("Ticket: %d - Acabaram as refeicoes \n", tickets_nu[i]->ticket);
    }
    printf("\n");
}

/* empilha pilhas com numeros de 0 a tam */
void empilhar_pilhas(pilha_t *pilha, int tam)
{
    int i;
    for (i = 0; i < tam; i++)
        push(pilha, i);
}

/* enfileira as pessoas na fila */
void enfileirar(fila_t *fila, pessoa_t **pessoa)
{
    int i;
    for (i = 0; i < 1000; i++)
        queue(fila, pessoa[i]->ticket);
}

/* dispensa todas as pessoas que restam na fila */
void dispensar(fila_t *fila, ticket_nu_t **tickets_nu, pessoa_t **pessoa, lista_t *lista, int i)
{
    int aux;
    while (!fila_vazia(fila))
    {
        tickets_nu[i]->motivo = 4; /* acabou a comida */
        tickets_nu[i]->ticket = pessoa[fila->ini->chave]->ticket;
        lista_insere_fim(lista, pessoa[fila->ini->chave]->ticket);
        dequeue(fila, &aux);
        i++;
    }
}

/* faz o atendimento de todas as pessoas da fila */
void atendimento(pilha_t *pilha_ref, pilha_t *pilha_masc, pessoa_t **pessoa, ticket_nu_t **tickets_nu, din_t *din, fila_t *fila, lista_t *lista)
{
    int i = 0;
    int aux;
    while (!fila_vazia(fila) && !pilha_vazia(pilha_ref))
    {
        /* se não estiver vacinada sai da fila e seu ticket vai para a lista dos nao atendidos */
        if (pessoa[fila->ini->chave]->vacina == 0)
        {
            lista_insere_fim(lista, pessoa[fila->ini->chave]->ticket);
            tickets_nu[i]->motivo = 1;
            tickets_nu[i]->ticket = pessoa[fila->ini->chave]->ticket;
            i = i + 1;
            dequeue(fila, &aux);
        }
        /* se estiver de mascara paga 1.30 e ganha uma refeicao */
        else if (pessoa[fila->ini->chave]->masc == 1)
        {
            pessoa[fila->ini->chave]->dinheiro = pessoa[fila->ini->chave]->dinheiro - 1.30;
            din->refeicao = din->refeicao + 1.30;
            dequeue(fila, &aux);
            pop(pilha_ref);
            /* caso as refeicoes acabarem vai pra funcao dispensar */
            if (pilha_vazia(pilha_ref))
                dispensar(fila, tickets_nu, pessoa, lista, i);
        }
        /* se nao estiver de mascara eh removida da fila , paga 2.50 se tiver dinheiro e mascara disponivel
            e entra na fila novamente */
        else if (pessoa[fila->ini->chave]->dinheiro >= 2.50 && !pilha_vazia(pilha_masc))
        {
            pessoa[fila->ini->chave]->dinheiro = pessoa[fila->ini->chave]->dinheiro - 2.50;
            din->mascara = din->mascara + 2.50;
            pessoa[fila->ini->chave]->masc = 1;
            queue(fila, pessoa[fila->ini->chave]->ticket);
            dequeue(fila, &aux);
            pop(pilha_masc);
        }
        /* a pessoa nao tem dinheiro ou acabaram as mascaras, ticket vai para os nao utilizados e ela vai
            embora em comer */
        else
        {
            lista_insere_fim(lista, pessoa[fila->ini->chave]->ticket);
            if (pilha_vazia(pilha_masc))
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
    /*  mascara = 1 a 100
        refeicoes = 500 a 1000
        pessoas = 1000  */
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
    enfileirar(fila, pessoa);
    atendimento(pilha_ref, pilha_masc, pessoa, tickets_nu, din, fila, lista);
    fila_destroi(fila);
    lista_imprimir(lista, tickets_nu, din);
    printf("Numero de tickets nao utilizados: %d \n", lista_tamanho(lista));
    printf("Dinheiro ganho total: %f \n", din->mascara + din->refeicao);
    printf("Dinheiro ganho com refeicao: %f \n", din->refeicao);
    printf("Dinheiro ganho com mascara: %f \n", din->mascara);

    return 0;
}
