#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "liblista.h"
#include "libfila.h"
#include "libpilha.h"
#include<math.h>

typedef struct {
    int* ticket;   /* identifica pessoa na fila */
    int* vacina;    /* 0 - n vacinado , 1 - vacinado */
    int* masc;     /* 0 - sem mascara , 1 - com mascara */
    float* dinheiro; /* 1.30 ou 3.80 */
} pessoa_t;

pessoa_t* pessoa_cria (int ticket){
    pessoa_t *pessoa;
    pessoa = malloc(sizeof(pessoa_t));
    int x = 1000;
    pessoa->ticket = malloc(sizeof(x));
    pessoa->vacina = malloc(sizeof(x));
    pessoa->masc = malloc(sizeof(x));
    pessoa->dinheiro = malloc(sizeof(x));

    if(!pessoa)
        return NULL;
    
    srand(time(NULL));  
    long int i;  
    for (i = 0; i < 6 ; i++){ 
        pessoa->ticket[i] = 1 + (rand() % 1000);
        pessoa->vacina[i] = rand() % 2; 
        pessoa->masc[i] = rand() % 2;
        int x = 1 + (rand() % 10);
        if (x <= 6)
            pessoa->dinheiro[i] = 1.30; 
        else
            pessoa->dinheiro[i] = 3.80; 
         
    }
    
    return pessoa;
}

int main(){

    
    int x = 1 + ( rand() % 100 );
    int y = 500 + ( rand() % 500 );
    int z = 1000;
    pilha_t* pilha_masc = pilha_cria(x);
    pilha_t* pilha_ref = pilha_cria(y);
    pessoa_t* pessoa = pessoa_cria(z);
    printf("Tamanho da pilha: %d \n", pilha_masc->nelem);
    printf("Tamanho da pilha: %d \n", pilha_ref->nelem);
    pilha_destroi(pilha_masc);
    pilha_destroi(pilha_ref);

    int i;
    for(i = 0; i < 6 ; i++){
    printf("Ticket: %d \n", pessoa->ticket[i]);
    printf("vacina: %d \n", pessoa->vacina[i]);
    printf("masc: %d \n", pessoa->masc[i]);
    printf("dinheiro: %f \n", pessoa->dinheiro[i]);
    }

    return 0;
}
