
#include <stdio.h>
#include <string.h>


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
    if(noAtual->caracter == NULL)
    {
        Codigo *codEsquerda = &cod;
        Codigo *codDireita = &cod;

        codEsquerda->codigo = cod->codigo << 1;
        codEsquerda->tamanho++;

        codDireita->codigo = cod->codigo << 1 + 1;
        codDireita->tamanho++;

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

int main()
{

    /*int arroz = 1;
    int *batata = &arroz;
    *batata = 0;
    printf("%d", arroz);*/

    char teste[6];
    strcpy(teste, "batata");

    No fila[100];
    int tamanho = 0;
    No *anterior;

    for(int i = 0; i < 6; i++)
    {
        if(tamanho != 0)
        {
            int existe = 0;
            for(int indice = 0; indice < tamanho; indice++)
            {
                if(fila[indice].caracter == teste[i])
                {
                    fila[indice].frequencia++;
                    while (indice < tamanho-1 && fila[indice].frequencia > fila[indice+1].frequencia)
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
                novoNo.caracter = teste[i];
                novoNo.frequencia = 1;
                anterior = &novoNo;
                incluir(fila, &tamanho, novoNo);
            }

        }
        else
        {

            No novoNo;
            novoNo.caracter = teste[i];
            novoNo.frequencia = 1;
            anterior = &novoNo;
            incluir(fila, &tamanho, novoNo);

        }


    }

        for(int i = 0; i < tamanho; i ++)
            printf("%c, %d ", fila[i].caracter, fila[i].frequencia);
        printf("\n");

        Codigo *code;
        code->codigo = 0;
        code->tamanho = 0;
        int size = 0;
        Codigo codigos[tamanho];
        No *raiz;
        *raiz = CriarArvore(fila, &tamanho);

        transcrever(raiz, code, size, codigos);

        printf("O primeiro código: %d", codigos[0]);



    //printf("%c, %c, %c, %d, %d, %d", fila[0].caracter, fila[1].caracter, fila[2].caracter, fila[0].frequencia, fila[1].frequencia, fila[2].frequencia);





    return 0;
}






