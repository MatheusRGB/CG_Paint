#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include "paint.h"

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

//Função para adicionar um ponto no vetor
void addPontos(float x, float y){
    pontos[qtd_pontos].x = x;
    pontos[qtd_pontos].y = y;

    printf("Ponto adicionado: (%.2f, %.2f)\n", pontos[qtd_pontos].x, pontos[qtd_pontos].y);
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

//Funcao para adicionar poligonos no vetor
void addPoligono(float x, float y){
    poligonos[qtd_poligonos][qtd_pontos_poligonos[qtd_poligonos]].x = x;
    poligonos[qtd_poligonos][qtd_pontos_poligonos[qtd_poligonos]].y = y;
    glutPostRedisplay();
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
    glLineWidth(3.0);
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
    for(int i = 0; i < qtd_poligonos; i++){
        glBegin(GL_POLYGON);
        for(int j = 0; j < qtd_pontos_poligonos[i]; j++){
            glColor3f(0,0,1);
            glVertex2f(poligonos[i][j].x, poligonos[i][j].y);
        }
        glEnd();

    }
    
}

//Funçoes para click do mouse
int OP = 0, mousepressionado = 0;
float mousex, mousey, transX, transY;
int selectPoligon;
int selecReta;
void getMouse(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        mousepressionado = 1;
        int window_width = glutGet(GLUT_WINDOW_WIDTH);
        int window_height = glutGet(GLUT_WINDOW_HEIGHT);
        transX = ((float)x / (float)window_width - 0.5) * 2.0;
        transY = ((float)(window_height - y) / (float)window_height - 0.5) * 2.0;

        mousex = ((float)x / (float)window_width - 0.5) * 2.0;
        mousey = ((float)(window_height - y) / (float)window_height - 0.5) * 2.0;
        selecionaPonto();
        selecionaReta();
        selecionaPoligono();

    } else if(button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        mousepressionado = 0;
        transPonto();
    }
    if(button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
        if(OP == 0){
            printf("Coordenadas atuais: (%.2f, %.2f)", mousex, mousey);
            selectPoligon = -1;
            selecReta = -1;
        }

        if(OP == 3){
             qtd_poligonos++;
             printf("poligono criado com sucesso.\n");
             selectPoligon = -1;
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
            
        }
    }
}
// FUNCAO PARA VERIFICAR SE O MOUSE ESTA PRESSIONADO
void motion_callback(int x, int y) {
    if(mousepressionado == 1) {
        int window_width = glutGet(GLUT_WINDOW_WIDTH);
        int window_height = glutGet(GLUT_WINDOW_HEIGHT);
        transX = ((float)x / (float)window_width - 0.5) * 2.0;
        transY = ((float)(window_height - y) / (float)window_height - 0.5) * 2.0;

    }
}
// FUNCIONALIDADE DE TECLAS ESPECIAIS DO TECLADO
float fatE;
float fatR;
void teclado(int key, int x, int y) {
    switch (key)
    {
    case GLUT_KEY_UP:
        fatE = 1.1;
        Escalreta();
        Escalpoli();
        break;
    case GLUT_KEY_DOWN:
        fatE = 0.9;
        Escalreta();
        Escalpoli();
        break;
    case GLUT_KEY_RIGHT:
        fatR = -0.4;
        Rotpoli();
        Rotreta();
        break;
    case GLUT_KEY_LEFT:
        fatR = 0.4;
        Rotpoli();
        Rotreta();
        break;
    case GLUT_KEY_INSERT:
        TransPoli();
        transReta();
        break;
    default:
        break;
    }
    glutPostRedisplay();
}
// FUNCIONALIDADE DAS TECLAS
void GerenciaTeclado(unsigned char key, int x, int y) {
    switch (key)
    {
    case 127: // VALOR ASCII DA TECLA DELETE
        if(selecionaPonto() == 1) {
            limparPontos();
        }
        if(selecionaPoligono() == 0) {
            apagarPoligono();
        }
        if(selecionaReta() == 1) {
            apagarReta();
        }
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

//Função para selecionar um ponto.
float selecX;
float selecY;
int selecionaPonto() {
    float mx = mousex;
    float my = mousey;
    float t = 0.01;
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

//Função para selecionar reta.
int selecionaReta() {
    float mx = mousex;
    float my = mousey;
    float t = 0.03;
    for(int i = 0; i < qtd_retas; i++) {

        int E = 0;
        int D = 0;
        int A = 0;
        int B = 0;

        if((mx <= retas[i].inicio.x + t && mx >= retas[i].inicio.x - t) || (mx <= retas[i].fim.x + t && mx >= retas[i].fim.x - t)) {
            if((my <= retas[i].inicio.y + t && my >= retas[i].inicio.y - t) || (my <= retas[i].fim.y + t && my >= retas[i].fim.y - t)) {
                printf("reta selecionada: (%.2f, %.2f) ate (%.2f, %.2f)\n", retas[i].inicio.x, retas[i].inicio.y, retas[i].fim.x, retas[i].fim.y);
                selecReta = i;
                return 1;
            }
        }else{
            //Esquerda/Direta
            if(retas[i].inicio.x < mx - t){
                if(retas[i].fim.x > mx + t){
                    E = 1, D = 1;
                }
            }
            //Direita/Esquerda
            if(retas[i].inicio.x > mx + t){
                if(retas[i].fim.x < mx - t){
                    E =1, D = 1;
                }
            }

            //Baixo/Cima
            if(retas[i].inicio.y < my - t){
                if(retas[i].fim.y > my + t){
                    B = 1, A = 1;
                }
            }
            //Cima/Baixo
            else if(retas[i].inicio.y > my + t){
                if(retas[i].fim.y < my - t ){
                    A = 1, B = 1;
                }
            }

            if(E==1 && D==1){
                if((my <= retas[i].inicio.y + t && my >= retas[i].inicio.y - t) || (my <= retas[i].fim.y + t && my >= retas[i].fim.y - t)){
                    printf("reta selecionada: (%.2f, %.2f) ate (%.2f, %.2f)\n", retas[i].inicio.x, retas[i].inicio.y, retas[i].fim.x, retas[i].fim.y);
                    selecReta = i;
                    E = 0;
                    D = 0;
                    return 1;
                }
            }

            else if(A==1 && B==1){
                if(((mx <= retas[i].inicio.x + t && mx >= retas[i].inicio.x - t) || (mx <= retas[i].fim.x + t && mx >= retas[i].fim.x - t))){
                    printf("reta selecionada: (%.2f, %.2f) ate (%.2f, %.2f)\n", retas[i].inicio.x, retas[i].inicio.y, retas[i].fim.x, retas[i].fim.y);
                    selecReta = i;
                    B = 0;
                    A = 0;
                    return 1;
                }
            }


        }

    }
    return 0;
}

//Função para selecionar um poligono, diz se está dentro ou fora.
int intersec = 0;
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
    }

    return 0;

}

//função para transladar um ponto (Por click).
void transPonto() {

    for (int i = 0; i < qtd_pontos; i++){
        if ((pontos[i].x == selecX) && (pontos[i].y == selecY)){
            float offX = transX - pontos[i].x;
            float offY = transY - pontos[i].y;

           float MatrizT[3][3] = {
           {1,0,offX},
           {0,1,offY},
           {0,0,   1}
           };

           float MatrizP[3][1] = {
           {pontos[i].x},
           {pontos[i].y},
           {     1    }
           };

           float MatrizR[3][1];

           for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 1; j++) {
                    MatrizR[i][j] = 0;
                    for (int k = 0; k < 3; k++) {
                        MatrizR[i][j] += MatrizT[i][k] * MatrizP[k][j];
                    }
                }
            }

            pontos[i].x = MatrizR[0][0];
            pontos[i].y = MatrizR[1][0];
            glutPostRedisplay();
        }
    }
}

//FUNCAO DE TRANSLACAO DA RETA
void transReta() {
    float centroideX = 0;
    float centroideY = 0;

    centroideX = centroideX + retas[selecReta].inicio.x + retas[selecReta].fim.x;
    centroideY = centroideY + retas[selecReta].inicio.y + retas[selecReta].fim.y;

    centroideX = (centroideX/2);
    centroideY = (centroideY/2);

    int window_width = glutGet(GLUT_WINDOW_WIDTH);
    int window_height = glutGet(GLUT_WINDOW_HEIGHT);

    for (int i = 0; i < qtd_retas; i++){

        if (i == selecReta){
            float offX = transX - centroideX;
            float offY = transY - centroideY;

           float MatrizT[3][3] = {
           {1,0,offX},
           {0,1,offY},
           {0,0,   1}
           };

           float MatrizP[3][1] = {
           {retas[selecReta].inicio.x},
           {retas[selecReta].inicio.y},
           {     1    }
           };
           float MatrizP2[3][1] = {
           {retas[selecReta].fim.x},
           {retas[selecReta].fim.y},
           {     1    }
           };

           float MatrizR[3][1];
           float MatrizR2[3][1];
           for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 1; j++) {
                    MatrizR[i][j] = 0;
                    for (int k = 0; k < 3; k++) {
                        MatrizR[i][j] += MatrizT[i][k] * MatrizP[k][j];
                    }
                }
            }
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 1; j++) {
                    MatrizR2[i][j] = 0;
                    for (int k = 0; k < 3; k++) {
                        MatrizR2[i][j] += MatrizT[i][k] * MatrizP2[k][j];
                    }
                }
            }

            retas[selecReta].inicio.x = MatrizR[0][0];
            retas[selecReta].inicio.y = MatrizR[1][0];

            retas[selecReta].fim.x = MatrizR2[0][0];
            retas[selecReta].fim.y = MatrizR2[1][0];
            glutPostRedisplay();
        }
    }

}

// FUNCAO DE TRANSLAÇAO DO POLIGONO
void TransPoli(){

    float centroideX = 0;
    float centroideY = 0;
    for(int i =0; i < qtd_pontos_poligonos[selectPoligon]; i++){

        centroideX = centroideX + poligonos[selectPoligon][i].x;
        centroideY = centroideY + poligonos[selectPoligon][i].y;
    }

    centroideX = centroideX/(float)qtd_pontos_poligonos[selectPoligon];
    centroideY = centroideY/(float)qtd_pontos_poligonos[selectPoligon];

    int window_width = glutGet(GLUT_WINDOW_WIDTH);
    int window_height = glutGet(GLUT_WINDOW_HEIGHT);

    for(int n =0; n < qtd_pontos_poligonos[selectPoligon]; n++){

        float offX = mousex - centroideX;
        float offY = mousey - centroideY;

        printf("Ponto selecionado: %.2f, %.2f\n",poligonos[selectPoligon][n].x, poligonos[selectPoligon][n].y );
        printf("ponto destino: %.2f, %.2f\n", transX, transY);
        printf("OffX: %.2f, offy: %.2f\n", offX, offY);

        float MatrizT[3][3] = {
           {1,0,offX},
           {0,1,offY},
           {0,0,   1}
           };

        float MatrizP[3][1] = {
           {  (poligonos[selectPoligon][n].x)  },
           {  (poligonos[selectPoligon][n].y)  },
           {     1    }
           };

        float MatrizR[3][1];

        for(int i = 0; i < 3; i++) {
                for (int j = 0; j < 1; j++) {
                    MatrizR[i][j] = 0;
                    for (int k = 0; k < 3; k++) {
                        MatrizR[i][j] += (MatrizT[i][k]) * (MatrizP[k][j]);
                    }
                }
            }

            for (int i = 0; i < 3; i++) {
                printf("%.2f\n", MatrizR[i][0]);
            }

            float newX = MatrizR[0][0];
            float newY = MatrizR[1][0];

            printf("X normal: %.2f\n", newX);
            printf("Y normal: %.2f\n", newY);

            poligonos[selectPoligon][n].x = newX;
            poligonos[selectPoligon][n].y = newY;

            printf("###\n");
            glutPostRedisplay();
    }
}

// FUNCAO DE ESCALA DA RETA
void Escalreta() {
    float centroideX = 0;
    float centroideY = 0;
    int window_width = glutGet(GLUT_WINDOW_WIDTH);
    int window_height = glutGet(GLUT_WINDOW_HEIGHT);
    centroideX = centroideX + retas[selecReta].inicio.x + retas[selecReta].fim.x;
    centroideY = centroideY + retas[selecReta].inicio.y + retas[selecReta].fim.y;

    centroideX = (centroideX/2);
    centroideY = (centroideY/2);

    for (int i = 0; i < qtd_retas; i++){

        if (i == selecReta){
            float offX = centroideX;
            float offY = centroideY;

           float MatrizT[3][3] = {
           {1,0,offX},
           {0,1,offY},
           {0,0,   1}
           };
           float MatrizV[3][3] = {
           {1,0,-offX},
           {0,1,-offY},
           {0,0,    1}
           };
           float MatrizE[3][3] = {
           {fatE  ,0   ,   0},
           {  0   ,fatE,   0},
           {0     ,0   ,   1}
           };
           float MatrizP[3][1] = {
           {retas[selecReta].inicio.x},
           {retas[selecReta].inicio.y},
           {     1    }
           };
           float MatrizP2[3][1] = {
           {retas[selecReta].fim.x},
           {retas[selecReta].fim.y},
           {     1    }
           };

           float MatrizRI[3][1];
           float MatrizRI2[3][3];
           float MatrizRI3[3][3];

           float MatrizRF[3][1];
           float MatrizRF2[3][3];
           float MatrizRF3[3][3];
            //para o primeiro ponto da reta
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    MatrizRI2[i][j] = 0;
                    for (int k = 0; k < 3; k++) {
                        MatrizRI2[i][j] += MatrizT[i][k] * MatrizE[k][j];
                    }
                }
            }

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    MatrizRI3[i][j] = 0;
                    for (int k = 0; k < 3; k++) {
                        MatrizRI3[i][j] += MatrizRI2[i][k] * MatrizV[k][j];
                    }
                }
            }

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 1; j++) {
                    MatrizRI[i][j] = 0;
                    for (int k = 0; k < 3; k++) {
                        MatrizRI[i][j] += MatrizRI3[i][k] * MatrizP[k][j];
                    }
                }
            }
            //para o segundo ponto da reta
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    MatrizRF2[i][j] = 0;
                    for (int k = 0; k < 3; k++) {
                        MatrizRF2[i][j] += MatrizT[i][k] * MatrizE[k][j];
                    }
                }
            }

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    MatrizRF3[i][j] = 0;
                    for (int k = 0; k < 3; k++) {
                        MatrizRF3[i][j] += MatrizRF2[i][k] * MatrizV[k][j];
                    }
                }
            }

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 1; j++) {
                    MatrizRF[i][j] = 0;
                    for (int k = 0; k < 3; k++) {
                        MatrizRF[i][j] += MatrizRF3[i][k] * MatrizP2[k][j];
                    }
                }
            }

            retas[selecReta].inicio.x = (MatrizRI[0][0]);
            retas[selecReta].inicio.y = (MatrizRI[1][0]);

            retas[selecReta].fim.x = (MatrizRF[0][0]);
            retas[selecReta].fim.y = (MatrizRF[1][0]);
            glutPostRedisplay();
        }
    }

}

// FUNCAO DE ESCALA DO POLIGONO
void Escalpoli(){
    float centroideX = 0;
    float centroideY = 0;

    for(int i =0; i < qtd_pontos_poligonos[selectPoligon]; i++){

        centroideX = centroideX + poligonos[selectPoligon][i].x;
        centroideY = centroideY + poligonos[selectPoligon][i].y;
    }

    centroideX = centroideX/(float)qtd_pontos_poligonos[selectPoligon];
    centroideY = centroideY/(float)qtd_pontos_poligonos[selectPoligon];

    for(int n =0; n < qtd_pontos_poligonos[selectPoligon]; n++){

        float offX = centroideX;
        float offY = centroideY;

        float MatrizT[3][3] = {
           {1,0,offX},
           {0,1,offY},
           {0,0,   1}
           };

        float MatrizV[3][3] = {
           {1,0,-offX},
           {0,1,-offY},
           {0,0,    1}
           };

        float MatrizE[3][3] = {
           {fatE  ,0   ,   0},
           {  0   ,fatE,   0},
           {0     ,0   ,   1}
           };

        float MatrizP[3][1] = {
           {  (poligonos[selectPoligon][n].x)},
           {  (poligonos[selectPoligon][n].y)},
           {     1    }
           };

        float MatrizR[3][1];
        float MatrizR2[3][3];
        float MatrizR3[3][3];

        for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    MatrizR2[i][j] = 0;
                    for (int k = 0; k < 3; k++) {
                        MatrizR2[i][j] += MatrizT[i][k] * MatrizE[k][j];
                    }
                }
            }

        for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    MatrizR3[i][j] = 0;
                    for (int k = 0; k < 3; k++) {
                        MatrizR3[i][j] += MatrizR2[i][k] * MatrizV[k][j];
                    }
                }
            }

        for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 1; j++) {
                    MatrizR[i][j] = 0;
                    for (int k = 0; k < 3; k++) {
                        MatrizR[i][j] += MatrizR3[i][k] * MatrizP[k][j];
                    }
                }
            }

            poligonos[selectPoligon][n].x = (MatrizR[0][0]);
            poligonos[selectPoligon][n].y = (MatrizR[1][0]);
            glutPostRedisplay();
    }
}

//Função para rotacionar reta;
void Rotreta(){
    float centroideX = 0;
    float centroideY = 0;
    int window_width = glutGet(GLUT_WINDOW_WIDTH);
    int window_height = glutGet(GLUT_WINDOW_HEIGHT);
    centroideX = centroideX + retas[selecReta].inicio.x + retas[selecReta].fim.x;
    centroideY = centroideY + retas[selecReta].inicio.y + retas[selecReta].fim.y;

    centroideX = (centroideX/2);
    centroideY = (centroideY/2);

    for (int i = 0; i < qtd_retas; i++){

        if (i == selecReta){
            float offX = centroideX;
            float offY = centroideY;

           float MatrizT[3][3] = {
           {1,0,offX},
           {0,1,offY},
           {0,0,   1}
           };

           float MatrizV[3][3] = {
           {1,0,-offX},
           {0,1,-offY},
           {0,0,    1}
           };

           float MatrizE[3][3] = {
           {cos(fatR),-sin(fatR),   0},
           {sin(fatR), cos(fatR),   0},
           {0        ,0         ,   1}
           };

           float MatrizP[3][1] = {
           {retas[selecReta].inicio.x},
           {retas[selecReta].inicio.y},
           {     1    }
           };

           float MatrizP2[3][1] = {
           {retas[selecReta].fim.x},
           {retas[selecReta].fim.y},
           {     1    }
           };

           float MatrizRI[3][1];
           float MatrizRI2[3][3];
           float MatrizRI3[3][3];

           float MatrizRF[3][1];
           float MatrizRF2[3][3];
           float MatrizRF3[3][3];

            //para o primeiro ponto da reta
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    MatrizRI2[i][j] = 0;
                    for (int k = 0; k < 3; k++) {
                        MatrizRI2[i][j] += MatrizT[i][k] * MatrizE[k][j];
                    }
                }
            }

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    MatrizRI3[i][j] = 0;
                    for (int k = 0; k < 3; k++) {
                        MatrizRI3[i][j] += MatrizRI2[i][k] * MatrizV[k][j];
                    }
                }
            }

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 1; j++) {
                    MatrizRI[i][j] = 0;
                    for (int k = 0; k < 3; k++) {
                        MatrizRI[i][j] += MatrizRI3[i][k] * MatrizP[k][j];
                    }
                }
            }

            //para o segundo ponto da reta
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    MatrizRF2[i][j] = 0;
                    for (int k = 0; k < 3; k++) {
                        MatrizRF2[i][j] += MatrizT[i][k] * MatrizE[k][j];
                    }
                }
            }

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    MatrizRF3[i][j] = 0;
                    for (int k = 0; k < 3; k++) {
                        MatrizRF3[i][j] += MatrizRF2[i][k] * MatrizV[k][j];
                    }
                }
            }

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 1; j++) {
                    MatrizRF[i][j] = 0;
                    for (int k = 0; k < 3; k++) {
                        MatrizRF[i][j] += MatrizRF3[i][k] * MatrizP2[k][j];
                    }
                }
            }

            retas[selecReta].inicio.x = (MatrizRI[0][0]);
            retas[selecReta].inicio.y = (MatrizRI[1][0]);

            retas[selecReta].fim.x = (MatrizRF[0][0]);
            retas[selecReta].fim.y = (MatrizRF[1][0]);
            glutPostRedisplay();
        }
    }
}

// FUNCAO DE ROTACAO DO POLIGONO
void Rotpoli(){
    float centroideX = 0;
    float centroideY = 0;

    for(int i =0; i < qtd_pontos_poligonos[selectPoligon]; i++){

        centroideX = centroideX + poligonos[selectPoligon][i].x;
        centroideY = centroideY + poligonos[selectPoligon][i].y;
    }

    centroideX = centroideX/(float)qtd_pontos_poligonos[selectPoligon];
    centroideY = centroideY/(float)qtd_pontos_poligonos[selectPoligon];

     for(int n =0; n < qtd_pontos_poligonos[selectPoligon]; n++){

        float offX = centroideX;
        float offY = centroideY;

        float MatrizT[3][3] = {
           {1,0,offX},
           {0,1,offY},
           {0,0,   1}
           };

        float MatrizV[3][3] = {
           {1,0,-offX},
           {0,1,-offY},
           {0,0,    1}
           };

        float MatrizRT[3][3] = {
           {cos(fatR)  ,-sin(fatR),   0},
           {sin(fatR)  ,cos(fatR),    0},
           {0        ,0      ,    1}
           };

        float MatrizP[3][1] = {
           {  (poligonos[selectPoligon][n].x)},
           {  (poligonos[selectPoligon][n].y)},
           {     1    }
           };

        float MatrizR[3][1];
        float MatrizR2[3][3];
        float MatrizR3[3][3];

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                MatrizR2[i][j] = 0;
                for (int k = 0; k < 3; k++) {
                    MatrizR2[i][j] += MatrizT[i][k] * MatrizRT[k][j];
                }
            }
        }

        for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    MatrizR3[i][j] = 0;
                    for (int k = 0; k < 3; k++) {
                        MatrizR3[i][j] += MatrizR2[i][k] * MatrizV[k][j];
                    }
                }
            }

        for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 1; j++) {
                    MatrizR[i][j] = 0;
                    for (int k = 0; k < 3; k++) {
                        MatrizR[i][j] += MatrizR3[i][k] * MatrizP[k][j];
                    }
                }
            }

        poligonos[selectPoligon][n].x = (MatrizR[0][0]);
        poligonos[selectPoligon][n].y = (MatrizR[1][0]);
        glutPostRedisplay();


     }

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

//Função para apagar reta.
void apagarReta() {
    Reta newretas[100];
    int j = 0;

    for(int i = 0; i < qtd_retas; i++) {
        if(i != selecReta) {
            newretas[j].inicio.x = retas[i].inicio.x;
            newretas[j].inicio.y = retas[i].inicio.y;
            newretas[j].fim.x = retas[i].fim.x;
            newretas[j].fim.y = retas[i].fim.y;
            j++;
        }
    }
    for(int i = 0; i < qtd_retas; i++){
        retas[i].inicio.x = newretas[i].inicio.x;
        retas[i].inicio.y = newretas[i].inicio.y;
        retas[i].fim.x = newretas[i].fim.x;
        retas[i].fim.y = newretas[i].fim.y;
    }
    qtd_retas--;
    glutPostRedisplay();
}

//Função para apagar um poligono.
void apagarPoligono(){
    Ponto newpoligono[100][100];

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

    qtd_pontos_poligonos[selectPoligon] = 0;
    glutPostRedisplay();

}

//MENUS
void sair() {exit(0);}

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
void mainMenu(int valor) {
	switch (valor)
	{
	case 0:
		sair();
		break;
    }
}

// MENU PRINCIPAL
void menu() {
    int menu1 = glutCreateMenu(menuFormas);
    glutAddMenuEntry("ponto", 1);
    glutAddMenuEntry("reta", 2);
    glutAddMenuEntry("poligono", 3);

    int menuMain = glutCreateMenu(mainMenu);
    glutAddSubMenu("Desenhar", menu1);
	glutAddMenuEntry("Sair", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
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

int main(int argc, char** argv){

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,0);
    glutCreateWindow("Paint_2");

    init();
    glutMouseFunc(getMouse);
    glutMotionFunc(motion_callback);
    glutSpecialFunc(teclado);
    glutKeyboardFunc(GerenciaTeclado);
    glutDisplayFunc(display);
    menu();
    glutMainLoop();

    return 0;
}
