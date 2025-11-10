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
        printf("cod %d, nome %s, pre %.2f, qnt %d\n", p[i].codigo, p[i].nome, p[i].preco, p[i].quantidade);
    }
}

void adicionarProduto(const char *nomeArquivo, int tam, Produto p[]){
    fopen(nomeArquivo, "a");

    printf("digite o codigo do produto: ");
}

void menu(int a, Produto p[]){
    int escolha;

    printf("\n\n=======MENU=======");
    printf("\n1. Adicionar produto");
    printf("\n2. Buscar produto por código");
    printf("\n3. Imprimir produtos");
    printf("\n4. Ordenar por preço e imprimir");
    printf("\n5. Sair");
    printf("\n==================\n");
    
    scanf("%d", &escolha);
    switch (escolha){
    case 1: break;
    case 2: break;
    case 3: imprimirProdutos(a, p); break;
    case 4: break;
    case 5: break;
    default: printf("digite um numero valido!"); break;
    }
}

int main() {
    Produto p[50];
    int tam = sizeof(p)/sizeof(p[0]);

    int a = lerTexto("produtos.txt", tam, p);

    menu(a, p);

    return 0;
}
