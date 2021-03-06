#include <stdio.h>
#include "ponto.h"
#include "retangulo.h"

void imprime_retangulo(Retangulo r){

    printf("Canto superior esquerdo: (%d,%d) \n", r.p_cse.x, r.p_cse.y);
    printf("Canto superior direito: (%d,%d) \n", r.p_cse.x+r.largura, r.p_cse.y);
    printf("Canto inferior esquerdo: (%d,%d) \n", r.p_cse.x, r.p_cse.y-r.altura);
    printf("Canto inferior direito: (%d,%d) \n", r.p_cse.x+r.largura, r.p_cse.y-r.altura);

}

void inicializa_retangulo(Retangulo *r)
{
    printf("Indique a altura do retangulo: ");
    scanf("%d", &r->altura);
    printf("Indique a largura do retangulo: ");
    scanf("%d", &r->largura);
    printf("Indique as coordenadas do canto superior esquerdo do retangulo: \n");
    initPonto(&r->p_cse);
}

int area_retangulo(Retangulo r)
{
    return r.altura*r.largura;
}

int ponto_retangulo(Retangulo r, ponto2D p)
{
    if(p.x > r.p_cse.x && p.x < r.p_cse.x+r.largura && p.y < r.p_cse.y && p.y > r.p_cse.y-r.altura)
        return 1;

    return 0;
}

void move_retangulo(Retangulo *r, int dx, int dy)
{
    movePonto(&r->p_cse,dx,dy);
}
