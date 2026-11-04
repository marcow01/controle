#include <stdio.h>
#include <math.h> 

int main(){

    float amplitude;
    float estabilizador;
    float tempo;
    float ytempo;

    printf("digite: \n");
    printf("Amplitude\n");
    scanf("%f", &amplitude);

    printf("2. Valor de estabilizacao \n");
    scanf("%f", &estabilizador);

    printf("3. Tempo t1 \n");
    scanf("%f", &tempo);

    printf("4. Valor de y para tempo t1 \n");
    scanf("%f", &ytempo);

    // printf("Amplitude: %.2f \n", amplitude);
    // printf("Estabiliza em: %.2f \n", estabilizador);
    // printf("Tempo t1: %.2f \n", tempo);
    // printf("Valor de y no tempo t1: %.2f \n", ytempo);

    //ganho estático: Kdc = estabilizador/amplitude

    float Kdc = estabilizador/amplitude;

    //constante T: -tempo/ln(1-ytempo/estabilizador)

    double T = ((-1)*tempo)/log(1-(ytempo/estabilizador));

    //resultados: 

    printf("Ganho Estatico (Kdc): %.4f\n", Kdc);
    printf("Constante de Tempo (T): %.4f s\n", T);
    printf("Funcao de transferencia G(s) = %.2f / %.2f * s + 1 \n", Kdc, T);

    return 0;
}