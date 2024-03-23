#include <math.h>
#include <stdio.h>

typedef struct _Ponto {
    float x, y;
} Ponto;

typedef struct _Cincunferencia {
    float raio;
    Ponto centro;
} Cincunferencia;

float distance(Ponto p1, Ponto p2) {
    return sqrtf(powf(p1.x - p2.x, 2) + powf(p1.y - p2.y, 2));
}

int is_in_cincunfere(Cincunferencia c, Ponto p) {
    float dist = distance(p, c.centro);

    if (dist <= c.raio) {
        return 1;
    }

    return 0;
}

int main(int argc, char *argv[]) {
    Ponto p;
    Cincunferencia c;

    printf("Entre com as coordenadas de p: ");
    scanf("%f %f", &p.x, &p.y);

    printf("Entre com o raio do curculo c: ");
    scanf("%f", &c.raio);

    printf("Entre com as coordenadas do centro do circulo c: ");
    scanf("%f %f", &c.centro.x, &c.centro.y);

    if (is_in_cincunfere(c, p)) {
        printf("O ponto esta contido na cincunferencia\n");
    } else {
        printf("O ponto nao esta contido na cincunferencia\n");
    }

    return 0;
}
