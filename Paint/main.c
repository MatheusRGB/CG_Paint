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

//Vetor de poligonos
int qtd_pontos_poligonos[100] = {0};
int qtd_poligonos = 0;
Ponto poligonos[100][100];

//Fun  o para adicionar um ponto no vetor
void addPontos(float x, float y){
    pontos[qtd_pontos].x = x;
    pontos[qtd_pontos].y = y;

    printf("Ponto adicionado: (%.2f, %.2f)\n", pontos[qtd_pontos].x, pontos[qtd_pontos].y);
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

    printf("Poligono %d adicionado com ponto x: %.2f \n", qtd_poligonos, poligonos[qtd_poligonos][qtd_pontos_poligonos[qtd_poligonos]].x);

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

//Funçoes relacionadas com o mouse
int OP = 0, mousepressionado = 0;
float mousex, mousey, transX, transY;

void getMouse(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        mousepressionado = 1;
        int window_width = glutGet(GLUT_WINDOW_WIDTH);
        int window_height = glutGet(GLUT_WINDOW_HEIGHT);
        transX = ((float)x / (float)window_width - 0.5) * 2.0;
        transY = ((float)(window_height - y) / (float)window_height - 0.5) * 2.0;

        mousex = ((float)x / (float)window_width - 0.5) * 2.0;
        mousey = ((float)(window_height - y) / (float)window_height - 0.5) * 2.0;
    } else if(button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        mousepressionado = 0;
    }
    if(button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
        if(OP == 0){
            printf("(%.2f, %.2f)", mousex, mousey);
        }

        if(OP == 3){
             qtd_poligonos++;
             printf("poligono criado com sucesso.\n");
             OP = 0;
        }else{
            OP = 0;
        }
    }
    if(OP == 1) {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){

            int window_width = glutGet(GLUT_WINDOW_WIDTH);
            int window_height = glutGet(GLUT_WINDOW_HEIGHT);

            float window_x = ((float)x / (float)window_width - 0.5) * 2.0;
            float window_y = ((float)(window_height - y) / (float)window_height - 0.5) * 2.0;

            addPontos(window_x, window_y);
            //glutPostRedisplay();
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
            //glutPostRedisplay();
        }
    }
}
void motion_callback(int x, int y) {
    if(mousepressionado == 1) {
        int window_width = glutGet(GLUT_WINDOW_WIDTH);
        int window_height = glutGet(GLUT_WINDOW_HEIGHT);
        transX = ((float)x / (float)window_width - 0.5) * 2.0;
        transY = ((float)(window_height - y) / (float)window_height - 0.5) * 2.0;

    }
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
//Função para selecionar um ponto.
float selecX;
float selecY;
int selecionaPonto(float px, float py, float mx, float my, float t) {
    for(int i = 0; i < qtd_pontos; i++) {
        if(mx <= pontos[i].x + t && mx >= pontos[i].x - t) {
            if(my <= pontos[i].y + t && my >= pontos[i].y - t) {
                printf("ponto selecionado: (%.2f, %.2f)\n", pontos[i].x, pontos[i].y);
                selecX = pontos[i].x;
                selecY = pontos[i].y;
                return 1;
            }
        }
    }
    return 0;
}
//Função para selecionar um poligono, diz se está dentro ou fora.
int intersec = 0;
int selectPoligon;

int selecionaPoligono() {
    float mx = mousex;
    float my = mousey;
    int aux = 0;
    for(int i = 0; i < qtd_poligonos; i++){
        if(aux == 1){
            break;
        }
        for(int j = 0; j < qtd_pontos_poligonos[i]; j++){
            for( int k = 0; k < qtd_pontos_poligonos[i]; k++){
                if(((poligonos[i][j].x > mx && poligonos[i][k].x > mx) && ((poligonos[i][j].y > my && poligonos[i][k].y < my) || (poligonos[i][j].y < my && poligonos[i][k].y > my)))) {
                    selectPoligon = i;
                    intersec++;

                    if(((intersec/2) % 2 != 0) && (j+1 == qtd_pontos_poligonos[i])){
                        aux = 1;
                    }
                }
            }
        }
    }

    int n_intersec = intersec/2;
    intersec = 0;

    if( (n_intersec) % 2 != 0){
        printf("Dentro, poligono %d\n",selectPoligon);
    }else{
        printf("Fora\n");
    }

    return 0;

}
//função para transladar um ponto (NAO ESTA FUNCIONANDO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!)
void transPonto() {
    //int verifica = selecionaPonto(pontos->x, pontos->y, mousex, mousey, 0.02);
    Ponto newponto[100];
    int j = 0;

    for (int i = 0; i < qtd_pontos; i++){
        if ((pontos[i].x == selecX) && (pontos[i].y == selecY)){
            newponto[j].x = pontos[i].x + transX;
            newponto[j].y = pontos[i].y + transY;
            j++;
        }
    }
    for(int i = 0; i < qtd_pontos; i++){
        pontos[i].x = newponto[i].x;
        pontos[i].y = newponto[i].y;
    }
    glutPostRedisplay();
}

//Função para apagar um ponto
void limparPontos() {
    Ponto newpontos[100];
    int j = 0;

    for (int i = 0; i < qtd_pontos; i++){
        if ((pontos[i].x != selecX) && (pontos[i].y != selecY)){
            newpontos[j].x = pontos[i].x;
            newpontos[j].y = pontos[i].y;
            j++;
         }
    }

    for(int i = 0; i < qtd_pontos; i++){
        pontos[i].x = newpontos[i].x;
        pontos[i].y = newpontos[i].y;
    }

    qtd_pontos--;
    glutPostRedisplay();
}

void apagarPoligono(){
    Ponto newpoligono[100][100];
    int j = 0;

    for(int i = 0; i < qtd_poligonos; i++){
        for(int j = 0; j < qtd_pontos_poligonos[i]; j++){
            if(i!= selectPoligon){
                newpoligono[j][qtd_pontos_poligonos[j]].x = poligonos[qtd_poligonos][qtd_pontos_poligonos[qtd_poligonos]].x;
                newpoligono[j][qtd_pontos_poligonos[j]].y = poligonos[qtd_poligonos][qtd_pontos_poligonos[qtd_poligonos]].y;
            }
        }
    }

    for(int i = 0; i < qtd_poligonos; i++){
        for(int j = 0; j < qtd_pontos_poligonos[i]; j++){
                newpoligono[qtd_poligonos][qtd_pontos_poligonos[j]].x = poligonos[qtd_poligonos][qtd_pontos_poligonos[qtd_poligonos]].x;
                newpoligono[qtd_poligonos][qtd_pontos_poligonos[j]].y = poligonos[qtd_poligonos][qtd_pontos_poligonos[qtd_poligonos]].y;
        }
    }

    //qtd_poligonos--;
    qtd_pontos_poligonos[selectPoligon] = 0;

}
//MENUS
void sair() {exit(0);}

int verificaPonto;
void menuSeleciona(int opcao) {
        switch(opcao) {
        case 1:
            printf("mouse clicou em: (%.2f, %.2f)", mousex, mousey);
		    verificaPonto = selecionaPonto(pontos->x, pontos->y, mousex, mousey, 0.02);
            if(verificaPonto == 0) {
                printf("Nao ha pontos no local selecionado.\n");
            }
            break;
        case 2:
            printf("Selecionou a reta\n");
            break;
        case 3:
            selecionaPoligono();
            break;
    }
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

void menuTransladar(int opcao) {
        switch(opcao) {
        case 1:
            transPonto();
            printf("Transladou o ponto\n");
            break;
        case 2:
            printf("Transladou a reta\n");
            break;
        case 3:
            printf("Transladou o poligono\n");
            break;
    }
}
void menuRotacionar(int opcao) {
        switch(opcao) {
        case 1:
            printf("Rotacionou a reta\n");
            break;
        case 2:
            printf("Rotacionou o poligono\n");
            break;
    }
}
void menuEscalonar(int opcao) {
        switch(opcao) {
        case 1:
            printf("Escalonou a reta\n");
            break;
        case 2:
            printf("Escalonou o poligono\n");
            break;
    }
}

void menuApaga(int opcao) {
        switch(opcao) {
        case 1:
            limparPontos();
            printf("Apagou o ponto\n");
            break;
        case 2:
            printf("Apagou a reta\n");
            break;
        case 3:
            apagarPoligono();
            printf("Apagou o poligono\n");
            break;
    }
}

void mainMenu(int valor) {
	switch (valor)
	{
	case 0:
		sair();
		break;
	case 1:
		break;
	case 2:

		break;
	case 3:

		break;
	}
}

void menu() {
    int menu1 = glutCreateMenu(menuFormas);
    glutAddMenuEntry("ponto", 1);
    glutAddMenuEntry("reta", 2);
    glutAddMenuEntry("poligono", 3);

    int menu2 = glutCreateMenu(menuTransladar);
    glutAddMenuEntry("ponto", 1);
    glutAddMenuEntry("reta", 2);
    glutAddMenuEntry("poligono", 3);

    int menu3 = glutCreateMenu(menuSeleciona);
    glutAddMenuEntry("ponto", 1);
    glutAddMenuEntry("reta", 2);
    glutAddMenuEntry("poligono", 3);

    int menu4 = glutCreateMenu(menuRotacionar);
    glutAddMenuEntry("reta", 1);
    glutAddMenuEntry("poligono", 2);

    int menu5 = glutCreateMenu(menuEscalonar);
    glutAddMenuEntry("reta", 1);
    glutAddMenuEntry("poligono", 2);

    int menu6 = glutCreateMenu(menuApaga);
    glutAddMenuEntry("ponto", 1);
    glutAddMenuEntry("reta", 2);
    glutAddMenuEntry("poligono", 3);

    int menuMain = glutCreateMenu(mainMenu);
    glutAddSubMenu("Selecionar", menu3);
    glutAddSubMenu("Desenhar", menu1);
    glutAddSubMenu("Transladar", menu2);
    glutAddSubMenu("Rotacionar", menu4);
    glutAddSubMenu("Escalonar", menu5);
	glutAddSubMenu("Apagar", menu6);
	glutAddMenuEntry("Sair", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char** argv){

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,0);
    glutCreateWindow("Paint_2");

    init();
    glutMouseFunc(getMouse);
    glutMotionFunc(motion_callback);
    glutDisplayFunc(display);
    menu();
    glutMainLoop();

    return 0;
}
