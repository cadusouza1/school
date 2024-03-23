#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define N_FILMES 3
#define VALOR_INGRESSO 20
#define COLUNA 10
#define FILEIRA 40

/* Simples enumeracao representando os filmes disponiveis no cimena. Os valores
 * da enumeracao comecam a partir do 1 */
typedef enum _Filmes {
    VELOZES_E_FURIOSOS_137 = 1,
    THE_FLASH,
    TRANSFORMERS
} Filmes;

/* Inicializa uma sala com o valor '0' em todos os lugares */
void inicializa(char sala[FILEIRA][COLUNA]) {
    int i, j;
    for (i = 0; i < FILEIRA; i++) {
        for (j = 0; j < COLUNA; j++) {
            sala[i][j] = '0';
        }
    }
}

/* Converte uma enumaracao Filme em uma string correspondente ao nome do filme
 * que o valor da enumeracao representa */
char *nome_filme(Filmes filme) {
    switch (filme) {
    case VELOZES_E_FURIOSOS_137:
        return "Velozes e Furiosos 137";
    case THE_FLASH:
        return "The Flash";
    case TRANSFORMERS:
        return "Transformers";
    default:
        return NULL;
    }
}

Filmes seleciona_filme() {
    int escolha_filme;

    printf("-------------------------------------");
    printf("\nBem Vindo ao cinema Mariano Pinheiro");
    printf("\n-------------------------------------");
    printf("\nQual filme voce deseja assistir:");
    printf("\n1 - Velozes e Furiosos 137");
    printf("\n2 - The Flash");
    printf("\n3 - Transformers");
    printf("\n0 - Encerrar operacao\n");

    while (scanf("%d", &escolha_filme) != 1 || escolha_filme > TRANSFORMERS ||
           escolha_filme < 0) {
        printf("\n-------------------------------------");
        printf("\nEscolha invalida. Digite novamente o codigo do filme.");
        printf("\n1 - Velozes e Furiosos 137");
        printf("\n2 - The Flash");
        printf("\n3 - Transformers");
        printf("\n0 - Encerrar operacao\n");
        while (getchar() != '\n')
            ;
    }

    if (escolha_filme == 0) {
        printf("Operacao encerrada\n");
        exit(0);
    }

    printf("Filme escolhido -> %s\n", nome_filme(escolha_filme));
    return (Filmes)escolha_filme;
}

int confirma_filme() {
    int escolha;
    printf("\nDigite 1 para continuar ou 0 para cancelar operacao:");

    while (1) {
        if (scanf("%d", &escolha) == 1) {
            if (escolha == 0) {
                printf("\n-------------------------------------");
                printf("\nOperacao cancelada.");
                printf("\n-------------------------------------");
                return 0;
            } else if (escolha == 1) {
                return 1;
            } else {
                printf("\nEntrada invalida. Digite 1 para continuar ou 0 para "
                       "cancelar operacao:");
            }
        } else {
            printf("\nEntrada invalida. digite novamente:");
            while (getchar() != '\n')
                ; /* Limpa o buffer de entrada */
        }
    }
}

int compra_de_ingressos(Filmes filme, int qtd_ingressos_restantes_filme) {
    char *nome = nome_filme(filme);
    int qtd_ingressos;
    printf("\nDigite a quantidade de ingressos desejadas para o filme %s ",
           nome);
    scanf("%d", &qtd_ingressos);

    while (qtd_ingressos > qtd_ingressos_restantes_filme || qtd_ingressos < 1) {
        if (qtd_ingressos < 1) {
            printf("Quantidade minima de ingressos:1.\nDigite novamente a "
                   "quantidade de ingressos desejada:");
            scanf("%d", &qtd_ingressos);
        } else {
            printf("Quantidade maxima de ingressos: %d.\nDigite novamente a "
                   "Quantidade de ingressos desejada:",
                   qtd_ingressos_restantes_filme);
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

int valida_meia_entrada(int qtd_meia_estudante, int *clientes_meia_entrada) {
    int i, j, carteira_estudante, numCarteirasUtilizadas = 0;
    bool carteiraJaUtilizada;

    if (qtd_meia_estudante == 0)
        return 0;

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

        for (j = 0; j < qtd_meia_estudante; j++) {
            if (carteira_estudante == clientes_meia_entrada[j]) {
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

        clientes_meia_entrada[numCarteirasUtilizadas] = carteira_estudante;
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

    printf(
        "\n------------------------------------------------------------------");
    printf("\nForam selecionados %d ingressos para desconto Itasil", itasil);
    printf(
        "\n------------------------------------------------------------------");

    return itasil;
}

int busca_codigo_itasil(int clientes_itasil[], int tamanho_vetor_itasil,
                        int codigo_cliente_itasil) {
    int i;
    for (i = 0; i < tamanho_vetor_itasil; i++) {
        if (clientes_itasil[i] == codigo_cliente_itasil) {
            return 1;
        }
    }

    return -1;
}

int valida_cliente_itasil(int qtd_cliente_itasil, int clientes_itasil[]) {
    int i, codigo_cliente_itasil, numero_itasil_valida = 0;
    for (i = 0; i < qtd_cliente_itasil; i++) {
        printf("\nDigite o codigo Itasil do %d ingresso ou zero para cancelar "
               "o desconto:",
               i + 1);
        scanf("%d", &codigo_cliente_itasil);

        if (codigo_cliente_itasil == 0) {
            printf("\nO desconto do %d ingresso foi cancelado.\n", i + 1);
            continue;
        }

        if (codigo_cliente_itasil < 0 || codigo_cliente_itasil % 341 != 0 ||
            codigo_cliente_itasil % 1 != 0) {
            printf("Codigo invalido. Digite novamente o codigo Itasil:");
            i--;
            continue;
        }

        if (busca_codigo_itasil(clientes_itasil, qtd_cliente_itasil,
                                codigo_cliente_itasil) == 1) {
            printf("\nEsse codigo ja foi utilizado.");
            i--;
            continue;
        }

        clientes_itasil[numero_itasil_valida] = codigo_cliente_itasil;
        numero_itasil_valida++;
    }

    return numero_itasil_valida;
}

/* Checa se o assento desejado na posicao fileira coluna esta fora dos limites
 * do cinema. Caso o assento esteja fora dos limites, a funcao retornara 1, caso
 * contrario retornara 0 */
int assento_fora_dos_limites(int fileira, int coluna) {
    return fileira < 0 || fileira >= FILEIRA || coluna < 0 || coluna >= COLUNA;
}

/* Exibe o mapa da sala junto com as informacoes sobre as posicoes e estado das
 * poltronas do cinema na saida padrao */
void exibe_mapa(char sala[FILEIRA][COLUNA]) {
    int i, j;
    printf("  ");
    for (i = 0; i < COLUNA; i++) {
        printf(" %c", i + 'A');
    }
    printf("\n");

    for (i = 0; i < FILEIRA; i++) {
        printf("%d ", i + 1);

        if (i < 9) {
            printf(" ");
        }

        for (j = 0; j < COLUNA; j++) {
            printf("%c ", sala[i][j]);
        }
        printf("%d\n", i + 1);
    }

    printf("\n");
}

/* Checa se o assento na posicao sala[coluna][fileira] esta ocupado.
 * A funcao retorna 1 caso o assento esteja ocupado e 0 caso contrario */
int assento_ocupado(int fileira, int coluna, char sala[FILEIRA][COLUNA]) {
    return sala[fileira][coluna] == 'X';
}

/* Coleta, checa e reserva os assentos desejados pelo usuario */
void reserva_assento(int n_ingressos_a_reservar, char sala[FILEIRA][COLUNA]) {
    int i, fileira;
    char coluna;
    for (i = 0; i < n_ingressos_a_reservar; i++) {
        do {
            printf(
                "\nDigite um numero inteiro entre 1 e %d e uma letra no "
                "formato 'Letra Numero' para reservar a poltrona do ingresso "
                "%d/%d (sem espaco)\n",
                FILEIRA, i + 1, n_ingressos_a_reservar);
            scanf("%c %d", &coluna, &fileira);

            /* Converter o valor do usuário para o intervalo 0..(FILEIRA - 1) */
            fileira--;

            /* Converter o caractere entrado pelo usuário para maiúsculo para
             * aceitar tanto letras minúsculas quanto maiúsculas */
            coluna = toupper(coluna) - 'A';
            printf("%d %d\n", coluna, fileira);

            if (assento_fora_dos_limites(fileira, (int)coluna)) {
                printf("Valor fora dos limites. Tente novamente.\n");
            }

            if (assento_ocupado(fileira, (int)coluna, sala)) {
                printf("Assento ocupado. Tente novamente.\n");
            }

        } while (assento_fora_dos_limites(fileira, coluna) ||
                 assento_ocupado(fileira, coluna, sala));

        sala[fileira][(int)coluna] = 'X';
    }
}

void calcula_exibe_preco(int ingressos_inteira, int meia_estudante,
                         int meia_itasil) {
    float valor_total, valor_ingresso, valor_meia_estudante, valor_meia_itasil;
    valor_ingresso = VALOR_INGRESSO * ingressos_inteira;
    valor_meia_estudante = VALOR_INGRESSO * meia_estudante * 0.5;
    valor_meia_itasil = VALOR_INGRESSO * meia_itasil * 0.7;
    valor_total = valor_ingresso + valor_meia_estudante + valor_meia_itasil;

    printf("\nResumo do compra:");
    printf("\n%d ingressos meia estudante", meia_estudante);
    printf("\n%d ingressos meia itasil", meia_itasil);
    printf("\n%d ingressos inteiros", ingressos_inteira);
    printf(
        "\n------------------------------------------------------------------");
    printf("\nValor total da compra : %.2f REAIS", valor_total);
    printf(
        "\n------------------------------------------------------------------");
    printf("\nObrigado pela preferencia. Volte sempre");
    printf(
        "\n------------------------------------------------------------------");
}

/* Le um arquivo contendo os estados dos assentos de uma sala e o armazena na
 * variavel sala. O arquivo a ser lido é definido pelo valor da enumeracao
 * passada */
void carrega_sala(Filmes filme, char sala[FILEIRA][COLUNA]) {
    int i = 0;
    char *filename;
    FILE *f;

    switch (filme) {
    case VELOZES_E_FURIOSOS_137:
        filename = "velozes_e_furiosos_137.txt";
        break;
    case THE_FLASH:
        filename = "the_flash.txt";
        break;
    case TRANSFORMERS:
        filename = "transformers.txt";
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

    for (i = 0; i < FILEIRA; i++) {
        fread(&sala[i], sizeof(char), COLUNA, f);
        fgetc(f); /* Pular o caratere de nova linha */
    }

    fclose(f);
}

/* Escreve o estado de uma sala dentro do arquivo que representa os estados dos
 * assentos do fime que representa */
void salvar_sala(Filmes filme, char sala[FILEIRA][COLUNA]) {
    int i;
    char *filename;
    FILE *f;

    switch (filme) {
    case VELOZES_E_FURIOSOS_137:
        filename = "velozes_e_furiosos_137.txt";
        break;
    case THE_FLASH:
        filename = "the_flash.txt";
        break;
    case TRANSFORMERS:
        filename = "transformers.txt";
        break;
    default:
        break;
    }

    f = fopen(filename, "w");

    if (f == NULL) {
        printf("Nao foi possivel abrir o arquivo %s\n", filename);
        exit(1);
    }

    rewind(f);

    for (i = 0; i < FILEIRA; i++) {
        fwrite(&sala[i], sizeof(char), COLUNA, f);
        fputc('\n', f);
    }

    fclose(f);
}
