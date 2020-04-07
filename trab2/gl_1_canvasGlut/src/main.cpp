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

#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.
#include <vector>
#include "main.h"
#include "Botao.h"

using namespace std;


//variavel global para selecao do que sera exibido na canvas.
int opcao  = 50;
int screenWidth = 1080, screenHeight = 720; //largura e altura inicial da tela . Alteram com o redimensionamento de tela.
int mouseX, mouseY; //variaveis globais do mouse para poder exibir dentro da render().
char figuraSelecionada;
vector<Botao>botoes;
vector<Circulo>circulos;
vector<Triangulo>triangulos;

void renderizaBotoes()
{
    for(auto b = botoes.begin();b!=botoes.end();++b)
    {
        switch(b->getFigura())
        {
            case 'c':
                b->Render(0,0,255,255,255,255);
                break;
            case 't':
                b->Render(255,0,0,255,255,255);
                break;
        }

    }
}
void DrawMouseScreenCoords()
{
    char str[100];
    sprintf(str, "Mouse: (%d,%d)", mouseX, mouseY);
    text(10,300, str);
    sprintf(str, "Screen: (%d,%d)", screenWidth, screenHeight);
    text(10,320, str);
}

//funcao chamada continuamente. Deve-se controlar o que desenhar por meio de variaveis globais
//Todos os comandos para desenho na canvas devem ser chamados dentro da render().
//Deve-se manter essa função com poucas linhas de codigo.
void render()
{
   DrawMouseScreenCoords(mouseX,mouseY,screenWidth,screenHeight);
   desenhaGUI(screenWidth,screenHeight);
   renderizaBotoes();

   for(auto c = circulos.begin();c!=circulos.end();++c)
   {
       c->Render(0,0,0);
   }
   for(auto t = triangulos.begin();t!=triangulos.end();++t)
   {
       t->Render(0,0,0);
   }
}

//funcao chamada toda vez que uma tecla for pressionada.
void keyboard(int key)
{
   printf("\nTecla: %d" , key);
   if( key < 200 )
   {
      opcao = key;
   }

   switch(key)
   {
      case 27:
	     exit(0);
	  break;

   }
}

//funcao chamada toda vez que uma tecla for liberada
void keyboardUp(int key)
{
   printf("\nLiberou: %d" , key);
}

//funcao para tratamento de mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int wheel, int direction, int x, int y)
{
   mouseX = x; //guarda as coordenadas do mouse para exibir dentro da render()
   mouseY = y;

   printf("\nmouse %d %d %d %d %d %d", button, state, wheel, direction,  x, y);

   if( state == 0 ) //clicou
   {
       for(auto i = botoes.begin();i!=botoes.end();++i)
       {
           if( i->Colidiu(x, y) )
           {
               figuraSelecionada = i->getFigura();
               printf("\nClicou no %c\n", i->getFigura());
           }

       }
       if(mouseX<880)
       {
           switch(figuraSelecionada)
           {
                case 'c':
                    circulos.push_back(Circulo(mouseX,mouseY,30));
                    break;
                case 't':
                    triangulos.push_back(Triangulo(mouseX,mouseY,30));
                    break;
           }
       }
   }
}
void iniciaBotoes()
{
    botoes.push_back(Botao(960,600,100,40,"Circulo",'c'));
    botoes.push_back(Botao(960,550,100,40,"Triangulo",'t'));
}

int main(void)
{
   initCanvas(&screenWidth, &screenHeight, "Titulo da Janela: Canvas 2D - Pressione 1, 2, 3");
   iniciaBotoes();
   runCanvas();
}
