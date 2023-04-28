#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <GL/glut.h>

//Estrutura do ponto
typedef struct{
    float x;
    float y;
}Ponto;

//Estrutura da Reta
typedef struct{
    Ponto inicio;
    Ponto fim;
}Reta;

//Vetor de pontos
int qtd_pontos = 0;
Ponto pontos[100];

// Controle de pontos
int ponto_inicial = 0;
Ponto novo_ponto;

//Vetor de retas
int qtd_retas = 0;
Reta retas[100];

//Vetor de pontos
int qtd_pontos_poligonos[100] = {0};
int qtd_poligonos = 0;
Ponto poligonos[100][100];

//Fun  o para adicionar um ponto no vetor
void addPontos(float x, float y){
    pontos[qtd_pontos].x = x;
    pontos[qtd_pontos].y = y;

    printf("Ponto adicionado %f \n", pontos[qtd_pontos].x);
    qtd_pontos++;

}

//Fun  o para adicionar reta no vetor
void addReta(float x, float y, float x2, float y2){
    retas[qtd_retas].inicio.x = x;
    retas[qtd_retas].inicio.y = y;

    retas[qtd_retas].fim.x = x2;
    retas[qtd_retas].fim.y = y2;

    qtd_retas++;
}
//Funcao para adicionar poligonos no vetor
void addPoligono(float x, float y){
    poligonos[qtd_poligonos][qtd_pontos_poligonos[qtd_poligonos]].x = x;
    poligonos[qtd_poligonos][qtd_pontos_poligonos[qtd_poligonos]].y = y;

    printf("Poligono %d adicionado com ponto x: %f \n", qtd_poligonos, poligonos[qtd_poligonos][qtd_pontos_poligonos[qtd_poligonos]].x);

    qtd_pontos_poligonos[qtd_poligonos]++;

}

//Desenha todos os pontos do vetor
void desenhaPonto(){
    glPointSize(5.0);
    glBegin(GL_POINTS);
    for(int i = 0; i < qtd_pontos; i++){
        glColor3f(1,0,0);
        glVertex2f(pontos[i].x, pontos[i].y);
    }
    glEnd();
}

//Desenha todas as retas do vetor
void desenhaReta(){
    glLineWidth(2.0);
    glBegin(GL_LINES);
    for(int i = 0; i < qtd_retas; i++){
        glColor3f(0,1,0);
        glVertex2f(retas[i].inicio.x, retas[i].inicio.y);
        glVertex2f(retas[i].fim.x, retas[i].fim.y);
    }
    glEnd();
}

//Desenha todas os poligonos do vetor
void desenhaPoligono(){
    glPointSize(5.0);
    //glBegin(GL_POLYGON);
    for(int i = 0; i < qtd_poligonos; i++){
        glBegin(GL_POLYGON);
        for(int j = 0; j < qtd_pontos_poligonos[i]; j++){
            glColor3f(0,0,1);
            glVertex2f(poligonos[i][j].x, poligonos[i][j].y);
        }
        glEnd();

    }
    //glEnd();
}

int OP = 0;
void getMouse(int button, int state, int x, int y){

    if(OP == 1) {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){

            int window_width = glutGet(GLUT_WINDOW_WIDTH);
            int window_height = glutGet(GLUT_WINDOW_HEIGHT);

            float window_x = (- 1 + 2 *(float)x / (float)window_width );
            float window_y = (1 - 2 * (float)(y) / (float)window_height);

            addPontos(window_x, window_y);
        }
    } else if(OP == 2) {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
            int window_width = glutGet(GLUT_WINDOW_WIDTH);
            int window_height = glutGet(GLUT_WINDOW_HEIGHT);

            float window_x = ((float)x / (float)window_width - 0.5) * 2.0;
            float window_y = ((float)(window_height - y) / (float)window_height - 0.5) * 2.0;

            if (ponto_inicial == 0) {
                novo_ponto.x = window_x;
                novo_ponto.y = window_y;
                ponto_inicial = 1;
            } else {
                addReta(novo_ponto.x, novo_ponto.y, window_x, window_y);
                ponto_inicial = 0;
            }
        }
    } else if(OP == 3) {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){

            int window_width = glutGet(GLUT_WINDOW_WIDTH);
            int window_height = glutGet(GLUT_WINDOW_HEIGHT);

            float window_x = ((float)x / (float)window_width - 0.5) * 2.0;
            float window_y = ((float)(window_height - y) / (float)window_height - 0.5) * 2.0;

            addPoligono(window_x, window_y);

            glutPostRedisplay();
        }else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN){
            qtd_poligonos++;
            printf("novo poligono criado\n");

            glutPostRedisplay();
        }
    }
    glutPostRedisplay();
}

void display (void){
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    desenhaPonto();
    desenhaReta();
    desenhaPoligono();

    glFlush();

}

void init (){
    glClearColor(1.0,1.0,1.0,0.0);

    glMatrixMode(GL_PROJECTION);
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);


}

void menuFormas(int opcao) {
    switch(opcao) {
        case 1:
            printf("Criando pontos\n");
            OP = 1;
            break;
        case 2:
            printf("Criando linhas\n");
            OP = 2;
            break;
        case 3:
            printf("Criando poligonos\n");
            OP = 3;
            break;
    }
}

int main(int argc, char** argv){

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB);
    glutInitWindowSize(400,400);
    glutInitWindowPosition(100,0);
    glutCreateWindow("Paint_2");

    init();
    glutMouseFunc(getMouse);
    glutDisplayFunc(display);

    //Cria menu
    int menu;
    menu = glutCreateMenu(menuFormas);
    glutAddMenuEntry("Cria ponto", 1);
    glutAddMenuEntry("Cria reta", 2);
    glutAddMenuEntry("Cria poligono", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();

    return 0;
}
