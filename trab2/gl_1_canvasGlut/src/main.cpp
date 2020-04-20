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
   picker->Render();
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
       arrasta = true;
       for(list<Botao>::iterator i = botoes.begin();i!=botoes.end();++i)
       {
           if(i->Colidiu(x,y))
           {
               switch(i->getFuncao())
               {
                   case 'a':
                        for(list<Figura*>::iterator i = figuras.begin();i!=figuras.end();++i)
                        {
                            figuras.erase(i);
                            carregado = false;
                        }
                        break;
                   case 'P':
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
                   case 'c':
                        proximaFigura = i->getFuncao();
                        break;
                   case '3':
                        proximaFigura = i->getFuncao();
                        break;
                   case '4':
                        proximaFigura = i->getFuncao();
                        break;
                   case '5':
                        proximaFigura = i->getFuncao();
                        break;
                   case '6':
                        proximaFigura = i->getFuncao();
                        break;
                    case '7':
                        proximaFigura = i->getFuncao();
                        break;
                   case '8':
                        proximaFigura = i->getFuncao();
                        break;
                    case 'd':
                        proximaFigura = i->getFuncao();
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
                    case 'F':
                        if(figuraSelecionada != nullptr)
                        {
                            for(auto i = figuras.begin();i != figuras.end();++i)
                            {
                                if(*i == figuraSelecionada)
                                    figuras.erase(i);
                            }
                            figuras.push_back(figuraSelecionada);

                        }
                        break;
                    case 'A':
                        if(figuraSelecionada != nullptr)
                        {
                            for(auto i = figuras.begin();i != figuras.end();++i)
                            {
                                if(*i == figuraSelecionada)
                                    figuras.erase(i);
                            }

                            figuras.push_front(figuraSelecionada);
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
                    figuras.push_back(new Poligono(mouseX,mouseY,tamanho,picker->getR(),picker->getG(),picker->getB(),preenchidag,360,0));
                    proximaFigura = (char)NULL;
                    break;
                case '3':
                    figuras.push_back(new Poligono(mouseX,mouseY,tamanho,picker->getR(),picker->getG(),picker->getB(),preenchidag,3,0));
                    proximaFigura = (char)NULL;
                    break;
                case '4':
                    figuras.push_back(new Poligono(mouseX,mouseY,tamanho,picker->getR(),picker->getG(),picker->getB(),preenchidag,4,pi/4));
                    proximaFigura = (char)NULL;
                    break;
                case '5':
                    figuras.push_back(new Poligono(mouseX,mouseY,tamanho,picker->getR(),picker->getG(),picker->getB(),preenchidag,5,0));
                    proximaFigura = (char)NULL;
                    break;
                case '6':
                    figuras.push_back(new Poligono(mouseX,mouseY,tamanho,picker->getR(),picker->getG(),picker->getB(),preenchidag,6,0));
                    proximaFigura = (char)NULL;
                    break;
                case '7':
                    figuras.push_back(new Poligono(mouseX,mouseY,tamanho,picker->getR(),picker->getG(),picker->getB(),preenchidag,7,0));
                    proximaFigura = (char)NULL;
                    break;
                case '8':
                    figuras.push_back(new Poligono(mouseX,mouseY,tamanho,picker->getR(),picker->getG(),picker->getB(),preenchidag,8,0));
                    proximaFigura = (char)NULL;
                    break;
                case 'd':
                    figuras.push_back(new Poligono(mouseX,mouseY,tamanho,picker->getR(),picker->getG(),picker->getB(),preenchidag,10,0));
                    proximaFigura = (char)NULL;
                    break;
            }
        }
    }
    if( button==0 && state == 1 )//soltou o clique
    {
        arrasta = false;
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
    if(arrasta && figuraSelecionada!=nullptr && mouseX<880)
    {
        figuraSelecionada->setX(mouseX);
        figuraSelecionada->setY(mouseY);
    }
   if(arrasta && picker->getBRed()->Colidiu(x,y))
   {
       picker->setXRed(x);
       if(figuraSelecionada!=nullptr)
       {
           figuraSelecionada->setColor(picker->getR(),picker->getG(),picker->getB());
       }
   }
   if(arrasta && picker->getBGreen()->Colidiu(x,y))
   {
       picker->setXGreen(x);
       if(figuraSelecionada!=nullptr)
       {
           figuraSelecionada->setColor(picker->getR(),picker->getG(),picker->getB());
       }
   }
   if(arrasta && picker->getBBlue()->Colidiu(x,y))
   {
       picker->setXBlue(x);
       if(figuraSelecionada!=nullptr)
       {
           figuraSelecionada->setColor(picker->getR(),picker->getG(),picker->getB());
       }
   }
}

int main(void)
{
   initCanvas(&screenWidth, &screenHeight, "Editor de Figuras Vetoriais - Pedro Rossato");
   iniciaBotoes();
   runCanvas();
}
