#include <stdio.h>
#include <string.h>
//Projeto: Programação Estruturada | C

// ---------------------------------------------------------
// Estrutura que representa um produto
// ---------------------------------------------------------
typedef struct Produto {
    int codigo;
    char nome[50];
    float preco;
    int quantidade;
} Produto;


// ---------------------------------------------------------
// Função: lerTexto
// Lê produtos do arquivo e armazena no vetor p[].
// Retorna a quantidade de produtos lidos.
// ---------------------------------------------------------
int lerTexto(const char *nomeArquivo, int tam, Produto p[]) {
    FILE *file = fopen(nomeArquivo, "r");
    if (file == NULL) {
        puts("Erro ao abrir arquivo");
        return 0;
    }

    int a = 0;
    while (fscanf(file, "%d %49s %f %d",
                  &p[a].codigo, p[a].nome, &p[a].preco, &p[a].quantidade) == 4) 
    {
        a++;
        if (a >= tam) break;
    }

    fclose(file);
    return a;
}


// ---------------------------------------------------------
// Função: imprimirProdutos
// Imprime todos os produtos carregados no vetor.
// ---------------------------------------------------------
void imprimirProdutos(int a, Produto p[]) {

    printf("\n===================== LISTA DE PRODUTOS =====================\n");
    printf("| %-6s | %-15s | %-10s | %-10s |\n", "COD", "NOME", "PRECO", "QNT");
    printf("--------------------------------------------------------------\n");

    for (int i = 0; i < a; i++) {
        printf("| %-6d | %-15s | %-10.2f | %-10d |\n",
               p[i].codigo, p[i].nome, p[i].preco, p[i].quantidade);
    }

    printf("==============================================================\n");
}


// ---------------------------------------------------------
// Função: adicionarProduto
// Grava um novo produto no final do arquivo.
// ---------------------------------------------------------
void adicionarProduto(const char *nomeArquivo) {
    int cod, qnt;
    float preco;
    char nome[50];

    FILE *f = fopen(nomeArquivo, "a");
    if (f == NULL) {
        printf("Erro ao salvar arquivo!\n");
        return;
    }

    printf("Digite o CODIGO do produto: ");
    scanf("%d", &cod);

    printf("Digite o NOME do produto: ");
    scanf("%49s", nome);

    printf("Digite o PRECO do produto: ");
    scanf("%f", &preco);

    printf("Digite a QUANTIDADE do produto: ");
    scanf("%d", &qnt);

    fprintf(f, "\n%d %s %.2f %d", cod, nome, preco, qnt);
    fclose(f);
}


// ---------------------------------------------------------
// Função: buscar_por_codigo
// Pesquisa um produto no vetor pelo código.
// ---------------------------------------------------------
void buscar_por_codigo(int a, Produto p[]) {
    int codigo;
    int encontrado = 0;

    printf("Digite o codigo do produto que deseja buscar: ");
    scanf("%d", &codigo);

    for (int i = 0; i < a; i++) {
        if (p[i].codigo == codigo) {
            printf("\n===== Produto encontrado =====\n");
            printf("Codigo: %d\n", p[i].codigo);
            printf("Nome: %s\n", p[i].nome);
            printf("Preco: %.2f\n", p[i].preco);
            printf("Quantidade: %d\n", p[i].quantidade);
            printf("==================================\n");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\nProduto com codigo %d nao encontrado.\n", codigo);
    }
}


// ---------------------------------------------------------
// Função: ordenarImprimir
// Ordena os produtos pelo preço (crescente) usando inserção
// e imprime o resultado.
// ---------------------------------------------------------
void ordenarImprimir(int a, Produto p[]) {
    Produto temp;

    for (int i = 1; i < a; i++) {
        temp = p[i];
        int j = i - 1;

        while (j >= 0 && p[j].preco > temp.preco) {
            p[j + 1] = p[j];
            j--;
        }
        p[j + 1] = temp;
    }

    printf("\n===== Produtos ordenados por preco =====\n");
    imprimirProdutos(a, p);
}


// ---------------------------------------------------------
// Função: menu
// Interface principal do sistema.
// ---------------------------------------------------------
void menu(int a, Produto p[]) {
    int escolha;

    do {
        printf("\n\n======= MENU =======");
        printf("\n1. Adicionar produto");
        printf("\n2. Buscar produto por codigo");
        printf("\n3. Imprimir produtos");
        printf("\n4. Ordenar por preco e imprimir");
        printf("\n5. Sair");
        printf("\n====================\n");

        printf("Escolha: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                adicionarProduto("produtos.txt");

                // recarrega o vetor após adicionar
                a = lerTexto("produtos.txt", 50, p);
                break;

            case 2:
                buscar_por_codigo(a, p);
                break;

            case 3:
                imprimirProdutos(a, p);
                break;

            case 4:
                ordenarImprimir(a, p);
                break;

            case 5:
                printf("Encerrando sistema...\n");
                break;

            default:
                printf("Digite um numero valido!\n");
                break;
        }

    } while (escolha != 5);
}


// ---------------------------------------------------------
// Função principal
// ---------------------------------------------------------
int main() {
    Produto p[50];
    int tam = sizeof(p) / sizeof(p[0]);

    // Carrega produtos do arquivo no início do programa
    int a = lerTexto("produtos.txt", tam, p);

    // Abre menu
    menu(a, p);

    return 0;
}
