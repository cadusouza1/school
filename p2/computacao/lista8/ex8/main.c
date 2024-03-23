#include <stdio.h>
#include <stdlib.h>

#define NUM_TEMPOS 4

typedef struct _Tempo {
    int hora, minuto, segundo;
} Tempo;

int maior_tempo(Tempo *t1, Tempo *t2) {
    if (t1->hora > t2->hora) {
        return 1;
    } else if (t1->hora < t2->hora) {
        return -1;
    }

    if (t1->minuto > t2->minuto) {
        return 1;
    } else if (t1->minuto < t2->minuto) {
        return -1;
    }

    if (t1->segundo > t2->segundo) {
        return 1;
    } else if (t2->segundo > t1->segundo) {
        return -1;
    }

    return 0;
}

void sort_tempo(Tempo t[], int n) {
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            if (maior_tempo(&t[j], &t[j + 1]) == 1) {
                Tempo temp = t[j];
                t[j] = t[j + 1];
                t[j + 1] = temp;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    Tempo tempos[NUM_TEMPOS];

    for (int i = 0; i < NUM_TEMPOS; i++) {
        printf("Entre com a hora da tarefa %d: ", i);
        scanf("%d", &tempos[i].hora);

        printf("Entre com a minuto da tarefa %d: ", i);
        scanf("%d", &tempos[i].minuto);

        printf("Entre com a segundo da tarefa %d: ", i);
        scanf("%d", &tempos[i].segundo);
    }

    sort_tempo(tempos, NUM_TEMPOS);

    for (size_t i = 0; i < NUM_TEMPOS; i++) {
        printf("%d:%d:%d\n", tempos[i].hora, tempos[i].minuto,
               tempos[i].segundo);
    }

    return 0;
}
