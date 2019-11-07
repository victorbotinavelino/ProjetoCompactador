
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



typedef struct No
{
    unsigned char caracter;
    int frequencia;
    struct No *direita, *esquerda;

} No;



typedef struct Codigo
{
    char caracter;
    int codigo;
    int tamanho;
} Codigo;



void incluir(No *vetor, int *size, No newNo)
{
    int i;
    for(i = 0; i < *size; i++)
    {
        if(newNo.frequencia < vetor[i].frequencia)
            break;
    }

    for(int e = *size; e > i; e--)
        vetor[e] = vetor[e-1];
    vetor[i] = newNo;
    (*size)= *size + 1;
}

void arvoreToString(No* raiz)
{
    printf("[%c-%d", raiz->caracter, raiz->frequencia);
    if(raiz->esquerda)
    {
        printf(" -> ");
        arvoreToString(raiz->esquerda);
    }
    if(raiz->direita)
    {
        printf(" -> ");
        arvoreToString(raiz->direita);
    }
    printf("]");
}





No retirar(No *vetor, int *size)
{
   No retorno = vetor[0];
   (*size)--;
   for(int i = 0; i < *size; i++)
        vetor[i] = vetor[i+1];
   return retorno;

}



void FilaDeNos( int *tamanho, No fila[])
{

    int i;
    unsigned char* caracterLido;
    FILE *file = fopen("BATATA.txt", "rb");
    while(fread(caracterLido, 1,1,file))
    {
        if(*tamanho != 0)
        {
            int existe = 0;
            for(int indice = 0; indice < *tamanho; indice++)
            {
                if(fila[indice].caracter == *caracterLido)
                {
                    fila[indice].frequencia++;
                    while (indice < (*tamanho)-1 && fila[indice].frequencia > fila[indice+1].frequencia)
                    {
                        No aux = fila[indice];
                        fila[indice] = fila[indice+1];
                        fila[indice+1] = aux;
                        indice++;
                    }
                    existe = 1;
                    break;

                }

            }
            if(existe == 0)
            {
                No novoNo;
                novoNo.caracter = *caracterLido;
                novoNo.frequencia = 1;
                novoNo.direita = (No*)malloc(sizeof(No));
                novoNo.esquerda = (No*)malloc(sizeof(No));
                novoNo.esquerda = NULL;
                novoNo.direita  = NULL;
                incluir(fila, tamanho, novoNo);

            }

        }
        else
        {

            No novoNo;
            novoNo.direita = (No*)malloc(sizeof(No));
            novoNo.esquerda = (No*)malloc(sizeof(No));
            novoNo.esquerda = NULL;
            novoNo.direita  = NULL;
            novoNo.caracter = *caracterLido;
            novoNo.frequencia = 1;
            incluir(fila, tamanho, novoNo);
        }



    }


}

No CriarArvore(No *vetor, int *size)
{
    while(*size > 1)
    {
        No* newNo=(No*)malloc(sizeof(No));
        No *esquerda = (No*)malloc(sizeof(No));
        *esquerda = retirar(vetor, size);
        No *direita = (No*)malloc(sizeof(No));
        *direita = retirar(vetor, size);
        newNo->esquerda = (No*)malloc(sizeof(No));
        newNo->direita = (No*)malloc(sizeof(No));
        newNo->esquerda = esquerda;
        newNo->direita = direita;
        newNo->caracter = '\0';
        newNo->frequencia = esquerda->frequencia + direita->frequencia;
        incluir(vetor, size, *newNo);
    }



    return vetor[0];

}


void gerarCodigos(No *noAtual, char* cod, int topo, Codigo osCodigos[], int* qtdCodigos)
{
    /*if(noAtual->caracter == '\0')
    {*/
    if(noAtual->esquerda)
    {
        cod[topo] = '0';
        gerarCodigos(noAtual->esquerda, cod, topo+1, osCodigos, qtdCodigos);
    }

    if(noAtual->direita)
    {
        cod[topo] = '1';
        gerarCodigos(noAtual->direita, cod, topo+1, osCodigos, qtdCodigos);
    }

    //}
    if(noAtual->direita ==  NULL && noAtual->esquerda == NULL);
    {

        int i = 0;
        int j = topo-1;
        osCodigos[*qtdCodigos].tamanho = topo;
        osCodigos[*qtdCodigos].codigo = 0;
        for(;i<topo;i++)
        {
            if(cod[i] == '1')
                osCodigos[*qtdCodigos].codigo += pow(2, j--);
        }
        osCodigos[*qtdCodigos].caracter = noAtual->caracter;
        printf("caracter do cod %d, eh %c, frequencia %d \n", *qtdCodigos, osCodigos[*qtdCodigos].caracter, noAtual->frequencia);
        *qtdCodigos = *qtdCodigos + 1;
        printf("aaaa %d\n\n", *qtdCodigos);
    }
}


void compactar(char lista[], Codigo osCodigos[], int tamanho, int tamanhoCod)
{
    for(int indice = 0; indice < tamanho; indice++)
    {

        for(int indiceCod = 0; indiceCod < tamanhoCod; indiceCod++)
        {
            printf("valor1:%d e o valor 2: %d \n", osCodigos[indiceCod].caracter, lista[indice]);
           if(osCodigos[indiceCod].caracter == lista[indice])
            {
                printf("%d, esse eh o cod", osCodigos[indiceCod].codigo);
                lista[indice] = osCodigos[indiceCod].codigo;

            }

        }


    }

}


void descompactar(char lista[], Codigo osCodigos[], int tamanho, int tamanhoCod)
{
    for(int indice = 0; indice < tamanho; tamanho++)
    {
        for(int indiceCod = 0; indiceCod < tamanhoCod; indiceCod++)
            if(osCodigos[indiceCod].codigo == lista[indice])
            {
                lista[indice] = osCodigos[indiceCod].caracter;
                break;
            }

    }

}

int main()
{


        int *tamanhoFuturo = (int*)malloc(sizeof(int));
        *tamanhoFuturo = 0;

        No fila[256];
        FilaDeNos(tamanhoFuturo, fila);



        /*for(int i = 0; i < *tamanhoFuturo; i ++)
            printf("%c, %d ", fila[i].caracter, fila[i].frequencia);
        printf("\n");*/



        /*Codigo *code = (Codigo*)malloc(sizeof(Codigo));
        code->codigo = 0;
        code->tamanho = 0;*/

        No *raiz = (No*)malloc(sizeof(No));
        *raiz = CriarArvore(fila, tamanhoFuturo);

        //arvoreToString(raiz);

        //printf("batata, %d", CriarArvore(fila, &tamanho).frequencia);


        Codigo *codigos = (Codigo*)malloc(sizeof(Codigo));

        int size = 0;
        int* qtsCodigos = (int*)malloc(sizeof(int));
        *qtsCodigos =0;

        char code[257];
        gerarCodigos(raiz, code, size, codigos, qtsCodigos);
        char eins = codigos[0].caracter;
        char zwei = codigos[1].caracter;
        char drei = codigos[2].caracter;


        printf("Os primeiros 3 codigos: %c, %c, %c", eins, zwei, drei);
        printf("\n");

        free(tamanhoFuturo);
        free(raiz);
        free(code);


/*  -----------------  PARTE 2  ---------------------
        char clonee[6];
        strcpy(clonee, "batata");
        compactar(clonee, codigos, 6, 3);



            printf("%d", clonee[0]);
        printf("\n");

        */


         return 0;


    //printf("%c, %c, %c, %d, %d, %d", fila[0].caracter, fila[1].caracter, fila[2].caracter, fila[0].frequencia, fila[1].frequencia, fila[2].frequencia);






}






