// Inclusão das bibliotecas necessárias pro programa funcionar
#include <stdio.h>
#include <stdlib.h> // Para malloc, free, etc. (embora aqui só use 'return 0')
#include <string.h> // Para strcmp, strcpy, strcspn
#include <time.h>   // Para medir o tempo (clock)

// ESTRUTURAS E CONSTANTES
#define MAX_COMPONENTES 20 // Limite máximo de componentes no vetor

// Struct para guardar os dados de um componente
struct Componente {
    char nome[30];
    char tipo[20];
    int prioridade;
};

// VARIÁVEIS GLOBAIS
struct Componente torre[MAX_COMPONENTES]; // O vetor principal
int totalComponentes = 0; // Controla quantos componentes já foram cadastrados
long long comparacoes = 0; // Para contar quantas comparações os 'sorts' fazem
int ordenadoPorNome = 0; // Flag (0=não, 1=sim) para saber se a busca binária pode ser usada

// Funções
void cadastrarComponentes();
void mostrarComponentes();
void bubbleSortNome();
void insertionSortTipo();
void selectionSortPrioridade();
void buscaBinariaPorNome();
// Função especial que recebe outra função como parâmetro (ponteiro de função)
void medirTempo(void (*funcaoOrdenacao)(), const char* nomeAlgoritmo);
void limparBufferEntrada(); // Função para limpar o 'enter' que sobra do scanf

// FUNÇÃO PRINCIPAL
int main() {
    int opcao;

    printf("--- MISSÃO FINAL: TORRE DE FUGA ---\n");
    cadastrarComponentes(); // Começa cadastrando os itens

    while (1) { // Loop infinito do menu
        printf("\n\n--- PAINEL DE ESTRATÉGIA ---\n");
        printf("Escolha o critério de montagem (ordenação):\n");
        printf("1. Ordenar por NOME (Bubble Sort)\n");
        printf("2. Ordenar por TIPO (Insertion Sort)\n");
        printf("3. Ordenar por PRIORIDADE (Selection Sort)\n");
        printf("4. ATIVAR TORRE (Buscar Chip Central por Nome)\n");
        printf("5. Sair da Simulação\n");
        printf("Sua escolha, comandante: ");
        scanf("%d", &opcao);
        limparBufferEntrada(); // Limpa o 'enter' que o scanf deixou

        switch (opcao) {
            case 1:
                // Passa a FUNÇÃO bubbleSortNome como argumento
                medirTempo(bubbleSortNome, "Bubble Sort por Nome");
                break;
            case 2:
                medirTempo(insertionSortTipo, "Insertion Sort por Tipo");
                break;
            case 3:
                medirTempo(selectionSortPrioridade, "Selection Sort por Prioridade");
                break;
            case 4:
                buscaBinariaPorNome();
                break;
            case 5:
                printf("\nSimulação encerrada.\n");
                return 0; // Sai do programa
            default:
                printf("\n*** Comando inválido! Tente novamente. ***\n");
        }
        // Se a opção foi um 'sort', mostra o resultado
        if (opcao >= 1 && opcao <= 3) {
            mostrarComponentes();
        }
    }
}

// FUNÇÕES DE GERENCIAMENTO E INTERFACE

// Pede os dados dos componentes ao usuário
void cadastrarComponentes() {
    printf("Cadastre até %d componentes para a torre.\n", MAX_COMPONENTES);
    printf("Digite 'fim' no nome para parar.\n");
    while (totalComponentes < MAX_COMPONENTES) {
        printf("\n--- Componente %d ---\n", totalComponentes + 1);
        printf("Nome: ");
        fgets(torre[totalComponentes].nome, 30, stdin);
        // O fgets pega o 'enter' (\n) também. Esta linha acha o '\n' e troca por '\0' (fim da string).
        torre[totalComponentes].nome[strcspn(torre[totalComponentes].nome, "\n")] = 0; 

        // Checa se o usuário digitou 'fim' para parar
        if (strcmp(torre[totalComponentes].nome, "fim") == 0) break;

        printf("Tipo (Controle, Suporte, Propulsao): ");
        fgets(torre[totalComponentes].tipo, 20, stdin);
        torre[totalComponentes].tipo[strcspn(torre[totalComponentes].tipo, "\n")] = 0; // Remove o \n

        printf("Prioridade (1-10): ");
        scanf("%d", &torre[totalComponentes].prioridade);
        limparBufferEntrada(); // Limpa o 'enter' que o scanf deixou

        totalComponentes++; // Aumenta o contador
    }
}

// Mostra a lista de componentes na tela
void mostrarComponentes() {
    printf("\n--- ORDEM DE MONTAGEM ATUAL ---\n");
    for (int i = 0; i < totalComponentes; i++) {
        printf("[%02d] Nome: %-20s | Tipo: %-15s | Prio: %d\n", i + 1,
               torre[i].nome, torre[i].tipo, torre[i].prioridade);
    }
    printf("----------------------------------\n");
}

// Função para limpar caracteres extras do buffer de entrada, principalmente o 'enter'
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Lê e descarta até achar o 'enter' ou o fim do arquivo
}

// FUNÇÕES DE ORDENAÇÃO

// Ordena por Nome (Bubble Sort)
void bubbleSortNome() {
    comparacoes = 0;
    ordenadoPorNome = 0; // Zera a flag (vai ser setada no fim)
    struct Componente temp; // Variável para a troca
    for (int i = 0; i < totalComponentes - 1; i++) {
        for (int j = 0; j < totalComponentes - 1 - i; j++) {
            comparacoes++; // Conta a comparação
            // Se a string [j] vem DEPOIS (>) da [j+1]
            if (strcmp(torre[j].nome, torre[j + 1].nome) > 0) {
                // Troca eles de lugar
                temp = torre[j];
                torre[j] = torre[j + 1];
                torre[j + 1] = temp;
            }
        }
    }
    ordenadoPorNome = 1; // avisa que o vetor está ordenado por nome
}

// Ordena por Tipo (Insertion Sort)
void insertionSortTipo() {
    comparacoes = 0;
    ordenadoPorNome = 0; // Ordenar por tipo 'quebra' a ordem por nome
    struct Componente chave;
    int j;
    for (int i = 1; i < totalComponentes; i++) {
        chave = torre[i]; // Pega o item 'i'
        j = i - 1;
        // Puxa os itens maiores que a 'chave' para a direita
        while (j >= 0) {
            comparacoes++; // Conta a comparação
            if (strcmp(chave.tipo, torre[j].tipo) < 0) {
                torre[j + 1] = torre[j]; // Joga o [j] pra frente
                j = j - 1;
            } else {
                break; // Achou o lugar certo
            }
        }
        torre[j + 1] = chave; // Insere a 'chave' no buraco
    }
}

// Ordena por Prioridade (Selection Sort)
void selectionSortPrioridade() {
    comparacoes = 0;
    ordenadoPorNome = 0; // 'Quebra' a ordem por nome
    int indiceMin;
    struct Componente temp;
    for (int i = 0; i < totalComponentes - 1; i++) {
        indiceMin = i; // Assume que o 'i' é o menor
        // Procura o menor no resto do vetor
        for (int j = i + 1; j < totalComponentes; j++) {
            comparacoes++;
            if (torre[j].prioridade < torre[indiceMin].prioridade) {
                indiceMin = j; // Achou um menor ainda, guarda o índice
            }
        }
        // Se o menor não for o 'i', troca eles
        if (indiceMin != i) {
            temp = torre[i];
            torre[i] = torre[indiceMin];
            torre[indiceMin] = temp;
        }
    }
}

// FUNÇÃO DE BUSCA

// Busca Binária (só funciona se ordenadoPorNome == 1)
void buscaBinariaPorNome() {
    // Checa se o vetor está ordenado por nome
    if (!ordenadoPorNome) {
        printf("\n*** ALERTA: Execute a ordenação por NOME (opção 1) antes de ativar a torre! ***\n");
        return;
    }
    char chave[30] = "ChipCentral"; // O item que queremos achar
    printf("\nBuscando componente de ativação: '%s'...\n", chave);
    
    int comps = 0; // Contador de comparações só da busca
    int inicio = 0, fim = totalComponentes - 1, meio;

    while (inicio <= fim) {
        meio = inicio + (fim - inicio) / 2; // Acha o meio
        comps++;
        int res = strcmp(torre[meio].nome, chave);
        if (res == 0) { // Achou! (strcmp == 0 é igual)
            printf("SUCESSO! Componente-chave encontrado na posição %d.\n", meio + 1);
            printf("A torre de fuga pode ser ativada!\n");
            printf("Comparações na busca: %d\n", comps);
            return;
        }
        // Se o 'meio' vem antes (< 0) da 'chave', joga fora a metade esquerda
        if (res < 0) inicio = meio + 1;
        // Se o 'meio' vem depois (> 0), joga fora a metade direita
        else fim = meio - 1;
    }
    printf("FALHA! Componente-chave '%s' não encontrado. Montagem impossível.\n", chave);
    printf("Comparações na busca: %d\n", comps);
}

// FUNÇÃO DE ANÁLISE DE DESEMPENHO

// Mede o tempo de um algoritmo de ordenação
// Recebe um ponteiro para a função que vai rodar (ex: bubbleSortNome)
void medirTempo(void (*funcaoOrdenacao)(), const char* nomeAlgoritmo) {
    clock_t inicio, fim; // Variáveis para guardar o tempo
    double tempoGasto;

    inicio = clock();   // 1. Marca o tempo de início
    funcaoOrdenacao();  // 2. RODA A FUNÇÃO que foi passada (ex: bubbleSortNome())
    fim = clock();      // 3. Marca o tempo de fim

    // Calcula o tempo gasto (em segundos)
    tempoGasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    printf("\n--- Análise de Desempenho: %s ---\n", nomeAlgoritmo);
    // Pega o número de comparações que a função de sort contou na variável global
    printf("Número de comparações: %lld\n", comparacoes); 
    printf("Tempo de execução: %f segundos\n", tempoGasto);
    printf("-------------------------------------------\n");
}
