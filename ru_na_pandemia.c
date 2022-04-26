#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "liblista.h"
#include "libfila.h"
#include "libpilha.h"
#include<math.h>

typedef struct {
    int ticket;   /* identifica pessoa na fila */
    int vacina;    /* 0 - n vacinado , 1 - vacinado */
    int masc;     /* 0 - sem mascara , 1 - com mascara */
    float dinheiro; /* 1.30 ou 3.80 */
} pessoa_t;

pessoa_t** pessoa_cria (int ticket){
    int x = 1050;
    int i;
    pessoa_t **pessoa;
    pessoa = malloc(x * sizeof(pessoa_t*));
    if(!pessoa)
        return NULL;
    for (i = 0; i < x; i++) 
        pessoa[i] = malloc(sizeof(pessoa_t));

    
    srand(time(NULL));   
    int z = 1; 
    for (i = 0; i < x ; i++){ 
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

int main(){

    srand(time(NULL));  
    int x = 1 + ( rand() % 100 );
    int y = 500 + ( rand() % 500 );
    int z = 1000;
    int aux;

    // 1 E 2 

    pilha_t* pilha_masc = pilha_cria(x);
    pilha_t* pilha_ref = pilha_cria(y);
    pessoa_t** pessoa = pessoa_cria(z);
    int i;

    for(i = 0; i < x ; i++)
        push(pilha_masc, i);

    
    for(i = 0; i < y ; i++)
        push(pilha_ref, i);
    
    //printf("%d \n", pilha_tamanho(pilha_masc));
    //printf("%d \n", pilha_tamanho(pilha_ref));
    
    // 4
    fila_t* fila = fila_cria();
    for(i = 1; i < 1050; i++)
        queue(fila, pessoa[i]->ticket);

    fila_imprime(fila);
    // 5
    lista_t* lista = lista_cria();
    i = 0;
    printf("%d \n", fila->ini->chave);
    while (!pilha_vazia(pilha_ref) && !fila_vazia(fila)) {
        if (pessoa[fila->ini->chave]->vacina == 0){
            dequeue(fila, &aux);
            lista_insere_fim(lista, pessoa[fila->ini->chave]->ticket);
        }
        else if (pessoa[fila->ini->chave]->masc == 1) {
            pessoa[fila->ini->chave]->dinheiro = pessoa[fila->ini->chave]->dinheiro - 1.30;
            dequeue(fila, &aux);
            pop(pilha_ref);
        }
        else {
            dequeue(fila, &aux);
            if(pessoa[fila->ini->chave]->dinheiro >= 2.50 && !pilha_vazia(pilha_masc)) {
                pessoa[fila->ini->chave]->dinheiro = pessoa[fila->ini->chave]->dinheiro - 2.50;
                pessoa[fila->ini->chave]->masc = 1;
                queue(fila, pessoa[fila->ini->chave]->ticket);
                printf("ticket: %d\n", pessoa[fila->ini->chave]->ticket);
            }
            else {
                lista_insere_fim(lista, pessoa[fila->ini->chave]->ticket);
            }
        }
        printf("%d \n", fila->ini->chave);

    }
    fila_destroi(fila);
    //printf("%d \n", lista_tamanho(lista));
    // lista_imprime(lista);
    //printf("%d \n", pilha_tamanho(pilha_ref));
    //printf("%d \n", pilha_tamanho(pilha_masc));
    
    return 0;
}
