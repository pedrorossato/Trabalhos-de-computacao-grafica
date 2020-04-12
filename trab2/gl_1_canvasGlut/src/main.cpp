/*********************************************************************
// Canvas para desenho, criada sobre a API OpenGL. Nao eh necessario conhecimentos de OpenGL para usar.
//  Autor: Cesar Tadeu Pozzer
//         03/2020
//
//  Pode ser utilizada para fazer desenhos, animacoes, e jogos simples.
//  Tem tratamento de mouse e teclado
//  Estude o OpenGL antes de tentar compreender o arquivo gl_canvas.cpp
//
// *********************************************************************/

#include "main.h"

//funcao chamada continuamente. Deve-se controlar o que desenhar por meio de variaveis globais
//Todos os comandos para desenho na canvas devem ser chamados dentro da render().
//Deve-se manter essa função com poucas linhas de codigo.
void render()
{
   desenhaGUI(screenWidth,screenHeight);
   renderizaBotoes();
   renderizaLabels();
   for(list<Figura*>::iterator f = figuras.begin();f!=figuras.end();++f)
   {
       (*f)->render();
   }
}

//funcao para tratamento de mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int wheel, int direction, int x, int y)
{
   mouseX = x; //guarda as coordenadas do mouse para exibir dentro da render()
   mouseY = y;

   printf("\nmouse %d %d %d %d %d %d", button, state, wheel, direction,  x, y);

   if( button==0 && state == 0 ) //clicou com botao esquerdo
   {
       for(list<Botao>::iterator i = botoesFiguras.begin();i!=botoesFiguras.end();++i)
       {
           if( i->Colidiu(x, y) )
           {
               proximaFigura = i->getFigura();
           }

       }
       for(list<Botao>::iterator i = botoesTamanho.begin();i!=botoesTamanho.end();++i)
       {
           if(i->Colidiu(x,y))
           {
               switch (i->getFigura())
               {
                    case '+':
                        figuraSelecionada->setTamanho(figuraSelecionada->getTamanho()+5);
                        tamanho+=5;
                        break;
                    case '-':
                        figuraSelecionada->setTamanho(figuraSelecionada->getTamanho()-5);
                        tamanho-=5;
                        break;
               }
           }
       }
       for(list<Botao>::iterator i = botoesRotacao.begin();i!=botoesRotacao.end();++i)
       {
           if(i->Colidiu(x,y))
           {
               switch(i->getFigura())
               {
                    case '>':
                        figuraSelecionada->rotaciona();
                        break;
                    case '<':
                        figuraSelecionada->rotaciona();
                        break;
               }
           }
       }
       if(mouseX<880)
       {

            for(list<Figura*>::iterator i = figuras.begin();i!=figuras.end();++i)
            {
                if((*i)->Colidiu(x,y))
                {
                    figuraSelecionada = (*i);
                }
            }

            switch(proximaFigura)
            {
                case 'c':
                    figuras.push_back(new Circulo(mouseX,mouseY,tamanho,0,0,0,true));
                    proximaFigura = NULL;
                    break;
                case 't':
                    figuras.push_back(new Triangulo(mouseX,mouseY,tamanho,0,0,0,true));
                    proximaFigura = NULL;
                    break;
                case 'q':
                    figuras.push_back(new Quadrado(mouseX,mouseY,tamanho,0,0,0,true));
                    proximaFigura = NULL;
                    break;
            }
        }
    }
    else if(button==2 && state==0) //clicou com botao direito
    {
       for(list<Figura*>::iterator i = figuras.begin();i!=figuras.end();++i)
       {
           if((*i)->Colidiu(x,y))
           {
                i = figuras.erase(i);
           }
       }
    }
    else if (wheel==0)
    {
       switch(direction)
       {
        case 1:
            for(list<Figura*>::iterator i = figuras.begin();i!=figuras.end();++i)
            {
                if((*i)->Colidiu(x,y))
                {
                    (*i)->setTamanho((*i)->getTamanho()+5);
                    tamanho+=5;
                }
            }
            break;
        case -1:
            for(list<Figura*>::iterator i = figuras.begin();i!=figuras.end();++i)
            {
                if((*i)->Colidiu(x,y))
                {
                    if((*i)->getTamanho()>5)
                    {
                        (*i)->setTamanho((*i)->getTamanho()-5);
                        tamanho-=5;
                    }
                }
            }
            break;
       }
    }
}


int main(void)
{
   initCanvas(&screenWidth, &screenHeight, "Editor de Figuras Vetoriais - Pedro Rossato");
   iniciaBotoes();
   runCanvas();
}
