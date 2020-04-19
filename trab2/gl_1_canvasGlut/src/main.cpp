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
#define pi 3.14159265
//funcao chamada continuamente. Deve-se controlar o que desenhar por meio de variaveis globais
//Todos os comandos para desenho na canvas devem ser chamados dentro da render().
//Deve-se manter essa função com poucas linhas de codigo.
void render()
{
   desenhaGUI(screenWidth,screenHeight);
   renderizaBotoes();
   renderizaLabels();
   renderizaColorPicker();
   for(list<Figura*>::iterator f = figuras.begin();f!=figuras.end();++f)
   {
       (*f)->render();
   }
   printf("\nsize: %d\n",figuras.size());
}

//funcao para tratamento de mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int wheel, int direction, int x, int y)
{
   mouseX = x; //guarda as coordenadas do mouse para exibir dentro da render()
   mouseY = y;

   printf("\nmouse %d %d %d %d %d %d", button, state, wheel, direction,  x, y);

   if( button==0 && state == 0 ) //clicou com botao esquerdo
   {
       for(list<Botao>::iterator i = botoes.begin();i!=botoes.end();++i)
       {
           if(i->Colidiu(x,y))
           {
               switch(i->getFigura())
               {
                   case 'a':
                        for(list<Figura*>::iterator i = figuras.begin();i!=figuras.end();++i)
                        {
                            figuras.erase(i);
                            carregado = false;
                        }
                        break;
                   case 'f':
                        switch(preenchidag)
                        {
                            case 0 :
                                preenchidag=1;
                                if(figuraSelecionada!=nullptr)
                                    figuraSelecionada->setPreenchida(preenchidag);
                                break;
                            case 1:
                                preenchidag=0;
                                if(figuraSelecionada!=nullptr)
                                    figuraSelecionada->setPreenchida(preenchidag);
                                break;
                        }
                   case 'q':
                        proximaFigura = i->getFigura();
                        break;
                   case 'c':
                        proximaFigura = i->getFigura();
                        break;
                   case 't':
                        proximaFigura = i->getFigura();
                        break;
                   case 'p':
                        proximaFigura = i->getFigura();
                        break;
                   case 'h':
                        proximaFigura = i->getFigura();
                        break;
                   case 'o':
                        proximaFigura = i->getFigura();
                        break;
                   case '+':
                        if(figuraSelecionada != nullptr)
                        {
                            figuraSelecionada->setTamanho(figuraSelecionada->getTamanho()+5);
                            tamanho = figuraSelecionada->getTamanho();
                        }
                        else
                            tamanho+=5;
                        break;
                    case '-':
                        if(figuraSelecionada != nullptr && figuraSelecionada->getTamanho()>5)
                        {
                            figuraSelecionada->setTamanho(figuraSelecionada->getTamanho()-5);
                            tamanho = figuraSelecionada->getTamanho();
                        }
                        if(tamanho>5 && figuraSelecionada == nullptr)
                            tamanho-=5;
                        break;
                    case 'm':
                        if(figuraSelecionada != nullptr)
                        {
                            figuras.push_back(new Poligono(figuraSelecionada->getX(),figuraSelecionada->getY(),figuraSelecionada->getTamanho(),
                                                           figuraSelecionada->getR(),figuraSelecionada->getG(),figuraSelecionada->getB(),
                                                           figuraSelecionada->getPreenchida(),figuraSelecionada->getLados(),figuraSelecionada->getAngulo()));
                            for(auto i = figuras.begin();i != figuras.end();++i)
                            {
                                if(*i == figuraSelecionada)
                                    figuras.erase(i);
                            }

                        }
                        break;
                    case '>':
                        if(figuraSelecionada != nullptr)
                        {
                            figuraSelecionada->rotaciona(-(pi/18));
                        }
                        break;
                    case '<':
                        if(figuraSelecionada != nullptr)
                        {
                            figuraSelecionada->rotaciona(pi/18);
                        }
                        break;
                    case 's':
                        salvar();
                        break;
                    case 'l':
                        carregar();
                        break;
               }
           }
       }


       if(mouseX<880)
       {
            figuraSelecionada = nullptr;
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
                    figuras.push_back(new Poligono(mouseX,mouseY,tamanho,rg,gg,bg,preenchidag,360,0));
                    proximaFigura = NULL;
                    break;
                case 't':
                    figuras.push_back(new Poligono(mouseX,mouseY,tamanho,rg,gg,bg,preenchidag,3,0));
                    proximaFigura = NULL;
                    break;
                case 'q':
                    figuras.push_back(new Poligono(mouseX,mouseY,tamanho,rg,gg,bg,preenchidag,4,pi/4));
                    proximaFigura = NULL;
                    break;
                case 'p':
                    figuras.push_back(new Poligono(mouseX,mouseY,tamanho,rg,gg,bg,preenchidag,5,0));
                    proximaFigura = NULL;
                    break;
                case 'h':
                    figuras.push_back(new Poligono(mouseX,mouseY,tamanho,rg,gg,bg,preenchidag,7,0));
                    proximaFigura = NULL;
                    break;
                case 'o':
                    figuras.push_back(new Poligono(mouseX,mouseY,tamanho,rg,gg,bg,preenchidag,8,0));
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
                    tamanho=(*i)->getTamanho();
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
                        tamanho=(*i)->getTamanho();
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
