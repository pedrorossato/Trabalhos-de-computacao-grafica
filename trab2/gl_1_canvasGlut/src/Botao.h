#ifndef __BOTAO_H__
#define __BOTAO_H__

#include "gl_canvas2d.h"

class Botao{
  float altura, largura, x, y;
  char label[100];
  char figura;

public:
  Botao(float _x, float _y, float _larg, float _alt, char *_label, char _figura)
  {
     altura  = _alt;
     largura = _larg;
     x = _x;
     y = _y;
     strcpy(label, _label);
     figura = _figura;
  }

  void Render(int rb, int gb, int bb,int rt, int gt,int bt,int preenchida)
  {
      color((float)rb/255,(float)gb/255,(float)bb/255);
      if(preenchida==1)
        rectFill(x, y, x + largura, y + altura);
      else
        rect(x,y,x+largura,y+altura);
      color((float)rt/255,(float)gt/255,(float)bt/255);
      text(x+5, y+altura/2, label); //escreve o label do botao mais ou menos ao centro.
  }
  char getFigura()
  {
      return figura;
  }
  char *getLabel()
  {
      return label;
  }
  //recebe as coordenadas do mouse para tratar clique ou detectar quando o mouse esta em cima do botao
  bool Colidiu(int mx, int my)
  {
      if( mx >= x && mx <= (x + largura) && my >= y && my <= (y + altura) )
      {
          return true;
      }
      return false;
  }

};

#endif
