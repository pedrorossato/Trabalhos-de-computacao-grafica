#ifndef TRIANGULO_H
#define TRIANGULO_H


class Triangulo
{
    int x,y,raio;
    public:
        Triangulo(int _x, int _y, int _raio)
        {
            x = _x;
            y = _y;
            raio = _raio;
        }
        void Render(int r, int g,int b)
        {
            color((float)r/255,(float)g/255,(float)b/255);
            circleFill(x,y,raio,3);
        }

    protected:

    private:
};

#endif // TRIANGULO_H
