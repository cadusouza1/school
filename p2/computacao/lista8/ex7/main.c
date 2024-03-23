#include <stdio.h>

typedef struct _Tempo {
    int hora, minuto, segundo;
} Tempo;

int maior_tempo(Tempo t1, Tempo t2) {
    if (t1.hora > t2.hora) {
        return 1;
    } else if (t2.hora > t1.hora) {
        return -1;
    }

    if (t1.minuto > t2.minuto) {
        return 1;
    } else if (t2.minuto > t1.minuto) {
        return -1;
    }

    if (t1.segundo > t2.segundo) {
        return 1;
    } else if (t2.segundo > t1.segundo) {
        return -1;
    }

    return 0;
}

int main(int argc, char *argv[]) {

    Tempo t1, t2;

    printf("Entre com a hora do tempo t1: ");
    scanf("%d", &t1.hora);

    printf("Entre com a minuto do tempo t1: ");
    scanf("%d", &t1.minuto);

    printf("Entre com a segundo do tempo t1: ");
    scanf("%d", &t1.segundo);

    printf("Entre com a hora do tempo t2: ");
    scanf("%d", &t2.hora);

    printf("Entre com a minuto do tempo t2: ");
    scanf("%d", &t2.minuto);

    printf("Entre com a segundo do tempo t2: ");
    scanf("%d", &t2.segundo);

    int maior = maior_tempo(t1, t2);

    if (maior > 0) {
        printf("t1 > t2\n");
    } else if (maior == 0) {
        printf("t1 == t2\n");
    } else {
        printf("t1 < t2\n");
    }

    return 0;
}
