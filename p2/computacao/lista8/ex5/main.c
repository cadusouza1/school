#include <stdio.h>

typedef struct _Tempo {
    int hora, minuto, segundo;
} Tempo;

Tempo maior_tempo(Tempo t1, Tempo t2) {
    if (t1.hora > t2.hora) {
        return t1;
    } else if (t2.hora > t1.hora) {
        return t2;
    }

    if (t1.minuto > t2.minuto) {
        return t1;
    } else if (t2.minuto > t1.minuto) {
        return t2;
    }

    if (t1.segundo > t2.segundo) {
        return t1;
    } else if (t2.segundo > t1.segundo) {
        return t2;
    }

    return t1;
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

    Tempo maior = maior_tempo(t1, t2);

    printf("Tempo maior: %d:%d:%d\n", maior.hora, maior.minuto, maior.segundo);
    return 0;
}
