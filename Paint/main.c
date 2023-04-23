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

//Vetor de retas
int qtd_retas = 0;
Reta retas[100];

//Função para adicionar um ponto no vetor
void addPontos(float x, float y){
    pontos[qtd_pontos].x = x;
    pontos[qtd_pontos].y = y;

    printf("Ponto adicionado %f", pontos[qtd_pontos].x);
    qtd_pontos++;

}

//Função para adicionar reta no vetor
void addReta(float x, float y, float x2, float y2){
    retas[qtd_retas].inicio.x = x;
    retas[qtd_retas].inicio.y = y;

    retas[qtd_retas].fim.x = x2;
    retas[qtd_retas].fim.y = y2;

    qtd_retas++;
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

void getMouse(int button, int state, int x, int y){
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        POINT posiMouse;
        GetCursorPos(&posiMouse);
        addPontos((float)posiMouse.x, (float)posiMouse.y);

        /*
        int window_width = glutGet(GLUT_WINDOW_WIDTH);
        int window_height = glutGet(GLUT_WINDOW_HEIGHT);

        float window_x = ((float)x / (float)window_width - 0.5) * 2.0;
        float window_y = ((float)(window_height - y) / (float)window_height - 0.5) * 2.0;

        addPontos(window_x, window_y);
        */
        glutPostRedisplay();
    }
}

void display (void){
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    desenhaPonto();
    desenhaReta();

    glFlush();

}

void init (){
    glClearColor(1.0,1.0,1.0,0.0);

    glMatrixMode(GL_PROJECTION);
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);


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

    glutMainLoop();

    return 0;
}
