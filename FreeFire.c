// Inclusão das bibliotecas necessárias pro programa funcionar
#include <stdio.h>
#include <stdlib.h> // Para malloc, free (memória)
#include <string.h> // Para strcmp (comparar strings)
#include <time.h>   // (Não está sendo usado, mas é padrão)

// ESTRUTURAS DE DADOS

#define CAPACIDADE_VETOR 10 // Define o tamanho fixo da mochila-vetor

// Struct base para um item (o que vai ser guardado)
struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

// Struct do Nó
struct No {
    struct Item dados;      // O item que o nó está guardando
    struct No* proximo;     // Ponteiro que aponta para o próximo nó
};


// MOCHILAS (Variáveis Globais)

// Mochila 1: Vetor 
struct Item mochilaVetor[CAPACIDADE_VETOR];
int totalItensVetor = 0; // Controla quantos itens tem no vetor
int vetorOrdenado = 0; // Avisa se o vetor está ordenado (0=não, 1=sim)

// Mochila 2: Lista Encadeada
struct No* mochilaLista = NULL; // Ponteiro para o começo da lista (NULL = vazia)
int totalItensLista = 0;

// Contador para testes de busca
int comparacoes = 0;


// Funções 

// Menus
void gerenciarVetor();
void gerenciarLista();

// Funções do Vetor
void inserirItemVetor();
void removerItemVetor();
void listarItensVetor();
void ordenarVetor();
void buscarSequencialVetor();
void buscarBinariaVetor();

// Funções da Lista
void inserirItemLista();
void removerItemLista();
void listarItensLista();
void buscarSequencialLista();
void liberarLista(); // Limpar a memória


// FUNÇÃO PRINCIPAL
int main() {
    int opcao;
    while (1) {
        printf("\n\n--- COMPARATIVO DE ESTRUTURAS DE DADOS ---\n");
        printf("Qual mochila você quer gerenciar?\n");
        printf("1. Mochila com Vetor (Lista Sequencial)\n");
        printf("2. Mochila com Lista Encadeada\n");
        printf("3. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                gerenciarVetor();
                break;
            case 2:
                gerenciarLista();
                break;
            case 3:
                liberarLista(); // Limpa a memória da lista antes de sair (MUITO IMPORTANTE)
                printf("Saindo do programa...\n");
                return 0;
            default:
                printf("Opção inválida!\n");
        }
    }
}

// GERENCIADORES DE MENU 

void gerenciarVetor() {
    int opcao;
    printf("\n-- GERENCIANDO MOCHILA (VETOR) --\n");
    printf("1. Inserir | 2. Remover | 3. Listar | 4. Ordenar | 5. Busca Sequencial | 6. Busca Binária | 7. Voltar\n");
    printf("Escolha: ");
    scanf("%d", &opcao);

    switch(opcao) {
        case 1: inserirItemVetor(); break;
        case 2: removerItemVetor(); break;
        case 3: listarItensVetor(); break;
        case 4: ordenarVetor(); break;
        case 5: buscarSequencialVetor(); break;
        case 6: buscarBinariaVetor(); break;
        case 7: return;
        default: printf("Opção inválida!\n");
    }
}

void gerenciarLista() {
    int opcao;
    printf("\n-- GERENCIANDO MOCHILA (LISTA ENCADEADA) --\n");
    printf("1. Inserir | 2. Remover | 3. Listar | 4. Busca Sequencial | 5. Voltar\n");
    printf("Escolha: ");
    scanf("%d", &opcao);

    switch(opcao) {
        case 1: inserirItemLista(); break;
        case 2: removerItemLista(); break;
        case 3: listarItensLista(); break;
        case 4: buscarSequencialLista(); break;
        case 5: return;
        default: printf("Opção inválida!\n");
    }
}


// FUNÇÕES DO VETOR

void inserirItemVetor() {
    if (totalItensVetor >= CAPACIDADE_VETOR) {
        printf("Mochila (vetor) cheia!\n");
        return;
    }
    printf("Nome, Tipo, Quantidade: ");
    scanf("%s %s %d", mochilaVetor[totalItensVetor].nome, mochilaVetor[totalItensVetor].tipo, &mochilaVetor[totalItensVetor].quantidade);
    totalItensVetor++;
    vetorOrdenado = 0; // Se inseriu algo novo, a ordem (se existia) foi quebrada
    printf("Item inserido!\n");
}

void removerItemVetor() {
    // acha o índice e puxa os outros
    char nome[30];
    printf("Nome do item a remover: ");
    scanf("%s", nome);

    int indice = -1;
    for (int i = 0; i < totalItensVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            indice = i;
            break;
        }
    }

    if (indice != -1) {
        // Puxa os itens para cobrir o buraco
        for (int i = indice; i < totalItensVetor - 1; i++) {
            mochilaVetor[i] = mochilaVetor[i+1];
        }
        totalItensVetor--;
        printf("Item removido!\n");
    } else {
        printf("Item não encontrado.\n");
    }
}

void listarItensVetor() {
    printf("\n--- Itens na Mochila (Vetor) ---\n");
    for (int i = 0; i < totalItensVetor; i++) {
        printf("Nome: %s, Tipo: %s, Qtd: %d\n", mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
    }
}

// Ordena o vetor por nome (usando Bubble Sort)
void ordenarVetor() {
    if (totalItensVetor < 2) {
        printf("Não há itens suficientes para ordenar.\n");
        return;
    }
    struct Item temp; // Variável temporária para a troca
    for (int i = 0; i < totalItensVetor - 1; i++) {
        for (int j = 0; j < totalItensVetor - 1 - i; j++) {
            // Compara o item [j] com o [j+1]
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j+1].nome) > 0) {
                // Se for > 0, eles estão fora de ordem, então troca
                temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j+1];
                mochilaVetor[j+1] = temp;
            }
        }
    }
    vetorOrdenado = 1; // Avisa o sistema que o vetor agora está ordenado
    printf("Mochila (vetor) ordenada por nome!\n");
}

// Busca um item olhando um por um (do início ao fim)
void buscarSequencialVetor() {
    char nome[30];
    printf("Nome do item a buscar: ");
    scanf("%s", nome);
    
    comparacoes = 0; // Zera o contador de teste
    for (int i = 0; i < totalItensVetor; i++) {
        comparacoes++; // Conta +1 para cada item olhado
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            printf("Item encontrado! | Comparações: %d\n", comparacoes);
            return;
        }
    }
    printf("Item não encontrado. | Comparações: %d\n", comparacoes);
}

// Busca um item "quebrando" o vetor no meio.
void buscarBinariaVetor() {
    if (!vetorOrdenado) { // Checa a flag (se for 0, dá erro)
        printf("ERRO: A mochila precisa ser ordenada antes de usar a busca binária!\n");
        return;
    }

    char nome[30];
    printf("Nome do item a buscar (Busca Binária): ");
    scanf("%s", nome);

    comparacoes = 0; // Zera o contador
    int inicio = 0, fim = totalItensVetor - 1, meio;

    while (inicio <= fim) {
        meio = inicio + (fim - inicio) / 2; // Acha o índice do meio
        comparacoes++; // Conta a comparação
        int res = strcmp(mochilaVetor[meio].nome, nome);

        if (res == 0) { // Encontrou!
            printf("Item encontrado! | Comparações: %d\n", comparacoes);
            return;
        }
        if (res < 0) { // O nome do meio vem ANTES do nome buscado (alfabeticamente)
            inicio = meio + 1; // Joga fora a metade da esquerda
        } else { // O nome do meio vem DEPOIS
            fim = meio - 1; // Joga fora a metade da direita
        }
    }

    printf("Item não encontrado. | Comparações: %d\n", comparacoes);
}

// FUNÇÕES DA LISTA ENCADEADA

// Insere um item novo (sempre no começo da lista)
void inserirItemLista() {
    // 1. Pede memória pro novo nó
    struct No* novoNo = (struct No*) malloc(sizeof(struct No));
    if (novoNo == NULL) {
        printf("Erro de alocação de memória!\n");
        return;
    }
    
    // 2. Preenche os dados do item
    printf("Nome, Tipo, Quantidade: ");
    scanf("%s %s %d", novoNo->dados.nome, novoNo->dados.tipo, &novoNo->dados.quantidade);

    // 3. O 'proximo' do novo nó aponta para quem ERA o primeiro (a mochilaLista antiga)
    novoNo->proximo = mochilaLista;
    
    // 4. A mochilaLista (cabeça) passa a ser o novo nó
    mochilaLista = novoNo;
    
    totalItensLista++;
    printf("Item inserido!\n");
}

void removerItemLista() {
    if (mochilaLista == NULL) {
        printf("Mochila (lista) vazia!\n");
        return;
    }

    char nome[30];
    printf("Nome do item a remover: ");
    scanf("%s", nome);

    struct No* atual = mochilaLista;
    struct No* anterior = NULL;

    // Procura o nó, mas guarda o anterior
    while (atual != NULL && strcmp(atual->dados.nome, nome) != 0) {
        anterior = atual; // O 'anterior' vira o 'atual'
        atual = atual->proximo; // O 'atual' avança
    }

    // Se o loop acabou e 'atual' é NULL, não achou
    if (atual == NULL) {
        printf("Item não encontrado.\n");
        return;
    }

    // Se achou, 'atual' é o nó para remover.
    // Se 'anterior' é NULL, o item a remover é o primeiro da lista
    if (anterior == NULL) {
        mochilaLista = atual->proximo; // A cabeça da lista vira o segundo item
    } else { // Se 'anterior' existe (item no meio ou fim)
        anterior->proximo = atual->proximo; // O 'anterior' pula o 'atual' e aponta pro próximo
    }

    free(atual); // Limpa a memória do 'atual' (que foi pulado)
    totalItensLista--;
    printf("Item removido!\n");
}

void listarItensLista() {
    printf("\n--- Itens na Mochila (Lista Encadeada) ---\n");
    struct No* atual = mochilaLista; // Ponteiro temporário 
    while (atual != NULL) { // Enquanto não chegar no fim (NULL)
        printf("Nome: %s, Tipo: %s, Qtd: %d\n", atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo; // Avança o ponteiro 'atual' para o próximo
    }
}

// Busca na lista (igual ao vetor, um por um)
void buscarSequencialLista() {
    if (mochilaLista == NULL) {
        printf("Mochila (lista) vazia!\n");
        return;
    }

    char nome[30];
    printf("Nome do item a buscar: ");
    scanf("%s", nome);

    comparacoes = 0;
    struct No* atual = mochilaLista;
    while (atual != NULL) { // Caminha pela lista
        comparacoes++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            printf("Item encontrado! | Comparações: %d\n", comparacoes);
            return;
        }
        atual = atual->proximo; // Vai para o próximo
    }
    printf("Item não encontrado. | Comparações: %d\n", comparacoes);
}

// Limpa a memória de toda a lista 
void liberarLista() {
    struct No* atual = mochilaLista;
    struct No* proximo;
    while (atual != NULL) {
        proximo = atual->proximo; // 1. Guarda quem é o próximo
        free(atual); // 2. Limpa o atual
        atual = proximo; // 3. O atual vira o próximo (que guardamos)
    }
    mochilaLista = NULL; // Avisa que a lista está vazia
}
