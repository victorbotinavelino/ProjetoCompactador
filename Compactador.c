
#include <stdio.h>
#include <string.h>
#include <math.h>



typedef struct No
{
    char caracter;
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



No *CriarFilaDeNos(char arquivo[], int *tamanho, int *tamanhoArquivo)
{

    No fila[256];
    No *anterior;
     for(int i = 0; i < tamanhoArquivo; i++)
    {
        if(&tamanho != 0)
        {
            int existe = 0;
            for(int indice = 0; indice < &tamanho; indice++)
            {
                if(fila[indice].caracter == arquivo[i])
                {
                    fila[indice].frequencia++;
                    while (indice < (&tamanho)-1 && fila[indice].frequencia > fila[indice+1].frequencia)
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
                anterior = &novoNo;
                incluir(fila, &tamanho, novoNo);
            }

        }
        else
        {

            No novoNo;
            novoNo.caracter = arquivo[i];
            novoNo.frequencia = 1;
            anterior = &novoNo;
            incluir(fila, &tamanho, novoNo);

        }


    }

}

No CriarArvore(No *vetor, int *size)
{
    while(*size > 1)
    {
        No newNo;
        No esquerda = retirar(vetor, size);
        No direita = retirar(vetor, size);

        newNo.esquerda = &esquerda;
        newNo.direita = &direita;

        newNo.caracter = '\0';
        newNo.frequencia = esquerda.frequencia + direita.frequencia;

        incluir(vetor, size, newNo);
    }

    return vetor[0];

}


void transcrever(No *noAtual, Codigo *cod, int tam, Codigo osCodigos[])
{
    if(noAtual->caracter == '\0')
    {
        Codigo *codEsquerda = &cod;
        Codigo *codDireita = &cod;

        codEsquerda->codigo = cod->codigo << 1;
        codEsquerda->tamanho++;

        codDireita->codigo = cod->codigo << 1 + 1;
        codDireita->tamanho++;

        noAtual->esquerda = (No*)malloc(sizeof(No*));
        noAtual->direita = (No*)malloc(sizeof(No*));

        transcrever(noAtual->esquerda, codEsquerda, tam, osCodigos);
        transcrever(noAtual->direita, codDireita, tam, osCodigos);
    }
    else
    {
        osCodigos[tam] = *cod;
        osCodigos[tam].caracter = noAtual->caracter;
        tam++;
    }

}

void traduzir(char lista[], Codigo osCodigos[], int tamanho, int tamanhoCod)
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


void reverter(char lista[], Codigo osCodigos[], int tamanho, int tamanhoCod)
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

        char teste[6];
        strcpy(teste, "batata");

        int *tamanhoFuturo = 0;
        int *tamanhoAtual = 6;

        No *fila = CriarFilaDeNos(teste, &tamanhoFuturo, &tamanhoAtual);

        for(int i = 0; i < tamanhoFuturo; i ++)
            printf("%c, %d ", fila[i].caracter, fila[i].frequencia);
        printf("\n");



        Codigo *code;
        code->codigo = 0;
        code->tamanho = 0;

        int size = 0;
        Codigo codigos[&tamanhoFuturo];

        No *raiz = (No*)malloc(sizeof(No*));


        *raiz = CriarArvore(fila, tamanhoAtual); // TÁ DANDO ERRADA ESSA LINHAAAA

        //printf("batata, %d", CriarArvore(fila, &tamanho).frequencia);

        transcrever(raiz, code, size, codigos);
        char eins = codigos[0].codigo;
        char zwei = codigos[1].codigo;
        char drei = codigos[2].codigo;


        printf("O primeiro codigo: %d, %d, %d", eins, drei, zwei);
        printf("\n");


        char clonee[6];
        strcpy(clonee, "batata");
        traduzir(clonee, codigos, 6, 3);



            printf("%d", clonee[0]);
        printf("\n");



         return 0;


    //printf("%c, %c, %c, %d, %d, %d", fila[0].caracter, fila[1].caracter, fila[2].caracter, fila[0].frequencia, fila[1].frequencia, fila[2].frequencia);






}






