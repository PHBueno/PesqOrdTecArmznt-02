#include <stdio.h>
#include <stdlib.h>
/*
pensei em fazer toda que busca for procura ele vai incrementar os ponteiro numa soma dai ese resultado sera numero de vezes ou passos que precisou
- O grupo deverá escolher um dos algoritmos de busca estudados em aula.

- Antes de escolher a técnica de pesquisa a ser utilizada, o grupo deverá discutir com o professor (em aula).

- O grupo deverá utilizar funções recursivas para a implementação do programa.

- O grupo deverá considerar a característica do algoritmo a ser utilizado antes da implementação. Por exemplo, se for utilizado o algoritmo de busca binária, o grupo deverá garantir que os dados inseridos (números) estão ordenados.

- O grupo poderá melhorar o programa, incluindo novas funcionalidades, desde que tenha como demonstrar a utilização dos algoritmos de pesquisa (busca) utilizado.

- Podem ser utilizadas diversas estruturas de dados, além de vetores (árvores, por exemplo).

- Na apresentação (em aula) ao professor, o grupo deverá ter clareza no funcionamento do algoritmo de busca utilizado. O professor poderá realizar perguntar específicas sobre o funcionamento do algoritmo utilizado.


Descrição: desenvolver um programa em C que leia “N” números inteiros e armazene em memória. Após a leitura desses números, o usuário deverá ter a opção de localizar um número (do conjunto inserido). O programa deverá realizar a pesquisa e indicar se o número foi localizado ou não, indicar a posição que o número

se encontra (índice) e quantas comparações foram necessárias para localizar o número.

 */

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

void imprimirEmOrdem(NO *raiz){
    if(raiz != NULL){
        imprimirEmOrdem(raiz->esquerda);
        printf("\n%d", raiz->dado);
        imprimirEmOrdem(raiz->direita);
    }
}


void imprimirPreOrdem(NO *raiz){
    if(raiz != NULL){
        printf("\n%d", raiz->dado);
        imprimirPreOrdem(raiz->esquerda);
        imprimirPreOrdem(raiz->direita);
    }
}

void imprimirPosOrdem(NO *raiz){
    if(raiz != NULL){
        imprimirPosOrdem(raiz->esquerda);
        imprimirPosOrdem(raiz->direita);
        printf("\n%d", raiz->dado);
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
    printf("\n1 - Inserir\n2 - Remover\n3 - Imprimir\n0 - Sair \n4 -Imprimir em Ordem \n5 -Imprimir Pre Ordem,\n6 Imprimir em Pos Ordem ");
    printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
}


int main()
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
            printf("\nSua arvore:\n");
            imprime(raiz);
            printf("\n");
            break;
        }
        case 4:
        {
        	printf("\nImprimindo em ordem:  ");
        	imprimirEmOrdem(raiz);
        	printf("\n");
        	break;


		}
        case 5:
        {
          printf("\nImprimindo Pre Ordem: ");
		  imprimirPreOrdem(raiz);
		  printf("\n");
		  break;


		}

        case 6:
	    {
	    	 printf("\nImprimindo em Pos Ordem: ");
	    	 imprimirPosOrdem(raiz);
	    	 printf("\n");
	    	 break;


		}

        case 0: // Sair
        {
            printf("\nSua Arvore será liberada!\nAté mais!!\n");
            libera(raiz);
            break;
        }
        default:
            printf("Entrada invalida!!\nPor favor, tente outra vez!\n");
            break;
        }
    } while (opcao != 0);


 	return 0 ;


}

 