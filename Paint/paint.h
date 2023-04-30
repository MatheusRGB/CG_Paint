#include <stdio.h>
#include <stdlib.h>
//ESTRUTURA DO PONTO
typedef struct{
    float x;
    float y;
}Ponto;

//ESTRUTURA DA RETA
typedef struct{
    Ponto inicio;
    Ponto fim;
}Reta;

// PROTOTIPO DAS FUNCOES
//ADICIONAM AS FORMAS CRIADAS NO VETOR
void addPontos(float, float);
void addReta(float, float, float, float);
void addPoligono(float, float);

// DESENHA AS FORMAS NA TELA
void desenhaPonto();
void desenhaReta();
void desenhaPoligono();

// FUNCOES RELACIONADAS AO MOUSE
void getMouse(int, int, int, int);
void motion_callback(int, int);

//FUNCOES PARA SELECAO DAS FORMAS
int selecionaPonto();
int selecionaReta();
int selecionaPoligono();

//FUNCOES PARA TRANSLACAO DAS FORMAS
void transPonto();
void transReta();
void TransPoli();

//FUNCOES PARA ESCALAR AS FORMAS
void Escalreta();
void Escalpoli();

//FUNCOES PARA ROTACIONAR AS FORMAS
void Rotreta();
void Rotpoli();

//FUNCOES PARA APAGAR AS FORMAS
void limparPontos();
void apagarReta();
void apagarPoligono();

//FUNCOES RELACIONADAS AO TECLADO
void teclado(int, int, int);
void GerenciaTeclado(unsigned char, int, int);

// FUNCOES DO MENU
void sair();
void mainMenu(int);
void menu();
