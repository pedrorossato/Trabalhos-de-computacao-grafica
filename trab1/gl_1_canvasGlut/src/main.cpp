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

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>

#include "gl_canvas2d.h"

#include "Bmp.h"
#include "Botao.h"


Bmp     *img;
Botao   *btOriginal = NULL; //se a aplicacao tiver varios botoes, sugiro implementar um manager de botoes.
Botao   *btVermelho = NULL;
Botao   *btVerde = NULL;
Botao   *btAzul = NULL;
Botao   *btCinza = NULL;
Botao   *btNegativo = NULL;
Botao   *btDireita = NULL;
Botao   *btEsquerda = NULL;
Botao   *btEscalaNormal = NULL;
Botao   *btEscalaMeio = NULL;
Botao   *btEscalaQuarto = NULL;
Botao   *btEspelhar = NULL;
//variaveis globais.
int opcao  = 50;
int screenWidth = 1080, screenHeight = 720; //largura e altura inicial da tela . Alteram com o redimensionamento de tela.
int mouseX, mouseY; //variaveis globais do mouse para poder exibir dentro da render().
unsigned char *data;
int imagemMostrada = 1; //varivel para a imagem a ser mostrada na render
int rotacao = 0 ;   //valor da rotacao
float escala = 1 ;  //valor da escala
bool espelhar = false; // true se a imagem estiver espelhada
char titulolabel[50];
char canaislabel[50];
char rotacaolabel[10];
char escalalabel[10];

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
       if( btOriginal->Colidiu(x, y) )
       {
           //TODOS CANAIS RGB
           imagemMostrada = 1;
           printf("\nTodos os canais\n");
       }
       if( btVermelho->Colidiu(x, y) )
       {
           //CANAL VERMELHO
           imagemMostrada = 2;
           printf("\nCanal Vermelho\n");
       }
       if( btVerde->Colidiu(x, y) )
       {
           //CANAL VERDE
           imagemMostrada = 3;
           printf("\nCanal Verde\n");
       }
       if( btAzul->Colidiu(x, y) )
       {
           //CANAL AZUL
           imagemMostrada = 4;
           printf("\nCanal Azul\n");
       }
       if( btCinza->Colidiu(x, y) )
       {
           //TONDE DE CINZA
           imagemMostrada = 5;
           printf("\nLuminancia\n");
       }
       if( btNegativo->Colidiu(x, y) )
       {
           //IMAGEM FILTRO NEGATIVO
           imagemMostrada = 6;
           printf("\nNegativo\n");
       }
       if( btDireita->Colidiu(x, y) )
       {
           //INCREMENTA A ROTACAO
           rotacao = rotacao+90;
           if(rotacao==360)
            rotacao = 0;
           printf("\nDireita = %d\n", rotacao);
       }
       if( btEsquerda->Colidiu(x, y) )
       {
           //DECREMENTA A ROTACAO
           rotacao = rotacao - 90;
           if(rotacao==-360)
            rotacao = 0;
           printf("\nEsquerda = %d\n", rotacao);
       }
       if(btEscalaNormal->Colidiu(x, y) )
       {
           escala = 1;
           printf("\nEscala normal\n");
       }
       if(btEscalaMeio->Colidiu(x, y) )
       {
           //ESCALA 1/2
           escala = 0.5;
           printf("\nEscala meia\n");
       }
       if(btEscalaQuarto->Colidiu(x, y) )
       {
           //ESCALA 1/4
           escala = 0.25;
           printf("\nEscala um quarto\n");
       }
       if(btEspelhar->Colidiu(x, y) )
       {
           //ESPELHA A IMAGEM
           espelhar = !espelhar;
           printf("\nEscala um quarto\n");
       }
   }
}
//FUNCAO PARA INICIAR OS TEXTOS(LABELS)
void iniciaLabels()
{
   std::string t = "Trabalho A Computacao Grafica - Pedro Rossato";
   strcpy(titulolabel, t.c_str());
   std::string c = "Canais de cores";
   strcpy(canaislabel, c.c_str());
   std::string r = "Rotacao";
   strcpy(rotacaolabel, r.c_str());
   std::string s = "Escala";
   strcpy(escalalabel, s.c_str());
}
//FUNCAO PARA INICIAR OS BOTOES
void iniciaBotoes()
{
   btOriginal = new Botao(50, 80, 100, 40, "Original");
   btVermelho = new Botao(50,20,100,40, "Vermelho");
   btVerde = new Botao(170,80,100,40,"Verde");
   btAzul = new Botao(170,20,100,40,"Azul");
   btCinza = new Botao(290,80,100,40,"Cinza");
   btNegativo = new Botao(290,20,100,40,"Negativo");
   btEsquerda = new Botao(550,80,100,40,"Esquerda");
   btDireita = new Botao(660,80,100,40,"Direita");
   btEscalaNormal = new Botao(900,80,110,40,"Normal");
   btEscalaMeio = new Botao(900,20,50,40,"1/2");
   btEscalaQuarto = new Botao(960,20,50,40,"1/4");
   btEspelhar = new Botao(610,35,100,40,"Espelhar");
}
//FUNCAO PARA RENDERIZAR BOTOES
void renderizaBotoes()
{
   btOriginal->Render(0,0,0,255,255,255);
   btVermelho->Render(255,0,0,255,255,255);
   btVerde->Render(0,255,0,0,0,0);
   btAzul->Render(0,0,255,255,255,255);
   btCinza->Render(169,169,169,255,255,255);
   btNegativo->Render(25,25,112,255,255,255);
   btDireita->Render(218,165,32,0,0,0);
   btEsquerda->Render(218,165,32,0,0,0);
   btEscalaNormal->Render(192,192,192,0,0,0);
   btEscalaMeio->Render(192,192,192,0,0,0);
   btEscalaQuarto->Render(192,192,192,0,0,0);
   btEspelhar->Render(205,133,63,0,0,0);
}


//funcao chamada continuamente. Deve-se controlar o que desenhar por meio de variaveis globais
//Todos os comandos para desenho na canvas devem ser chamados dentro da render().
//Deve-se manter essa função com poucas linhas de codigo.
void render()
{
   //RENDERIZA A INTERFACE VISUAL
   color((float)112/255,(float)128/255,(float)144/255);
   rectFill(0,0,1080,150);
   rectFill(0,680,1080,720);
   //RENDERIZA OS TEXTOS NA INTERFACE VISUAL
   color(255,255,255);
   text(300,695,titulolabel);
   text(150,130,canaislabel);
   text(610,130,rotacaolabel);
   text(925,130,escalalabel);
   //RENDERIZA OS BOTOES
   renderizaBotoes();
   //RENDERIZA A IMAGEM ATUAL
   switch(imagemMostrada)
   {
        case 1:
            img->Render(300,300,1,1,1,1,rotacao,escala,espelhar); // imagem original
            break;
        case 2:
            img->Render(300,300,1,0,0,1,rotacao,escala,espelhar); // imagem em canal vermerlho
            break;
        case 3:
            img->Render(300,300,0,1,0,1,rotacao,escala,espelhar); // imagem em canal verde
            break;
        case 4:
            img->Render(300,300,0,0,1,1,rotacao,escala,espelhar); // imagem em canal azul
            break;
        case 5:
            img->Render(300,300,0.299,0.587,0.114,2,rotacao,escala,espelhar); // imagem em tons de cinza (luminancia)
            break;
        case 6:
            img->Render(300,300,1,1,1,3,rotacao,escala,espelhar); // imagem em negativo
            break;
   }
}

int main(void)
{
   initCanvas(&screenWidth, &screenHeight, "Trabalho CG - Pedro Rossato");
   //INICIA LABELS
   iniciaLabels();
   // INICIA BOTOES
   iniciaBotoes();
   // INICIA A IMAGEM
   img = new Bmp(".\\img2.bmp");
   img->convertBGRtoRGB();

   runCanvas();
}
