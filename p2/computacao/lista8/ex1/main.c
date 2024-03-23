#include <stdio.h>

typedef struct _Ponto {
    float x, y;
} Ponto;

int main(int argc, char *argv[]) {
    Ponto p;

    printf("Entre com as coodenadas do ponto p\n");
    scanf("%f %f", &p.x, &p.y);

    printf("dados lidos\n");
    printf("Ponto p: x = %f y = %f\n", p.x, p.y);
    return 0;
}
