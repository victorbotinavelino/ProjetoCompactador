
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
    (*size)++;
}




No retirar(No *vetor, int *size)
{
   No retorno = vetor[0];
   (*size)--;
   for(int i = 0; i < *size; i++)
        vetor[i] = vetor[i+1];
   return retorno;

}



void FilaDeNos(unsigned char arquivo[], int *tamanho, int tamanhoArquivo, No fila[])
{

        int i;
     for(i = 0; i < tamanhoArquivo; i++)
    {

        if(*tamanho != 0)
        {

            int existe = 0;
            for(int indice = 0; indice < *tamanho; indice++)
            {
                if(fila[indice].caracter == arquivo[i])
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
                novoNo.caracter = arquivo[i];
                novoNo.frequencia = 1;
                incluir(fila, tamanho, novoNo);

            }

        }
        else
        {

            No novoNo;
            novoNo.caracter = arquivo[i];
            novoNo.frequencia = 1;
            incluir(fila, tamanho, novoNo);


        }



    }


}

No CriarArvore(No *vetor, int *size)
{
    while(*size > 3)
    {
        No* newNo=(No*)malloc(sizeof(No));
        No *esquerda = (No*)malloc(sizeof(No));
        *esquerda = retirar(vetor, size);
        No *direita = (No*)malloc(sizeof(No));
        *direita = retirar(vetor, size);
        newNo->esquerda = esquerda;
        newNo->direita = direita;
        newNo->caracter = '\0';
        newNo->frequencia = esquerda->frequencia + direita->frequencia;
        incluir(vetor, size, *newNo);
    }



    return vetor[0];

}


void gerarCodigos(No *noAtual, Codigo *cod, int tam, Codigo osCodigos[])
{
    if(noAtual->caracter == '\0')
    {
        Codigo *codEsquerda = &cod;
        Codigo *codDireita = &cod;

        codEsquerda->codigo = (cod->codigo) << 1;
        codEsquerda->tamanho++;

        codDireita->codigo = (cod->codigo << 1) + 1;
        codDireita->tamanho++;


        gerarCodigos(noAtual->esquerda, codEsquerda, tam, osCodigos);
        gerarCodigos(noAtual->direita, codDireita, tam, osCodigos);
    }
    else
    {
        osCodigos[tam] = *cod;
        osCodigos[tam].caracter = noAtual->caracter;
        printf("caracter do cod %d, eh %c, frequencia %d \n", tam, osCodigos[tam].caracter, noAtual->frequencia);
        tam++;
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

        unsigned char teste[7];
        strcpy(teste, "batata");

        int *tamanhoFuturo = (int*)malloc(sizeof(int));
        *tamanhoFuturo = 0;
        int tamanhoAtual = 6;

        No fila[256];
        FilaDeNos(teste, tamanhoFuturo, tamanhoAtual, fila);



        for(int i = 0; i < *tamanhoFuturo; i ++)
            printf("%c, %d ", fila[i].caracter, fila[i].frequencia);
        printf("\n");



        Codigo *code = (Codigo*)malloc(sizeof(Codigo));
        code->codigo = 0;
        code->tamanho = 0;


         int *tamanhooo = (int*)malloc(sizeof(int));
        *tamanhooo = tamanhoAtual;
        No *raiz = (No*)malloc(sizeof(No));
        *raiz = CriarArvore(fila, tamanhooo); // TÁ DANDO ERRADA ESSA LINHAAAA

        //printf("batata, %d", CriarArvore(fila, &tamanho).frequencia);


        Codigo codigos[256];

        int size = 0;

        gerarCodigos(raiz, code, size, codigos);
        char eins = codigos[0].codigo;
        char zwei = codigos[1].codigo;
        char drei = codigos[2].codigo;


        printf("Os primeiros 3 codigos: %d, %d, %d", eins, zwei, drei);
        printf("\n");


        free(tamanhooo);
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






