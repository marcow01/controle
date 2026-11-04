#include <stdio.h>
#include <math.h> 

int tipoA(){

    float amplitude, estabilizador, tempo, ytempo;

    printf("1. Amplitude: "); 
    scanf("%f", &amplitude);

    printf("2. Valor de estabilizacao: "); 
    scanf("%f", &estabilizador);

    printf("3. Tempo t1: "); 
    scanf("%f", &tempo);

    printf("4. Valor de y para tempo t1: "); 
    scanf("%f", &ytempo);

    float Kdc = estabilizador/amplitude;
    double T = ((-1)*tempo)/log(1-(ytempo/estabilizador));

    printf("\nGanho Estatico (Kdc): %.4f\n", Kdc);
    printf("Constante de Tempo (T): %.4f s\n", T);
    printf("G(s) = %.2f / (%.2f * s + 1)\n", Kdc, T);

    FILE *arquivo = fopen("dadosA.csv", "w");

    if (arquivo != NULL) {
        fprintf(arquivo, "Tempo (s);y(t)\n");
        double tempo_final = 10.0;
        double passo = 0.1;
        for (double t = 0; t <= tempo_final + 1e-5; t += passo) {
            double yt = estabilizador * (1.0 - exp(-t / T));
            char bufT[32], bufY[32];
            snprintf(bufT, sizeof(bufT), "%.2f", t);
            snprintf(bufY, sizeof(bufY), "%.4f", yt);
            for (char *p = bufT; *p; p++) if (*p == '.') *p = ',';
            for (char *p = bufY; *p; p++) if (*p == '.') *p = ',';
            fprintf(arquivo, "%s;%s\n", bufT, bufY);
        }
        fclose(arquivo);
        printf("\n Arquivo 'dadosA.csv' gerado com sucesso! \n");
    }
    return 0;
}

int tipoB(){

    float amplitude, estabilizador, yp, tp;

    printf("1. Amplitude: "); 
    scanf("%f", &amplitude);

    printf("2. Valor de estabilizacao: "); 
    scanf("%f", &estabilizador);

    printf("3. Valor maximo do primeiro pico: "); 
    scanf("%f", &yp);

    printf("4. Tempo do primeiro pico: "); 
    scanf("%f", &tp);

    float Kdc = estabilizador/amplitude;
    float Mp = (yp - estabilizador)/estabilizador;
    float fatorAmortecimento = ((-1)*log(Mp))/sqrt(3.14159265 * 3.14159265 + log(Mp) * log(Mp));
    float frequenciaNatural = 3.14159265/(tp * sqrt(1 - (fatorAmortecimento * fatorAmortecimento)));

    printf("\nGanho Estatico (Kdc): %.4f\n", Kdc);
    printf("Fator de Amortecimento: %.4f\n", fatorAmortecimento);
    printf("Frequencia Natural: %.4f rad/s\n", frequenciaNatural);
    printf("G(s) = %.2f / (s^2 + %.2f * s + %.2f)\n", Kdc * frequenciaNatural * frequenciaNatural, 2 * fatorAmortecimento * frequenciaNatural, frequenciaNatural * frequenciaNatural);

    FILE *arquivo = fopen("dadosB.csv", "w");

    if (arquivo != NULL) {
        fprintf(arquivo, "Tempo (s);y(t)\n");
        double wd = frequenciaNatural * sqrt(1.0 - fatorAmortecimento * fatorAmortecimento);
        double phi = acos(fatorAmortecimento);
        double tempo_final = 10.0;
        double passo = 0.1;
        for (double t = 0; t <= tempo_final + 1e-5; t += passo) {
            double yt = estabilizador * (1.0 - (exp(-fatorAmortecimento * frequenciaNatural * t) / sqrt(1.0 - fatorAmortecimento * fatorAmortecimento)) * sin(wd * t + phi));
            char bufT[32], bufY[32];
            snprintf(bufT, sizeof(bufT), "%.2f", t);
            snprintf(bufY, sizeof(bufY), "%.4f", yt);
            for (char *p = bufT; *p; p++) if (*p == '.') *p = ',';
            for (char *p = bufY; *p; p++) if (*p == '.') *p = ',';
            fprintf(arquivo, "%s;%s\n", bufT, bufY);
        }
        fclose(arquivo);
        printf("\n Arquivo 'dadosB.csv' gerado com sucesso!\n");
    }
    return 0;
}

int main(){

    char tipo;
    printf("Escolha o tipo: (A) ou (B) \n");
    scanf(" %c", &tipo);

    if(tipo == 'A' || tipo == 'a'){
        tipoA();
    }
    else if(tipo == 'B' || tipo == 'b'){
        tipoB();
    }
    else{
        printf("Tipo invalido. \n");
    }
    return 0;
}