#ifndef TRIANGULO_H
#define TRIANGULO_H
#include "Figura.h"

class Triangulo : public Figura
{
    float vx[3],vy[3];
    public:
        Triangulo(int _x, int _y,int _tamanho,int _r, int _g ,int _b, bool _preenchida) : Figura(_x,_y,_tamanho,_r,_g,_b,_preenchida)
        {

        }
        void render()
        {
            vx[0] = x-tamanho; vx[1] = x; vx[2] = x+tamanho;
            vy[0] = y-tamanho; vy[1] = y+tamanho; vy[2] = y-tamanho;
            color((float)r/255,(float)g/255,(float)b/255);
            if (preenchida)
            {
                polygonFill(vx,vy,3);
            }
            else
            {
                polygon(vx,vy,3);
            }
        }
        bool Colidiu(int x, int y)
        {
            return false;
        }
    protected:

    private:
};

#endif // TRIANGULO_H
