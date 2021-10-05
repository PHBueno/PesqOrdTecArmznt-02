#include <stdio.h>
#include <stdlib.h>

typedef struct No
{
    int dado;
    struct No *esquerda;
    struct No *direita;
}NO;

NO *criaArvore(NO *arv)
{
    NO *novo = NULL;

    return novo;
}

NO *criaNo(int dado)
{
    NO *novo = (NO*) malloc(sizeof(NO));
    if(novo == NULL)
    {
        printf("Erro ao alocar memória\n");
        exit(1);
    }
    else
    {
        novo->dado = dado;
        novo->direita = NULL;
        novo->esquerda = NULL;
    }
}

NO *insere(NO *raiz, int dado)
{
    if(raiz == NULL)
    {
        NO *novo = criaNo(dado);
        return novo;
    }
    else
    {
        if(dado > raiz->dado)
        {
            raiz->direita = insere(raiz->direita, dado);
        }
        else
        {
            raiz->esquerda = insere(raiz->esquerda, dado);
        }
    }
    return raiz;
}

// Vai para a subarvore da Esquerda e procura pelo menor valor a direita
NO *maximoValor(NO *raiz)
{
    if(raiz != NULL)
    {
        NO *auxiliar = raiz->esquerda;
        while(auxiliar->direita != NULL)
        {
            auxiliar = auxiliar->direita;
        }
        return auxiliar;
    }
    return NULL;
}

NO *removeNo(NO *raiz, int dado)
{
    if(raiz == NULL)
    {
        printf("A árvore está vazia!!\n");
        return NULL;
    }
    else
    {
        // se o valor informado for o valor Raiz
        if(raiz->dado == dado)
        {
            // O nó não possui nenhum filho (nó folha)
            if(raiz->direita == NULL && raiz->esquerda == NULL)
            {
                free(raiz);
                return NULL;
            }
            else
            {   // Nó que possui um filho a esquerda
                if(raiz->direita == NULL && raiz->esquerda != NULL)
                {
                    NO* auxiliar = raiz->esquerda;
                    free(raiz);
                    return auxiliar;
                }
                // Nó que possui um filho a direita
                else if(raiz->direita != NULL && raiz->esquerda == NULL)
                {
                    NO *auxiliar = raiz->direita;
                    free(raiz);
                    return auxiliar;
                }
                // Nó que possui um filho a direita e um filho a esquerda
                if(raiz->direita != NULL && raiz->esquerda != NULL)
                {
                    NO *maximo = maximoValor(raiz);
                    raiz->dado = maximo->dado;
                    maximo->dado = dado;
                    raiz->esquerda = removeNo(raiz->esquerda, dado);
                    return raiz;
                }
            }
        }
        else
        {
            if(dado < raiz->dado)
            {
                raiz->esquerda = removeNo(raiz->esquerda, dado);
            }
            else
            {
                raiz->direita = removeNo(raiz->direita, dado);
            }
            return raiz;
        }
    }
}

void imprime(NO *raiz)
{
    if(raiz != NULL)
    {
        imprime(raiz->esquerda);
        printf("%d ", raiz->dado);
        imprime(raiz->direita);
    }
}

void libera(NO *raiz)
{
    if(raiz != NULL)
    {
        libera(raiz->esquerda);
        libera(raiz->direita);
        free(raiz);
    }
}

void menu()
{
    printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    printf("1 - Inserir\n2 - Remover\n3 - Imprimir\n4 - Sair");
    printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
}

void main()
{
    NO *raiz = criaArvore(raiz);
    int opcao;
    do
    {
        menu();
        printf("Informe a opção desejada: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1: // Inserir
        {
            printf("\n");
            int valor;
            printf("Informe o valor para INSERIR: ");
            scanf("%d", &valor);
            raiz = insere(raiz, valor);
            break;
        }
        case 2: // Remover
        {
            printf("\n");
            int valor;
            printf("Informe o valor para REMOVER: ");
            scanf("%d", &valor);
            raiz = removeNo(raiz, valor);
            break;
        }
        case 3: // Imprimir
        {
            printf("\nSua árvore:\n");
            imprime(raiz);
            printf("\n");
            break;
        }
        case 4: // Sair
        {
            printf("\nSua Arvore será liberada!\nAté mais!!\n");
            libera(raiz);
            break;
        }
        default:
            printf("Entrada invalida!!\nPor favor, tente outra vez!\n");
            break;
        }
    } while (opcao != 4);
}
