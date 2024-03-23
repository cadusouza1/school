#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define COLUNA 10
#define FILEIRA 40

typedef enum _Filmes { STAR_TREK = 1, STAR_WARS, AVENGERS } Filmes;

void inicializa(char sala[COLUNA][FILEIRA]) {
    int i, j;
    for (i = 0; i < COLUNA; i++) {
        for (j = 0; j < FILEIRA; j++) {
            sala[i][j] = '0';
        }
    }
}

char *nome_filme(Filmes filme) {
    switch (filme) {
    case STAR_TREK:
        return "Star Trek";
    case STAR_WARS:
        return "Star Wars";
    case AVENGERS:
        return "Avengers";
    default:
        return NULL;
    }
}

Filmes seleciona_filme() {
    Filmes escolha_filme;

    printf("-------------------------------------");
    printf("\nBem Vindo ao cinema Mariano Pinheiro");
    printf("\n-------------------------------------");
    printf("\nQual filme voce deseja assistir:");
    printf("\n1 - Star Trek");
    printf("\n2 - Star Wars");
    printf("\n3 - Avengers");
    printf("\n0 - Encerrar operacao\n");

    while (scanf("%d", &escolha_filme) != 1 || escolha_filme > AVENGERS ||
           escolha_filme < 0) {
        printf("\n-------------------------------------");
        printf("\nEscolha invalida. Digite novamente o codigo do filme.");
        printf("\n1 - Star Trek");
        printf("\n2 - Star Wars");
        printf("\n3 - Avengers");
        printf("\n0 - Encerrar operacao\n");
        while (getchar() != '\n')
            ;
    }

    if (escolha_filme == 0) {
        printf("Operacao encerrada\n");
        exit(0);
    }

    printf("Filme escolhido -> %s\n", nome_filme(escolha_filme));
    return escolha_filme;
}

void carrega_sala(Filmes filme, char sala[COLUNA][FILEIRA]) {
    int i = 0;
    char *filename;
    FILE *f;

    switch (filme) {
    case STAR_TREK:
        filename = "star_trek.txt";
        break;
    case STAR_WARS:
        filename = "star_wars.txt";
        break;
    case AVENGERS:
        filename = "avengers.txt";
        break;
    default:
        break;
    }

    f = fopen(filename, "r");

    if (f == NULL) {
        printf("Nao foi possivel abrir o arquivo %s\n", filename);
        exit(1);
    }

    /* Checando se a sala ainda não foi inicializada */
    if (fgetc(f) == EOF) {
        inicializa(sala);
        return;
    }

    rewind(f);

    for (i = 0; i < COLUNA; i++) {
        fread(&sala[i], sizeof(char), FILEIRA, f);
        fgetc(f); /* Pular o caratere de nova linha */
    }
}

void salvar_sala(Filmes filme, char sala[COLUNA][FILEIRA]) {
    int i;
    char *filename;
    FILE *f;

    switch (filme) {
    case STAR_TREK:
        filename = "star_trek.txt";
        break;
    case STAR_WARS:
        filename = "star_wars.txt";
        break;
    case AVENGERS:
        filename = "avengers.txt";
        break;
    default:
        break;
    }

    f = fopen(filename, "w");

    if (f == NULL) {
        printf("Nao foi possivel abrir o arquivo %s\n", filename);
        exit(1);
    }

    for (i = 0; i < COLUNA; i++) {
        fwrite(&sala[i], sizeof(char), FILEIRA, f);
        fputc('\n', f);
    }
}

int compra_de_ingressos(Filmes filme) {
    char *nome = nome_filme(filme);
    int qtd_ingressos;
    printf("\nDigite a quantidade de ingressos desejadas para o filme %s ",
           nome);
    scanf("%d", &qtd_ingressos);

    while (qtd_ingressos > 400 || qtd_ingressos < 1) {
        if (qtd_ingressos < 1) {
            printf("Quantidade minima de ingressos:1.\nDigite novamente a "
                   "quantidade de ingressos desejada:");
            scanf("%d", &qtd_ingressos);
        } else {
            printf("Quantidade maxima de ingressos:400.\nDigite novamente a "
                   "Quantidade de ingressos desejada:");
            scanf("%d", &qtd_ingressos);
        }
    }

    printf("\nForam selecionados %d ingressos para o filme %s", qtd_ingressos,
           nome);
    printf(
        "\n------------------------------------------------------------------");

    return qtd_ingressos;
}

int desconto_meia_entrada(int ingressos_totais) {
    int qtd_meia_entrada;
    printf("\nDigite a quantidade de ingressos irao receber o desconto de "
           "meia-entrada:");
    scanf("%d", &qtd_meia_entrada);
    while (qtd_meia_entrada > ingressos_totais) {
        printf("Quantidade invalida de ingressos meia-entrada");
        printf("\nDigite novamente a quantidade de ingressos meia-entrada:");
        scanf("%d", &qtd_meia_entrada);
    }
    printf(
        "\n------------------------------------------------------------------");
    printf("\nForam selecionados %d ingressos meia-entrada", qtd_meia_entrada);
    printf(
        "\n------------------------------------------------------------------");
    return qtd_meia_entrada;
}

bool valida_carteira(int carteira) {
    int soma = 0;
    int temp = carteira / 10;
    int ultimoDigito = carteira % 10;

    while (temp > 0) {
        soma += temp % 10;
        temp /= 10;
    }

    return (soma % 10) == ultimoDigito;
}

int valida_meia_entrada(int qtd_meia_estudante) {
    int i, j, carteira_estudante, numCarteirasUtilizadas = 0;
    bool carteiraJaUtilizada;
    int *carteirasUtilizadas =
        malloc(qtd_meia_estudante * sizeof(qtd_meia_estudante));

    if (carteirasUtilizadas == NULL) {
        printf("Nao foi possivel alocar memoria para as carteiras de meia "
               "entrada\n");
        exit(1);
    }

    if (qtd_meia_estudante == 0)
        return -1;

    for (i = 0; i < qtd_meia_estudante; i++) {
        printf("\nDigite a carteira de estudante do %d ingresso (ou 0 para "
               "cancelar o desconto)\n",
               i + 1);
        scanf("%d", &carteira_estudante);

        if (carteira_estudante == 0) {
            printf("Desconto cancelado para o ingresso %d.\n", i + 1);
            continue;
        }

        if (carteira_estudante < 10000 || carteira_estudante > 99999 ||
            !valida_carteira(carteira_estudante)) {
            printf(
                "Carteira de estudante invalida. Digite uma nova carteira.\n");
            i--;
            continue;
        }

        carteiraJaUtilizada = false;

        for (j = 0; j < numCarteirasUtilizadas; j++) {
            if (carteira_estudante == carteirasUtilizadas[j]) {
                carteiraJaUtilizada = true;
                break;
            }
        }

        if (carteiraJaUtilizada) {
            printf("A carteira de estudante ja foi utilizada. Digite uma nova "
                   "carteira.\n");
            i--;
            continue;
        }

        carteirasUtilizadas[numCarteirasUtilizadas] = carteira_estudante;
        numCarteirasUtilizadas++;

        printf("Carteira de estudante valida\n");
    }

    return numCarteirasUtilizadas;
}

int qtd_itasil(int qtd_meia_entrada, int qtd_ingressos_totais) {
    int itasil;

    printf("\nDigite a quantidade de ingressos que vao receber o desconto "
           "Itasil:");
    scanf("%d", &itasil);

    if (itasil == 0)
        return 0;

    while (itasil < 0 || itasil + qtd_meia_entrada > qtd_ingressos_totais) {
        printf("\nQuantidade de meia-itasil invalida.");
        printf("\nDigite a quantidade de ingressos que vao receber o desconto "
               "Itasil:");
        scanf("%d", &itasil);
    }

    return itasil;
}

bool assento_fora_dos_limites(int fileira, int coluna) {
    return fileira < 0 || fileira >= FILEIRA || coluna < 0 || coluna >= COLUNA;
}

void exibe_mapa(char sala[COLUNA][FILEIRA]) {
    int i, j;
    printf("  ");
    for (i = 0; i < FILEIRA; i++) {
        printf("%d ", i + 1);
    }
    printf("\n");

    for (i = 0; i < COLUNA; i++) {
        printf("%c ", i + 64 + 1);
        for (j = 0; j < FILEIRA; j++) {
            if (j < 10) {
                printf("%c ", sala[i][j]);
            } else {
                printf(" %c ", sala[i][j]);
            }
        }

        printf("\n");
    }
}

bool assento_ocupado(int fileira, int coluna, char sala[COLUNA][FILEIRA]) {
    return sala[coluna][fileira] == 'X';
}

void reserva_assento(int n_ingressos_a_reservar, char sala[COLUNA][FILEIRA]) {
    int i, fileira;
    char coluna;
    for (i = 0; i < n_ingressos_a_reservar; i++) {
        do {
            printf("\nDigite um numero inteiro entre 1 e %d e uma letra no "
                   "formato 'NumeroLetra' para reservar a poltrona do ingresso "
                   "%d/%d (sem espaco)\n",
                   FILEIRA, i + 1, n_ingressos_a_reservar);
            scanf("%d %c", &fileira, &coluna);

            /* Converter o valor do usuário para o intervalo 0..(FILEIRA - 1) */
            fileira--;

            /* Converter o caractere entrado pelo usuário para maiúsculo para
             * aceitar tanto letras minúsculas quanto maiúsculas */
            coluna = toupper(coluna) - 'A';

            if (assento_fora_dos_limites(fileira, coluna)) {
                printf("Digite um valor entre 1 e %d para a fileira e um "
                       "caractere entre 'A' e '%c' para a coluna\n",
                       FILEIRA, 'A' + COLUNA - 1);
            }

            if (assento_ocupado(fileira, coluna, sala)) {
                printf("Assento ocupado. Tente novamente\n");
            }

        } while (assento_fora_dos_limites(fileira, coluna) ||
                 assento_ocupado(fileira, coluna, sala));

        sala[(int)coluna][fileira] = 'X';
    }
}

void Calcula_Exibe_Preco(int Ingressos, int Meia_Estudante, int Meia_Itasil) {
    float Valor_Total, Valor_Ingresso, Valor_Meia_Estudante, Valor_Meia_Itasil;
    Valor_Ingresso = 20 * (Ingressos - (Meia_Estudante + Meia_Itasil));
    Valor_Meia_Estudante = (20 - (20 * 50 / 100)) * Meia_Estudante;
    Valor_Meia_Itasil = (20 - (20 * 30 / 100)) * Meia_Itasil;
    Valor_Total = Valor_Ingresso + Valor_Meia_Estudante + Valor_Meia_Itasil;
    printf("\nRESUMO DO COMPRA:");
    printf("\n%d INGRESSOS MEIA ESTUDANTE", Meia_Estudante);
    printf("\n%d INGRESSOS MEIA ITASIL", Meia_Itasil);
    printf("\n%d INGRESSOS INTEIROS", Ingressos);
    printf(
        "\n------------------------------------------------------------------");
    printf("\nVALOR TOTAL DA COMPRA : %.2f REAIS", Valor_Total);
    printf(
        "\n------------------------------------------------------------------");
}

int main(int argc, char *argv[]) {
    seleciona_filme();
    return 0;
}
