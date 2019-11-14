
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



typedef struct No
{
    unsigned char caracter;
    int frequencia;
    char vazio;
    struct No *direita, *esquerda;

} No;



typedef struct Codigo
{
    unsigned char caracter;
    int codigo;
    int tamanho;
} Codigo;



void incluir(No *vetor, int *size, No newNo)
{
    int i = 0;
    for(i = 0; i < *size; i++)
    {
        if(newNo.frequencia < vetor[i].frequencia)
            break;
    }

    int e = 0;
    for(e = *size; e > i; e--)
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
   int i = 0;
   for(; i < *size; i++)
        vetor[i] = vetor[i+1];
   return retorno;

}



void FilaDeNos(int *tamanho, No* fila, char* nomeArquivo)
{

    int i;
    unsigned char caracterLido;
    FILE* file = fopen(nomeArquivo, "rb");

    while(fread(&caracterLido, sizeof(char),1,file)>=1)
    {
        if(*tamanho != 0)
        {
            int existe = 0;
            int indice = 0;
            for(; indice < *tamanho; indice++)
            {
                if(fila[indice].caracter == caracterLido)
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
                novoNo.caracter = caracterLido;
                novoNo.frequencia = 1;
                novoNo.vazio = 0;
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
            novoNo.vazio = 0;
            novoNo.caracter = caracterLido;
            novoNo.frequencia = 1;
            incluir(fila, tamanho, novoNo);
        }



    }

    fclose(file);

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
        newNo->vazio = 1;
        newNo->frequencia = esquerda->frequencia + direita->frequencia;
        incluir(vetor, size, *newNo);
    }



    return vetor[0];

}

void gerarCodigos(No *noAtual, char cod[], int topo, Codigo *osCodigos[], int *qtdCodigos)
{

        if(noAtual->vazio == 0 && noAtual->esquerda == NULL && noAtual->direita == NULL)
        {
            if(noAtual->esquerda == NULL && noAtual->direita == NULL)
            {
                    int i = 0;
                    int j = topo;
                    (*osCodigos)[*qtdCodigos].tamanho = topo;
                    (*osCodigos)[*qtdCodigos].codigo = 0;
                    for(;i <= topo;i++)
                    {
                        if(cod[i] == '1')
                                (*osCodigos)[*qtdCodigos].codigo += pow(2, --j);
                        //printf("kehehe, % d aaaa\n", (*osCodigos)[*qtdCodigos].codigo);
                    }

                    (*osCodigos)[*qtdCodigos].caracter = noAtual->caracter;
                    //printf("caracter do cod n%d, ou seja, O CODIGO EH: %d,,, eh %c, frequencia %d, tamanho %d \n", *qtdCodigos, (*osCodigos)[*qtdCodigos].codigo,(*osCodigos)[*qtdCodigos].caracter, noAtual->frequencia, topo);
                    *qtdCodigos = *qtdCodigos + 1;
                    //printf("aaaa %d\n\n", *qtdCodigos);
            }
        }

        if(noAtual->esquerda)
        {
            int indice = topo+2;
            char codEsq[indice];
            int i;
            for(i = 0; i <= topo; i++)
                    codEsq[i] = cod[i];

            codEsq[topo + 1] = '0';
            codEsq[topo + 2] = '\0';
            gerarCodigos(noAtual->esquerda, codEsq, topo+1, osCodigos, qtdCodigos);
        }

        if(noAtual->direita)
        {
            int indice = topo + 3;
            char codDir[indice];
            int i;
               for(i = 0; i <= topo; i++)
                    codDir[i] = cod[i];

            codDir[topo + 1] = '1';
            codDir[topo + 2] = '\0';
            gerarCodigos(noAtual->direita, codDir, topo+1, osCodigos, qtdCodigos);
        }

}


void compactar(char* arquivoSaida, short int* tamanho, No* no, Codigo* cods, char* nomeArquivo)
{


            int indice = 0;
            FILE* file = fopen(nomeArquivo, "rb");
            FILE* saida = fopen(arquivoSaida, "wb");
            fwrite(&indice, sizeof(char), 1, saida);
            short int auxiliar = *tamanho;
            fwrite(&auxiliar, sizeof(short int), 1, saida);

            while(indice < *tamanho)
            {

                fwrite(&no[indice].caracter, sizeof(char), 1, saida);
                unsigned char byte1 = no[indice].frequencia & 255;
                unsigned char byte2 = (no[indice].frequencia>>8) & 255;
                unsigned char byte3 = (no[indice].frequencia>>16) & 255;
                unsigned char byte4 = (no[indice].frequencia>>24) & 255;

                fwrite(&byte1, sizeof(char), 1, saida);
                fwrite(&byte2, sizeof(char), 1, saida);
                fwrite(&byte3, sizeof(char), 1, saida);
                fwrite(&byte4, sizeof(char), 1, saida);

                indice++;
            }

            int tamanhoCodigoEmByte = 0;
            char* falta;
            int byte = 0;
            unsigned char aux = 0;
            int codigoAtual = 0;

            while(fread(&aux, sizeof(char), 1, file))
            {

                int iii = 0;
                while(cods[iii].caracter != aux && &cods[iii] != NULL)
                {
                    iii++;
                }
                if(cods[iii].caracter == aux)
                {

                    byte = byte << cods[iii].tamanho;
                    byte += cods[iii].codigo;
                    tamanhoCodigoEmByte += cods[iii].tamanho;
                    printf("cods[iii].codigo: %d, %d, %c\n",cods[iii].codigo, cods[iii].tamanho, aux);
                    printf("olha esse byte: %d\n", byte);
                    while(tamanhoCodigoEmByte >= 8)
                    {

                        unsigned char byteEscrever = byte >> (tamanhoCodigoEmByte - 8);
                        fwrite(&byteEscrever, sizeof(char), 1, saida);
                        byte = byte << sizeof(int) * 8 - tamanhoCodigoEmByte + 8;
                        byte = byte >> sizeof(int) * 8 - tamanhoCodigoEmByte + 8;
                        tamanhoCodigoEmByte = tamanhoCodigoEmByte - 8;

                    }
                }
            }
            if(tamanhoCodigoEmByte != 0)
            {
                byte = byte << 8 - tamanhoCodigoEmByte;
                fwrite(&byte, sizeof(char), 1, saida);
                fseek(saida, 0, SEEK_SET);
                char t = 8 - tamanhoCodigoEmByte;
                fwrite(&t, sizeof(char), 1, saida);
            }


            fclose(file);
            fclose(saida);



}

int bitExtracted(int number, int k, int p)
{
    return (((1 << k) - 1) & (number >> (p - 1)));
}


void descompactar(char* nomeArquivo)
{
    FILE* entrada = fopen(nomeArquivo, "rb");
    unsigned char lixo;
    fread(&lixo, sizeof(char), 1, entrada);

    short int tamanho;
    fread(&tamanho, sizeof(short int), 1, entrada);

    No* vetorDeNos = (No*)malloc(sizeof(No) * 257);

    unsigned char caracterAtual;
    int i = 0;

    for(; i < tamanho; i++)
    {
        No novoNo;
        novoNo.direita = (No*)malloc(sizeof(No));
        novoNo.esquerda = (No*)malloc(sizeof(No));
        novoNo.esquerda = NULL;
        novoNo.direita  = NULL;
        novoNo.vazio = 0;
        fread(&caracterAtual, sizeof(char), 1, entrada);
        novoNo.caracter = caracterAtual;
        fread(&caracterAtual, sizeof(char), 1, entrada);
        novoNo.frequencia = caracterAtual;
        vetorDeNos[i] = novoNo;
        fread(&caracterAtual, sizeof(char), 1, entrada);
        fread(&caracterAtual, sizeof(char), 1, entrada);
        fread(&caracterAtual, sizeof(char), 1, entrada);
    }

    int* sizeOfCodigos = (int*)malloc(sizeof(int));
    *sizeOfCodigos = tamanho;
    No *raiz = (No*)malloc(sizeof(No));
    *raiz = CriarArvore(vetorDeNos, sizeOfCodigos);

    arvoreToString(raiz);

    int stringSize = (strlen(nomeArquivo) - 7);
    char* newArq = (char*)malloc(240 * sizeof(char));
    strncpy(newArq, nomeArquivo, stringSize);
    newArq[stringSize] = '\0';
    FILE* novoArquivo = fopen(newArq, "wb");

    char ultimoByte = 0;
    No *ponteiro = raiz;

    while(fread(&caracterAtual, sizeof(char), 1, entrada))
    {
        int teste = getc(entrada);
        if (teste == EOF)
                ultimoByte = 1;
        fseek(novoArquivo, -1, SEEK_CUR);

        for(int c = 0; c < 8; c++)
        {
            if (ultimoByte)
                if (c == (8 - lixo))
                    break;

            if(ponteiro->esquerda == NULL && ponteiro->direita == NULL)
            {
                fwrite(&ponteiro->caracter, sizeof(char), 1, novoArquivo);
                ponteiro = raiz;

            }

            int theBit = caracterAtual & 0b10000000;
            if(theBit)
            {
                ponteiro = ponteiro->direita;
            }
            else
            {
                ponteiro = ponteiro->esquerda;
            }

            caracterAtual<<= 1;


        }



    }

     free(sizeOfCodigos);

    free(raiz);

    fclose(entrada);
    fclose(novoArquivo);
}





int main()
{
        char* arquivo = (char*)malloc(240 * sizeof(char));
        printf("Compactador Batata\n");
        printf("--------------------------\n");
        printf("Digite o caminho do arquivo a ser manipulado: \n");
        scanf("%s", arquivo);
        fflush(stdin);
        printf("\n\n Se deseja compactar, digite 1, caso queira descompactar, digite 2 \n");
        char resposta;
        char respostas[1];
        scanf("%s", respostas);
        resposta = respostas[0];

         if(resposta == '1')
        {
             int *tamanhoFuturo = (int*)malloc(sizeof(int));
            *tamanhoFuturo = 0;
            int *tamanhu = (int*)malloc(sizeof(int));
            *tamanhu = 0;

            No* fila = (No*)malloc(sizeof(No)*257);
            No* filaCopia = (No*)malloc(sizeof(No)*257);
            FilaDeNos(tamanhoFuturo, fila, arquivo);
            FilaDeNos(tamanhu, filaCopia, arquivo);

            *filaCopia = *fila;
            No *raiz = (No*)malloc(sizeof(No));
            *raiz = CriarArvore(fila, tamanhoFuturo);
            arvoreToString(raiz);
            printf("\n\n \n\n \n\n \n\n ");


            Codigo* codigos = (int*)malloc(sizeof(int)*257);

            int* qtsCodigos = (int*)malloc(sizeof(int));
            *qtsCodigos = 0;

            char code[1];
            code[0] = '\0';
            int numeroZero = 0;
            gerarCodigos(raiz, code, numeroZero, &codigos, qtsCodigos);

            char* arquivoSaida = (char*)malloc(240 * sizeof(char));
            strcpy(arquivoSaida, arquivo);
            strcat(arquivoSaida, ".batata");

            compactar(arquivoSaida, tamanhu, filaCopia, codigos, arquivo);

            printf("\n\n    COMPACTADO COM SUCESSO!!!");

            free(tamanhoFuturo);
            free(tamanhu);
            free(raiz);
            free(code);

        }
        else if(resposta == '2')
        {
            descompactar(arquivo);
             printf("\n\n    DESCOMPACTADO COM SUCESSO!!!");
        }



        return 0;
}





