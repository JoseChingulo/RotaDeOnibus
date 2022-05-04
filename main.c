#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "T2.h"
#include <stdbool.h>

int main()

{
    Lista *l;
    l = cria_lista();
    struct cidade c;
    int opt = 0, opt1 = 0, ui = 0, id, ctrl = 0;
    char n[256], f[256], str[10];

    do
    {
        printf("1 - Cadastrar rota\n2 - Excluir rota\n3 - Visitar rota\n4 - Sair\n");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opt);
        getchar();

        switch(opt)
        {
        case 1:
            printf("\n\tDigite a cidade de destino: ");
            gets(&c.nome);

            printf("\n\tDigite a descricao da cidade: ");
            gets(&c.frase);

            struct cidade curit;
            strcpy(curit.nome, "Curitiba");
            strcpy(curit.frase, "Capital do estado. Cidade do Jardim Botanico.");
            onibus *no;
            no = cria_rota();
            insere_r_ini(no, curit);
            do
            {
                ctrl = 0;
                printf("\n\tGostaria de adicionar mais uma cidade a rota? [S/N]\n\t");
                scanf("%s", &str);
                getchar();
                if(strcmp(str, "s") != 0 && strcmp(str, "S") != 0) ctrl = 1;
                else
                {

                    struct cidade c1;
                    printf("\n\tDigite o nome da cidade: ");
                    gets(&c1.nome);
                    printf("\n\tDigite a descricao da cidade: ");
                    gets(&c1.frase);
                    insere_r_fim(no, c1);
                }
            }
            while(ctrl != 1);
            insere_r_fim(no, c);
            if(insere_lista(l, no)) /*imprime(l)*/;
            else printf("\n\tOcorreu um erro!");
            clear();
            break;


        case 2:
            printf("\n\tRotas cadastradas:\n");
            imprime(l);
            imprime(l);
            printf("\n\tDigite o digito verificador da rota: ");
            scanf("%d", &id);
            onibus *o;
            if(busca_id(l, id, &o) != 0)
            {

            //libera_rota(o);
                libera_nodo(l, id);
                printf("\nRota excluida com sucesso!\n");
            }
            else printf("\n\t\Rota nao encontrada: ", id);
            clear();
            break;
        case 3:
            printf("\n\tRotas cadastradas:\n");
            imprime(l);
            printf("\n\tDigite o digito verificador da rota: ");
            scanf("%d", &id);
            if(busca_id(l, id, NULL) != 0)
                imprime_rotas(l, id);
            else printf("\n\t\Rota nao encontrada: %d", id);
            clear();
            break;
        case 4:
            break;
        default:
            printf("\n\tOpcao invalida!\n");
        }
    }
    while(opt != 4);
    libera_lista(l);
    return 0;
}
