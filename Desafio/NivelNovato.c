

 #include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 5
#define TAM_NOME 30
#define TAM_TIPO 20


// STRUCT: São os itens da mochila
// - nome: nome do item
// - tipo: tipo do item (arma, munição, cura, etc.)
// - quantidade: quantidade disponível do item

typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int quantidade;
} Item;


// FUNÇÃO: limparBuffer
// Objetivo: limpar o buffer do teclado após scanf para evitar erros


void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


// FUNÇÃO: inserirItem
// Objetivo: cadastrar um novo item na mochila


void inserirItem(Item **itens, int *numItens) {
    if (*numItens >= MAX_ITENS) {
        printf("Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    // Aloca memória para o novo item
    itens[*numItens] = (Item*) malloc(sizeof(Item));
    if (itens[*numItens] == NULL) {
        printf("Erro ao alocar memória para novo item.\n");
        return;
    }

    limparBuffer(); // limpa o buffer antes de ler strings

    printf("Digite o nome do item: ");
    fgets(itens[*numItens]->nome, TAM_NOME, stdin);
    itens[*numItens]->nome[strcspn(itens[*numItens]->nome, "\n")] = '\0'; // remove \n

    printf("Digite o tipo do item (arma, munição, cura...): ");
    fgets(itens[*numItens]->tipo, TAM_TIPO, stdin);
    itens[*numItens]->tipo[strcspn(itens[*numItens]->tipo, "\n")] = '\0';

    printf("Digite a quantidade do item: ");
    scanf("%d", &itens[*numItens]->quantidade);

    (*numItens)++;
    printf("Item cadastrado com sucesso!\n");
}


// FUNÇÃO: removerItem
// Objetivo: remover um item da mochila pelo nome e liberar a mémoria


void removerItem(Item **itens, int *numItens) {
    if (*numItens == 0) {
        printf("Mochila vazia! Nenhum item para remover.\n");
        return;
    }

    char nomeBusca[TAM_NOME];
    limparBuffer();
    printf("Digite o nome do item que deseja remover: ");
    fgets(nomeBusca, TAM_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < *numItens; i++) {
        if (strcmp(itens[i]->nome, nomeBusca) == 0) {
            free(itens[i]); // libera memória do item desloca os itens seguintes para preencher o espaço.
           
            for (int j = i; j < *numItens - 1; j++) {
                itens[j] = itens[j + 1];
            }
            (*numItens)--;
            printf("Item '%s' removido com sucesso!\n", nomeBusca);
            return;
        }
    }

    printf("Item '%s' não encontrado na mochila.\n", nomeBusca);
}


// FUNÇÃO: listarItens
// Objetivo: exibir todos os itens cadastrados na mochila

void listarItens(Item **itens, int numItens) {
    if (numItens == 0) {
        printf("Mochila vazia!\n");
        return;
    }

    printf("\n=== Itens na Mochila ===\n");
    for (int i = 0; i < numItens; i++) {
        printf("Item %d:\n", i + 1);
        printf("  Nome: %s\n", itens[i]->nome);
        printf("  Tipo: %s\n", itens[i]->tipo);
        printf("  Quantidade: %d\n", itens[i]->quantidade);
    }
    printf("========================\n");
}


// FUNÇÃO: buscarItem
// Objetivo: localizar um item pelo nome e exibir seus dados

void buscarItem(Item **itens, int numItens) {
    if (numItens == 0) {
        printf("Mochila vazia!\n");
        return;
    }

    char nomeBusca[TAM_NOME];
    limparBuffer();
    printf("Digite o nome do item que deseja buscar: ");
    fgets(nomeBusca, TAM_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < numItens; i++) {
        if (strcmp(itens[i]->nome, nomeBusca) == 0) {
            printf("\nItem encontrado:\n");
            printf("  Nome: %s\n", itens[i]->nome);
            printf("  Tipo: %s\n", itens[i]->tipo);
            printf("  Quantidade: %d\n", itens[i]->quantidade);
            return;
        }
    }

    printf("Item '%s' não encontrado na mochila.\n", nomeBusca);
}

// FUNÇÃO: liberarMochila
// Objetivo: liberar toda a memória dos itens

void liberarMochila(Item **itens, int numItens) {
    for (int i = 0; i < numItens; i++) {
        free(itens[i]);
    }
}


// FUNÇÃO PRINCIPAL

int main() {
    Item *mochila[MAX_ITENS]; // Vetor dos itens 
    int numItens = 0;
    int opcao;

    do {
        printf("\n=== Sistema de Mochila ===\n");
        printf("1 - Inserir Item\n");
        printf("2 - Remover Item\n");
        printf("3 - Listar Itens\n");
        printf("4 - Buscar Item\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItem(mochila, &numItens);
                listarItens(mochila, numItens);
                break;
            case 2:
                removerItem(mochila, &numItens);
                listarItens(mochila, numItens);
                break;
            case 3:
                listarItens(mochila, numItens);
                break;
            case 4:
                buscarItem(mochila, numItens);
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    // Libera toda memória antes de sair
    liberarMochila(mochila, numItens);

    return 0;
}
