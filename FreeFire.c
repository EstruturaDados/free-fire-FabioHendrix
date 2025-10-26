// Inclusão das bibliotecas necessárias pro programa funcionar
#include <stdio.h>
#include <stdlib.h> // Para a função exit() (para fechar o programa)
#include <string.h> // Para funções de string (strcmp, strcpy)

// CONSTANTES E STRUCTS

// Define o tamanho máximo da mochila. Fica mais fácil de mudar depois.
#define CAPACIDADE 10

// Struct do Item
// Define o "molde" de como um item é guardado
struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

// Variáveis globais (acessíveis por todas as funções)
struct Item mochila[CAPACIDADE]; // Onde os itens são guardados
int totalItens = 0; // Controla quantos itens já temos (começa em 0)

// Funções 
void inserirItem();
void removerItem();
void listarItens();
void buscarItem();

// FUNÇÃO PRINCIPAL
int main() {
    int opcao;

    // Loop principal do menu. Fica rodando até o usuário escolher '5' (Sair).
    while (1) {
        printf("\n\n--- MOCHILA DE LOOT ---\n");
        printf("Itens na mochila: %d/%d\n", totalItens, CAPACIDADE);
        printf("1. Adicionar Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("4. Buscar Item\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        // O switch 'escolhe' qual função chamar baseado na 'opcao' do usuário.
        switch (opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 5:
                printf("\nSaindo do sistema de inventário...\n");
                exit(0); // Fecha o programa (0 = saiu sem erro).
            default:
                printf("\n*** Opção inválida! Tente novamente. ***\n");
        }
    }

    return 0;
}

// Função para adicionar um item novo na mochila
void inserirItem() {
    // Checa se a mochila está cheia
    if (totalItens >= CAPACIDADE) {
        printf("\n*** A mochila está cheia! Não é possível adicionar mais itens. ***\n");
        return; // Sai da função e volta pro menu.
    }

    printf("\n--- Adicionando novo item ---\n");
    printf("Nome do item: ");
    // Salva o nome no próximo espaço livre (controlado por 'totalItens')
    scanf("%s", mochila[totalItens].nome); 

    printf("Tipo do item (Arma, Cura, Municao, etc.): ");
    scanf("%s", mochila[totalItens].tipo);

    printf("Quantidade: ");
    scanf("%d", &mochila[totalItens].quantidade);

    // Aumenta o contador, pois um item novo entrou.
    totalItens++;

    printf("\nItem adicionado com sucesso!\n");
    listarItens(); // Mostra a lista atualizada.
}

// Função para tirar um item da mochila (pelo nome)
void removerItem() {
    if (totalItens == 0) {
        printf("\n*** A mochila está vazia! Não há itens para remover. ***\n");
        return;
    }

    char nomeParaRemover[30];
    printf("\nDigite o nome do item a ser removido: ");
    scanf("%s", nomeParaRemover);

    int indiceEncontrado = -1;
    // 1. Procura o item para saber qual a posição (índice) dele.
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeParaRemover) == 0) {
            indiceEncontrado = i;
            break; // Achou. Guarda o 'i' (índice) e para o loop.
        }
    }

    // 2. Se 'indiceEncontrado' for diferente de -1, o item existe.
    if (indiceEncontrado != -1) {
        // 3. Puxa todos os itens (da frente) uma posição para trás, cobrindo o "buraco".
        for (int i = indiceEncontrado; i < totalItens - 1; i++) {
            mochila[i] = mochila[i + 1]; // O item da frente (i+1) copia por cima do item atual (i)
        }
        totalItens--; // Diminui o total de itens.
        printf("\nItem '%s' removido com sucesso!\n", nomeParaRemover);
        listarItens();
    } else {
        printf("\n*** Item '%s' não encontrado na mochila. ***\n", nomeParaRemover);
    }
}

// Função para mostrar tudo que tem na mochila
void listarItens() {
    printf("\n--- Itens na Mochila (%d/%d) ---\n", totalItens, CAPACIDADE);
    if (totalItens == 0) {
        printf("A mochila está vazia.\n");
        return;
    }

    for (int i = 0; i < totalItens; i++) {
        printf("[%d] Nome: %-15s | Tipo: %-10s | Qtd: %d\n",
               i + 1,
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade);
    }
    printf("----------------------------------\n");
}

// Função para procurar um item específico pelo nome
void buscarItem() {
    if (totalItens == 0) {
        printf("\n*** A mochila está vazia! Não há itens para buscar. ***\n");
        return;
    }

    char nomeParaBuscar[30];
    printf("\nDigite o nome do item que deseja buscar: ");
    scanf("%s", nomeParaBuscar);

    for (int i = 0; i < totalItens; i++) {
        // Compara o item atual (mochila[i]) com o nome buscado (strcmp == 0 é igual)
        if (strcmp(mochila[i].nome, nomeParaBuscar) == 0) {
            printf("\n--- Item Encontrado! ---\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            printf("------------------------\n");
            return; // Achou o item, mostra os dados e sai da função.
        }
    }

    // Se o loop 'for' terminou, é porque não achou o item.
    printf("\n*** Item '%s' não foi encontrado na mochila. ***\n", nomeParaBuscar);
}
