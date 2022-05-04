#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "T2.h"

struct nodo
{
    struct cidade cdd;
    struct nodo *ant;
    struct nodo *prox;
};
typedef struct nodo nodo;
struct lista
{
    int id;
    struct nodo *rota;
    struct nodo *prox;
};
typedef struct lista lista;
onibus* cria_rota()
{
    onibus* o = (onibus*) malloc(sizeof(onibus));
    if(o != NULL) *o = NULL;
    return o;
}
void libera_rota(onibus* o)
{
    if(o != NULL)
    {
        nodo *no;
        while((*o) != NULL)
        {
            no = *o;
            *o = (*o)->prox;
            free(no);
        }
        free(o);
    }
}
int size_rota(onibus* o)
{
    if(o == NULL) return 0;
    int cont = 0;
    nodo *no = *o;
    while(no != NULL)
    {
        cont++;
        no = no->prox;
    }
    return cont;
}
int rota_vazia(onibus* o)
{
    if(o == NULL) return 1;
    if(*o == NULL) return 1;
    return 0;
}
int insere_r_ini(onibus* o, struct cidade c)
{
    if(o == NULL) return 0;
    nodo* no = (nodo*) malloc(sizeof(nodo));
    if(no == NULL) return 0;
    no->cdd = c;
    no->ant = NULL;
    no->prox = (*o);
    *o = no;
    return 1;
}
int insere_r_fim(onibus* o, struct cidade c)
{
    if(o == NULL) return 0;
    nodo* no = (nodo*) malloc(sizeof(nodo));
    if(no == NULL) return 0;
    no->cdd = c;
    no->prox = NULL;
    nodo *aux = *o;
    while(aux->prox != NULL)
        aux = aux->prox;
    no->ant = aux;
    aux->prox = no;
    return 1;
}
int insere_r_med(onibus* o, struct cidade c)
{
    if(o == NULL) return 0;
    nodo* no = (nodo*) malloc(sizeof(nodo));
    if(no == NULL) return 0;
    no->cdd = c;
    nodo *aux = *o;
    while(aux->prox != NULL)
        aux = aux->prox;
    no->ant = aux->ant;
    no->prox = aux;
    aux->ant = no;
    return 1;
}
int rota_nome(onibus* o, onibus* p)
{
    if(o == NULL) return 0;
    nodo *aux = *o;
    while(aux->prox != NULL)
        aux = aux->prox;
    if(aux == NULL) return 0;
    *p = aux;
    return 1;
}
int rota_inicio(onibus* o, onibus* p)
{
    if(o == NULL) return 0;
    *p = *o;
    return 1;
}

/*==========================*/

Lista* cria_lista()
{
    Lista* l = (Lista*) malloc(sizeof(Lista));
    if(l != NULL) *l = NULL;
    return l;
}
void libera_nodo(Lista* l, int i)
{
    if(l != NULL)
    {
        lista *ant, *no = *l;
        while(no != NULL && no->id != i)
        {
            ant = no;
            no = no->prox;
        }
        if(no == NULL) return 0;
        if(no == *l) *l = no->prox;
        else ant->prox = no->prox;
        return 1;
    }
}
void libera_lista(Lista* l)
{
    if(l != NULL)
    {
        nodo* no;
        while((*l!= NULL))
        {
            no = *l;
            *l = (*l)->prox;
            free(no);
        }
        free(l);
    }
}
int tamanho_lista(Lista* l)
{
    if(l == NULL) return 0;
    int cont = 0;
    nodo *no = *l;
    while(no != NULL)
    {
        cont++;
        no = no->prox;
    }
    return cont;
}
int lista_vazia(Lista* l)
{
    if(l == NULL) return 1;
    if(*l == NULL) return 1;
    return 0;
};
int insere_lista(Lista* l, onibus* o)
{
    if(l == NULL) return 0;
    lista* no = (lista*) malloc(sizeof(lista));
    if(no == NULL) return 0;
    no->id = 1;
    no->rota = o;
    no->prox = NULL;
    if((*l) == NULL) *l = no;
    else
    {
        lista *aux = *l;
        while(aux->prox != NULL)
            aux = aux->prox;
        while(busca_id(l, no->id, NULL) != 0)
            no->id++;
        aux->prox = no;
    }
    return 1;
}
int imprime(Lista* l)
{
    if(l != NULL)
    {
        lista *no = *l;
        while(no != NULL)
        {
            nodo* n = (nodo*) malloc(sizeof(nodo));
            if(rota_nome(no->rota, &n))
                printf("\n\t%d - %s", no->id, n->cdd);
            no = no->prox;
        }
        if(no == NULL) printf("\n");
        return 1;
    }
    return 0;
}
int imprime_rotas(Lista* l, int i)
{
    if(!lista_vazia(l))
    {
        lista *no = *l;
        while(no != NULL && no->id != i)
            no = no->prox;
        if(no == NULL) return 0;
        else
        {
            nodo *n;
            rota_inicio(no->rota, &n);
            nodo *aux = n;
            int ui;
            do
            {
                printf("\n\t%s - ", aux->cdd.nome);
                printf("%s\n", aux->cdd.frase);
                if(aux->prox == NULL) printf("\n\t[Voce chegou a seu destino]\n");
                printf("\n\t1 - Proxima cidade\n\t2 - Cidade anterior\n\t3 - Sair\n");
                printf("\n\tOpcao: ");
                scanf("%d", &ui);
                switch(ui)
                {
                case 1:
                    if(aux->prox != NULL) aux = aux->prox;
                    else printf("\n\tOpcao invalida!\n");
                    break;
                case 2:
                    if(aux->ant != NULL) aux = aux->ant;
                    else printf("\n\tOpcao invalida!\n");
                    break;
                case 3:
                    break;
                default:
                    printf("\n\tOpcao inavalida!");
                }
            }
            while(ui != 3);
        }
        return 1;
    }
    return 0;
};
int busca_id(Lista* l, int i, onibus* o)
{
    if(l == NULL) return 0;
    if((*l) == NULL) return 0;
    lista *aux = *l;
    while(aux != NULL && aux->id != i)
        aux = aux->prox;
    if(aux == NULL) return 0;
    else
    {
        if(o != NULL) *o = aux->rota;
        return 1;
    }
}
int novo_id(Lista* l)
{
    int i = 1;
    lista *no = *l;
    while(no != NULL)
    {
        while(busca_id(l, i, NULL) != 0)
        {
            printf("\n\t%d", no->id);
            no = no->prox;
            i++;
        }
    }
    return 1;
}
int clear()
{
    printf("\n");
    system("pause");
    system("cls");
}
