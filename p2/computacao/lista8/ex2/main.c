#include <stdio.h>

typedef struct _Ponto {
    float x, y;
} Ponto;

typedef struct _Cincunferencia {
    float raio;
    Ponto centro;
} Cincunferencia;

int main(int argc, char *argv[]) {
    Cincunferencia c1;

    printf("Entre com o raio do curculo c1\n");
    scanf("%f", &c1.raio);

    printf("Entre com as coordenadas do centro do circulo c1\n");
    scanf("%f %f", &c1.centro.x, &c1.centro.y);

    printf("Dados lidos\n");
    printf("Circulo c1: raio = %f, x = %f, y = %f\n", c1.raio, c1.centro.x,
           c1.centro.y);
    return 0;
}
