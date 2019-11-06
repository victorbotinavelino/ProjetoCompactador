
            #include <stdlib.h>
            #include <string.h>
            #include <stdio.h>
            #include <locale.h>
            int main()
            {
                typedef unsigned char byte;
                #define false 0
                #define true !(false)


                typedef struct noArvore{
                    int             frequencia;
                    byte            c;
                    struct noArvore *direito;
                    struct noArvore *esquerdo;
                }noArvore;

                typedef struct noFila{
                    noArvore        *n;
                    struct noFila  *proximo;
                }noFila;

                typedef struct Fila{
                    noFila *primeiro;
                    noFila *ultimo;
                    int     qtd;
                }Fila;

                typedef struct noLista{
                    char valor;
                    struct noLista *proximo;
                    struct noLista *anterior;
                }noLista;

                typedef struct Lista{
                    noLista* primeiro;
                    noLista* ultimo;
                    int     qtd;
                }Lista;

                noLista* novoNoLista(char valor){
                    noLista *novo = malloc(sizeof(noLista));

                    if((novo = malloc(sizeof(*novo))) == NULL) return NULL;

                    novo->valor = valor;
                    novo->proximo = NULL;
                    novo->anterior = NULL;
                }

                void insereNaLista(Lista* l, char c)
                {
                    noLista* novo = novoNoLista(c);
                   if(l->primeiro)
                   {
                       char i = l->ultimo->valor;
                       l->ultimo->proximo = novo;
                       novo->anterior = l->ultimo;
                       l->ultimo = novo;
                       l->qtd++;
                   }
                   else{
                        l->primeiro = novo;
                        l->ultimo = novo;
                        l->qtd++;
                   }
                }

                char removeDaLista(Lista* l)
                {
                    if(l->primeiro)
                    {
                        char valor = l->ultimo->valor;
                        if(l->qtd>1)
                        {
                            noLista* anterior = l->ultimo->anterior;
                            free(l->ultimo);
                            l->ultimo = anterior;
                            l->qtd--;
                        }
                        else
                        {
                           l->primeiro = l->ultimo = NULL;
                           l->qtd--;
                        }
                        return valor;
                    }
                    else
                        return '\0';
                }

                noFila* novoNoFila(noArvore *no){
                    noFila *novo = malloc(sizeof(noFila));

                    if((novo = malloc(sizeof(*novo))) == NULL) return NULL;

                    novo->n = no;
                    novo->proximo = NULL;

                    return novo;
                }

                noArvore* novoNoArvore(byte c, int frequencia, noArvore *esquerda, noArvore *direita)
                {
                    noArvore *novo;

                    if ( ( novo = malloc(sizeof(*novo)) ) == NULL ) return NULL;

                    novo->c = c;
                    novo->frequencia = frequencia;
                    novo->esquerdo = esquerda;
                    novo->direito = direita;

                    return novo;
                }

                void noArvoreToString(noArvore* no)
                {
                    printf("[%c / %d]", no->c, no->frequencia);
                }

                void arvoreToString(noArvore* raiz)
                {
                    printf("[%d-%d", raiz->c, raiz->frequencia);
                    if(raiz->esquerdo)
                    {
                        printf(" -> ");
                        arvoreToString(raiz->esquerdo);
                    }
                    if(raiz->direito)
                    {
                        printf(" -> ");
                        arvoreToString(raiz->direito);
                    }
                    printf("]");
                }

                void insereNaFila(noFila*no, Fila *l)
                {
                    if(!l->primeiro){ //Se estiver vazia
                        l->primeiro = no;
                        l->ultimo = no;
                        l->qtd++;
                    }
                    else if(no->n->frequencia < l->primeiro->n->frequencia){ //Se for menos frequente que o primeiro
                        no->proximo = l->primeiro;
                        l->primeiro = no;
                        l->qtd++;
                    }
                    else if(no->n->frequencia >= l->ultimo->n->frequencia){ //Se for mais frequente que o ultimo
                        l->ultimo->proximo = no;
                        l->ultimo = no;
                        l->qtd++;
                    }
                    else{//Se não, precisamos procurar
                       noFila* atual = l->primeiro;
                       noFila* anterior;
                       int achou = false;
                       while(!achou){
                           if(atual->n->frequencia > no->n->frequencia){
                               anterior->proximo = no;
                               no->proximo = atual;
                               l->qtd++;
                               achou = true;
                           }
                           else{
                           anterior = atual;
                           atual = atual->proximo;
                           }
                       }
                    }
                }

                noArvore* removerFila(Fila* l){
                    noArvore* aux = l->primeiro->n;
                    l->primeiro = l->primeiro->proximo;

                    l->qtd--;
                    return aux;
                }

                void constroiArvore(Fila* l){
                    while(l->qtd > 1){
                        noArvore* primeiro = removerFila(l);
                        noArvore* segundo = removerFila(l);
                        int freq = primeiro->frequencia + segundo->frequencia;

                        noArvore* raiz;
                        raiz = novoNoArvore('\0', freq, primeiro, segundo);
                        noFila* noRaiz = novoNoFila(raiz);
                        insereNaFila(noRaiz, l);
                    }
                }

                void pegaFrequencia(FILE* arquivo, int* listaBytes )
                {
                    byte c;

                    while(fread(&c, 1,1,arquivo)>= 1)
                    {
                        listaBytes[c]++;
                    }
                    rewind(arquivo);
                }
                char getCodigo(byte c, Lista* codigo, noArvore* raiz)
                {
                    char encontrado = false;
                    if(raiz->c == c && !(raiz->direito ||raiz->esquerdo)){
                        noLista* atual = codigo->primeiro;
                        while(atual){
                            //printf("%c", atual->valor);
                            atual = atual->proximo;
                        }
                        return true;
                    }
                    else if(raiz->esquerdo){
                        insereNaLista(codigo, '0');
                        encontrado = getCodigo(c, codigo, raiz->esquerdo);
                    }
                    if(raiz->direito && !encontrado){
                        insereNaLista(codigo, '1');
                        encontrado = getCodigo(c, codigo, raiz->direito);
                    }
                    if(!encontrado){
                        char aux = removeDaLista(codigo);
                    }
                    return encontrado;

                }

                void bin(unsigned n)
                {
                    unsigned i = n;
                    while(i != 1){
                        printf("%d", i%2);
                        i = i/2;
                    }
                }


                void gerarArquivoCompactado(FILE* entrada, noArvore* raiz, FILE* saida)
                {
                    byte c;
                    unsigned tamanho = 0;
                    byte aux = 0;
                    fseek(saida, sizeof(unsigned int), SEEK_CUR);
                    while(fread(&c, 1,1,entrada)>= 1)
                    {
                        Lista codigo = {NULL,NULL, 0};
                        //printf("\n%d:", c);
                        getCodigo(c, &codigo, raiz);
                        noLista* atual = codigo.primeiro;
                        while(atual)
                        {
                           if(atual->valor == '1')
                            {
                                aux = aux|(1<<(tamanho % 8));
                            }
                            tamanho++;
                            if(tamanho%8 == 0)
                            {
                                //printf("\nFORMOU UM BYTE: %d", aux);
                                fwrite(&aux, 1, 1, saida);
                                aux = 0;
                            }
                            atual = atual->proximo;
                        }
                    }
                    //printf("\nRESTO: %d - %d", aux, tamanho%8);
                    fwrite(&aux,1,1,saida);
                    fseek(saida, 256 * sizeof(unsigned int), SEEK_SET);
                    fwrite(&tamanho, 1, sizeof(unsigned), saida);
                }

                void FreeHuffmanTree(noArvore *n)
                {
                    if (!n) return;
                    else
                    {
                        noArvore *esquerdo = n->esquerdo;
                        noArvore *direito = n->direito;
                        free(n);
                        FreeHuffmanTree(esquerdo);
                        FreeHuffmanTree(direito);
                    }
                }




                void comprimir(FILE* arquivo){
                    FILE* saida = fopen("algo.jj", "wb");
                    unsigned listaBytes[256] = {0};
                    pegaFrequencia(arquivo, listaBytes);

                    Fila huffman = {NULL, NULL, 0};

                    for(int i = 0; i < 256; i++)
                    {
                        if(listaBytes[i]){
                            noArvore* novoArvore;
                            novoArvore = novoNoArvore(i, listaBytes[i],NULL ,NULL );
                            noFila* novoFila = novoNoFila(novoArvore);
                            insereNaFila(novoFila, &huffman);
                        }
                    }

                    constroiArvore(&huffman);
                    noArvore* raiz = removerFila(&huffman);
                    fwrite(listaBytes, 256, sizeof(listaBytes[0]), saida);
                    gerarArquivoCompactado(arquivo, raiz, saida);
                    fclose(arquivo);
                    fclose(saida);
                    FreeHuffmanTree(raiz);
                }

                void descomprimir(FILE* arquivo)
                {
                    FILE* saida = fopen("Descompactado.txt", "wb");
                    unsigned listaBytes[256] = {0};
                    fread(listaBytes, 256, sizeof(listaBytes[0]), arquivo);
                    Fila huffman = {NULL, NULL, 0};

                    for(int i = 0; i < 256; i++)
                    {
                        if(listaBytes[i]){
                            noArvore* novoArvore;
                            novoArvore = novoNoArvore(i, listaBytes[i],NULL ,NULL );
                            noFila* novoFila = novoNoFila(novoArvore);
                            insereNaFila(novoFila, &huffman);
                        }
                    }
                    constroiArvore(&huffman);

                    noArvore* raiz = removerFila(&huffman);
                    //arvoreToString(raiz);
                    unsigned tamanho;
                    fread(&tamanho, 1, sizeof(tamanho), arquivo);
                    unsigned posicao = 0;
                    byte aux = 0;

                    while(posicao < tamanho)
                    {
                        noArvore* atual = raiz;
                        while(atual->esquerdo || atual->direito)
                        {
                            if(posicao % 8 == 0)
                            {
                                fread(&aux, 1, 1, arquivo);
                            }
                            int a = aux & (1 << posicao%8);
                            if(a == 0)
                            {
                                atual = atual->esquerdo;
                            }
                            else
                            {
                                atual = atual->direito;
                            }
                            posicao++;
                        }
                        fwrite(&(atual->c), 1,1, saida);
                }
                fclose(arquivo);
                fclose(saida);
                FreeHuffmanTree(raiz);
            }


                char* oq = "Comprimir";
                printf("Comprimir ou Descomprimir?\n");
                if(oq == "Comprimir")
                {
                   FILE *arq = fopen("algo.txt", "rb");
                    (!arq) ? printf("Erro ao ler o arquivo") : NULL == NULL ;
                    comprimir(arq);
                }
                else
                {
                    FILE *arq = fopen("algo.jj", "rb");
                    (!arq) ? printf("Erro ao ler o arquivo") : NULL == NULL;
                    descomprimir(arq);
                }
                return 0;
            }

