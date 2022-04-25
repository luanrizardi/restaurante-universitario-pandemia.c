#include<stdio.h>
#include<stdlib.h>
#include "libpilha.h"

/* 
 * Cria e retorna uma nova pilha com capacidade de nelem elementos. 
 * Retorna NULL em caso de erro de alocação 
*/
pilha_t* pilha_cria (int nelem){
    pilha_t *pilha;
    pilha = malloc(sizeof(pilha_t));
    pilha->elems = malloc(sizeof(nelem));
    if(!pilha || !pilha->elems)
        return NULL;
    pilha->nelem = nelem;
    pilha->topo = -1;
    return pilha;
}

/* 
 * Insere elem na pilha (politica LIFO). Retorna o número de elementos na pilha 
 * em caso de sucesso e -1 em caso de pilha cheia 
*/
int push (pilha_t* pilha, int elem){
    if(pilha->topo >= pilha->nelem - 1)
        return -1;
    pilha->topo++;
    pilha->elems[pilha->topo] = elem;
    return pilha->topo;

}

/* 
 * Remove (politica LIFO) e retorna um elemento da pilha. 
 * Em caso de pilha vazia retorna 0 
*/
int pop (pilha_t* pilha){
    if(pilha_vazia(pilha))
        return 0;   
    pilha->topo--;
    return pilha->elems[pilha->topo + 1];    
}
 
/* Similar ao Pop, mas retorna sem remover */
int pilha_topo (pilha_t* pilha){ 
    if(pilha_vazia(pilha))
        return 0; 
    return pilha->elems[pilha->topo];
}  

/* Retorna o numero de elementos da pilha, que pode ser 0 */
int pilha_tamanho (pilha_t* pilha){
    return pilha->topo + 1;
}

/* Retorna 1 se pilha vazia, 0 em caso contrario */ 
int pilha_vazia (pilha_t* pilha){
    if(pilha->topo != -1)
        return 0;
    return 1;    
}

/* Desaloca memoria de pilha_t e retorna NULL */
pilha_t* pilha_destroi (pilha_t* pilha){
	free(pilha->elems);
    pilha->elems = NULL;
    free(pilha);
    pilha = NULL;
    return NULL;
}
/* 
 * Imprime a pilha, da base ate o topo, este por ultimo, sem espaco no final.
 * Quando a pilha estiver vazia, nao imprime nada, nem um \n.
 * Esta funcao eh somente para facilitar teus testes.
 * Normalmente ela nao existe nas implementacoes de um TAD pilha.
*/
void pilha_imprime (pilha_t* pilha){
    if (!pilha)
        return;    
    printf("Pilha: ");
    for(int i = 0; i <= pilha->topo ; i++){
        printf("%d ",pilha->elems[i]);
    }
    printf("\n");
}
