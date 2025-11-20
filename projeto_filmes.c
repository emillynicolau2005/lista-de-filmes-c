#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* ============================
   ESTRUTURA DO REGISTRO
   ============================ */
typedef struct {
    char titulo[50];
    char genero[30];
    int ano;
} filme;

/* Protótipos */
void limpaBuffer(void);
void lerString(char *s, int tam);
int tamanho(FILE *arq);
void cadastrar(FILE *arq);
void consultar(FILE *arq);

/* ============================
   limpaBuffer
   ============================ */
void limpaBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* ============================
   Leitura segura de string
   ============================ */
void lerString(char *s, int tam) {
    if (fgets(s, tam, stdin) != NULL) {
        s[strcspn(s, "\n")] = '\0'; // Remove o '\n' do final
    }
}

/* ============================
   tamanho
   Retorna quantidade de registros
   ============================ */
int tamanho(FILE *arq) {
    long pos = ftell(arq);
    fseek(arq, 0, SEEK_END);
    long fim = ftell(arq);
    fseek(arq, pos, SEEK_SET);
    return (int)(fim / sizeof(filme));
}

/* ============================
   cadastrar
   ============================ */
void cadastrar(FILE *arq) {
    filme f;
    char confirma[3];

    printf("\n=== CADASTRAR FILME ===\n");
    printf("Registro número: %d\n", tamanho(arq) + 1);

    printf("Título: ");
    lerString(f.titulo, sizeof(f.titulo));

    printf("Gênero: ");
    lerString(f.genero, sizeof(f.genero));

    printf("Ano: ");
    while (scanf("%d", &f.ano) != 1) {
        printf("Ano inválido. Digite novamente: ");
        limpaBuffer();
    }
    limpaBuffer();

    printf("Confirmar cadastro (s/n)? ");
    lerString(confirma, sizeof(confirma));

    if (toupper(confirma[0]) == 'S') {
        fseek(arq, 0, SEEK_END);
        if (fwrite(&f, sizeof(filme), 1, arq) != 1) {
            printf("Erro ao salvar o filme.\n");
        } else {
            fflush(arq);
            printf("Filme cadastrado com sucesso!\n");
        }
    } else {
        printf("Cadastro cancelado.\n");
    }
}

/* ============================
   consultar
   ============================ */
void consultar(FILE *arq) {
    int codigo;
    filme f;

    if (tamanho(arq) == 0) {
        printf("\nNenhum filme cadastrado!\n");
        return;
    }

    printf("\nCódigo do filme: ");
    if (scanf("%d", &codigo) != 1) {
        printf("Entrada inválida.\n");
        limpaBuffer();
        return;
    }
    limpaBuffer();

    int total = tamanho(arq);

    if (codigo <= 0 || codigo > total) {
        printf("Código inválido! Total de filmes: %d\n", total);
        return;
    }

    long pos = (long)(codigo - 1) * sizeof(filme);
    if (fseek(arq, pos, SEEK_SET) != 0) {
        printf("Erro ao posicionar no arquivo.\n");
        return;
    }

    if (fread(&f, sizeof(filme), 1, arq) != 1) {
        printf("Erro ao ler o registro.\n");
        return;
    }

    printf("\n=== FILME (%d) ===\n", codigo);
    printf("Título:  %s\n", f.titulo);
    printf("Gênero:  %s\n", f.genero);
    printf("Ano:     %d\n", f.ano);
}

/* ============================
   main
   ============================ */
int main(void) {
    FILE *arq = fopen("filmes.dat", "r+b");
    if (!arq) {
        arq = fopen("filmes.dat", "w+b");
        if (!arq) {
            printf("Erro ao abrir ou criar arquivo.\n");
            return 1;
        }
    }

    int op;
    do {
        printf("\n========= LISTA DE FILMES =========\n");
        printf("1. Cadastrar filme\n");
        printf("2. Consultar filme\n");
        printf("3. Sair\n");
        printf("-----------------------------------\n");
        printf("Total de registros: %d\n", tamanho(arq));
        printf("Opção: ");

        if (scanf("%d", &op) != 1) {
            printf("Entrada inválida.\n");
            limpaBuffer();
            continue;
        }
        limpaBuffer();

        switch (op) {
            case 1: cadastrar(arq); break;
            case 2: consultar(arq); break;
            case 3: printf("Finalizando...\n"); break;
            default: printf("Opção inválida!\n");
        }

    } while (op != 3);

    fclose(arq);
    return 0;
}
