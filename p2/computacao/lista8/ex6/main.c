#include <stdio.h>

typedef struct _Tempo {
    int hora, minuto, segundo;
} Tempo;

Tempo soma_tempo(Tempo t1, Tempo t2) {
    int soma_segundo = 0, soma_minuto = 0, soma_hora = 0;
    Tempo soma;

    soma_segundo = t1.segundo + t2.segundo;
    soma_minuto = t1.minuto + t2.minuto + soma_segundo / 60;
    soma_hora = t1.hora + t2.hora + soma_minuto / 60;

    soma.segundo = soma_segundo % 60;
    soma.minuto = soma_minuto % 60;
    soma.hora = soma_hora;

    return soma;
}

int main(int argc, char *argv[]) {
    Tempo t1, t2, soma;

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

    soma = soma_tempo(t1, t2);

    printf("Soma: %d:%d:%d\n", soma.hora, soma.minuto, soma.segundo);
    return 0;
}
