
#include <stdio.h>
#include <string.h>


typedef struct No
{
    char caracter;
    int frequencia;
    struct No *direita, *esquerda;

} No;


void main()
{

    /*int arroz = 1;
    int *batata = &arroz;
    *batata = 0;
    printf("%d", arroz);*/

    char teste[7];
    strcpy(teste, "batata");

    No fila[7];
    int tamanho = 0;
    No *anterior;

    for(int i = 0; i < 7; i++)
    {
        if(tamanho != 0)
        {
            int existe = 0;
            for(int indice = 0; indice < tamanho; indice++)
            {
                if(fila[indice].caracter == teste[i])
                {
                    fila[indice].frequencia++;
                    int existe = 1;
                }
            }
            if(existe == 0)
            {
                No novoNo;
                novoNo.caracter = teste[i];
                novoNo.frequencia = 1;
                anterior = &novoNo;
                tamanho++;
                fila[i] = novoNo;
            }

        }
        else
        {

            No novoNo;
            novoNo.caracter = teste[i];
            novoNo.frequencia = 1;
            anterior = &novoNo;
            tamanho++;
            fila[i] = novoNo;

        }


    }

    printf("%c, %c, %c, %d, %d, %d", fila[0].caracter, fila[1].caracter, fila[2].caracter, fila[0].frequencia, fila[1].frequencia, fila[2].frequencia);



}






