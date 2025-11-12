#include <stdio.h>
#include <string.h>

typedef struct Produto {
    int codigo;
    char nome[50];
    float preco;
    int quantidade;
} Produto;

int lerTexto(const char *nomeArquivo, int tam, Produto p[]) {
    FILE *file = fopen(nomeArquivo, "r");
    if (file == NULL) {
        puts("Erro ao abrir arquivo");
        return 0;
    }

    int a = 0;
    while (fscanf(file, "%d %49s %f %d", &p[a].codigo, p[a].nome, &p[a].preco, &p[a].quantidade) == 4) {
        a++;
        if (a >= tam) break;
    }

    fclose(file);
    return a;
}

void imprimirProdutos(int a, Produto p[]){
    for (int i = 0; i < a; i++) {
        printf("codigo do produto: %d |, nome do produto: %s |, preco do produto: %.2f |, quantidade do produto:  %d |\n", p[i].codigo, p[i].nome, p[i].preco, p[i].quantidade);
    }
}

void adicionarProduto(const char *nomeArquivo){
    int cod, qnt;
    float preco;
    char nome[50];
    FILE *f = fopen(nomeArquivo, "a");
    if (f == NULL) {
        printf("Erro ao salvar arquivo!\n");
        return;
    }

    printf("digite o CODIGO do produto: ");
    scanf("%d", &cod);
    printf("digite o NOME do produto: ");
    scanf("%49s", nome);
    printf("digite o PRECO do produto: ");
    scanf("%f", &preco);
    printf("digite a QUANTIDADE do produto: ");
    scanf("%d", &qnt);

    fprintf(f, "\n");
    fprintf(f, "%d %s %.2f %d", cod, nome, preco, qnt);
    fclose(f);
}
void buscar_por_codigo(int a, Produto p[]){
    int codigo;
    int encontrado = 0;

    printf("Digite o código do produto que deseja buscar: ");
    scanf("%d", &codigo);

    for (int i = 0; i < a; i++) {
        if (p[i].codigo == codigo) {
            printf("\n===== Produto encontrado =====\n");
            printf("Código: %d\n", p[i].codigo);
            printf("Nome: %s\n", p[i].nome);
            printf("Preço: %.2f\n", p[i].preco);
            printf("Quantidade: %d\n", p[i].quantidade);
            printf("\n==================================\n");
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("\nProduto com código %d não encontrado.\n", codigo);
    }
}

void menu(int a, Produto p[]){
    int escolha;

    do{
        printf("\n\n=======MENU=======");
        printf("\n1. Adicionar produto");
        printf("\n2. Buscar produto por código");
        printf("\n3. Imprimir produtos");
        printf("\n4. Ordenar por preço e imprimir");
        printf("\n5. Sair");
        printf("\n==================\n");
        
        scanf("%d", &escolha);
        switch (escolha){
        case 1: adicionarProduto("produtos.txt");
                a = lerTexto("produtos.txt", 50, p); break;
        case 2: buscar_por_codigo(a, p); break;
        case 3: imprimirProdutos(a, p); break;
        case 4: break;
        case 5: break;
        default: printf("digite um numero valido!"); break;
        }
    }while(escolha != 5);
}

int main() {
    Produto p[50];
    int tam = sizeof(p)/sizeof(p[0]);

    int a = lerTexto("produtos.txt", tam, p);

    menu(a, p);

    return 0;
}
