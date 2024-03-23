#include <math.h>
#include <stdio.h>

typedef struct _Ponto {
    float x, y;
} Ponto;

float distance(Ponto p1, Ponto p2) {
    return sqrtf(powf(p1.x - p2.x, 2) + powf(p1.y - p2.y, 2));
}

int main(int argc, char *argv[]) {
    Ponto p1, p2;

    printf("Entre com as coordenadas de p1: ");
    scanf("%f %f", &p1.x, &p1.y);

    printf("Entre com as coordenadas de p2: ");
    scanf("%f %f", &p2.x, &p2.y);

    printf("Distancia entre p1 e p2: %f\n", distance(p1, p2));
    return 0;
}
