#ifndef __BOTAO_H__
#define __BOTAO_H__

#include "gl_canvas2d.h"

class Botao{
  float altura, largura, x, y;
  char label[100];
  char funcao;

public:
  Botao(float _x, float _y, float _larg, float _alt, char *_label, char _funcao)
  {
     altura  = _alt;
     largura = _larg;
     x = _x;
     y = _y;
     strcpy(label, _label);
     funcao = _funcao;
  }

  void Render(float rb, float gb, float bb,float rt, float gt,float bt,int preenchida)
  {
      color(rb,gb,bb);
      if(preenchida==1)
        rectFill(x, y, x + largura, y + altura);
      else
        rect(x,y,x+largura,y+altura);
      color(rt,gt,bt);
      text(x+5, y+altura/2, label); //escreve o label do botao mais ou menos ao centro.
  }
  char getFuncao()
  {
      return funcao;
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
  //seta o x do botao
  void setX(int _x)
  {
      x=_x-5;
  }
};

#endif
