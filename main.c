#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#define M_PI 3.14159265358979323846

int largura=500, altura=500;
void Obelisco(void);
void Iniciar(void);

// Variáveis para controle da câmera em coordenadas polares
float raio = 8.0f;        // Distância da câmera ao centro
float altura_cam = 4.0f;  // Altura da câmera
float angulo = 0.0f;      // Ângulo de rotação em radianos

// Converter coordenadas polares para cartesianas
float a[3] = {0.0f, 0.0f, 0.0f};

void DesenharCirculo(float raio, float y, int segmentos) {
    float angulo;
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < segmentos; i++) {
        angulo = 2.0f * M_PI * i / segmentos;
        glVertex3f(cos(angulo) * raio, y, sin(angulo) * raio);
    }
    glEnd();
}

void DesenharBaseCircular() {
    // Desenha o chão circular principal com cor de grama
    glColor3f(0.2f, 0.6f, 0.2f);  // Tom de verde para grama
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, 0.0f, 0.0f);  // Centro
    for(int i = 0; i <= 360; i += 10) {
        float angle = i * M_PI / 180.0f;
        glVertex3f(cos(angle) * 2.0f, 0.0f, sin(angle) * 2.0f);
    }
    glEnd();

    // Desenha os círculos concêntricos com um tom de verde mais escuro
    glColor3f(0.15f, 0.5f, 0.15f);  // Verde mais escuro para os círculos
    for(float r = 0.5f; r <= 2.0f; r += 0.5f) {
        DesenharCirculo(r, 0.01f, 50);
    }
}

void DesenharObeliscoComContornos() {
    // Corpo do obelisco
    float corpo_y = 0.01f;
    
    // Primeiro desenha as faces preenchidas
    glBegin(GL_QUADS);
    glColor3f(0.9f, 0.9f, 0.9f);
    
    // Face frontal
    glVertex3f(-0.2f, corpo_y, 0.2f);
    glVertex3f(0.2f, corpo_y, 0.2f);
    glVertex3f(0.05f, corpo_y + 1.8f, 0.05f);
    glVertex3f(-0.05f, corpo_y + 1.8f, 0.05f);
    
    // Face direita
    glVertex3f(0.2f, corpo_y, 0.2f);
    glVertex3f(0.2f, corpo_y, -0.2f);
    glVertex3f(0.05f, corpo_y + 1.8f, -0.05f);
    glVertex3f(0.05f, corpo_y + 1.8f, 0.05f);
    
    // Face traseira
    glVertex3f(0.2f, corpo_y, -0.2f);
    glVertex3f(-0.2f, corpo_y, -0.2f);
    glVertex3f(-0.05f, corpo_y + 1.8f, -0.05f);
    glVertex3f(0.05f, corpo_y + 1.8f, -0.05f);
    
    // Face esquerda
    glVertex3f(-0.2f, corpo_y, -0.2f);
    glVertex3f(-0.2f, corpo_y, 0.2f);
    glVertex3f(-0.05f, corpo_y + 1.8f, 0.05f);
    glVertex3f(-0.05f, corpo_y + 1.8f, -0.05f);
    glEnd();

   
    glLineWidth(2.0f);
    glColor3f(0.7f, 0.7f, 0.7f);  // Cor mais escura para os contornos
    
    // Contornos do corpo
    glBegin(GL_LINE_LOOP);
    glVertex3f(-0.2f, corpo_y, 0.2f);
    glVertex3f(0.2f, corpo_y, 0.2f);
    glVertex3f(0.05f, corpo_y + 1.8f, 0.05f);
    glVertex3f(-0.05f, corpo_y + 1.8f, 0.05f);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex3f(0.2f, corpo_y, 0.2f);
    glVertex3f(0.2f, corpo_y, -0.2f);
    glVertex3f(0.05f, corpo_y + 1.8f, -0.05f);
    glVertex3f(0.05f, corpo_y + 1.8f, 0.05f);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex3f(0.2f, corpo_y, -0.2f);
    glVertex3f(-0.2f, corpo_y, -0.2f);
    glVertex3f(-0.05f, corpo_y + 1.8f, -0.05f);
    glVertex3f(0.05f, corpo_y + 1.8f, -0.05f);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex3f(-0.2f, corpo_y, -0.2f);
    glVertex3f(-0.2f, corpo_y, 0.2f);
    glVertex3f(-0.05f, corpo_y + 1.8f, 0.05f);
    glVertex3f(-0.05f, corpo_y + 1.8f, -0.05f);
    glEnd();

    // Ponta do obelisco
    float ponta_y = corpo_y + 1.8f;
    
    // Faces da ponta preenchidas
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.9f, 0.8f);
    
    glVertex3f(-0.05f, ponta_y, 0.05f);
    glVertex3f(0.05f, ponta_y, 0.05f);
    glVertex3f(0.0f, ponta_y + 0.2f, 0.0f);
    
    glVertex3f(0.05f, ponta_y, 0.05f);
    glVertex3f(0.05f, ponta_y, -0.05f);
    glVertex3f(0.0f, ponta_y + 0.2f, 0.0f);
    
    glVertex3f(0.05f, ponta_y, -0.05f);
    glVertex3f(-0.05f, ponta_y, -0.05f);
    glVertex3f(0.0f, ponta_y + 0.2f, 0.0f);
    
    glVertex3f(-0.05f, ponta_y, -0.05f);
    glVertex3f(-0.05f, ponta_y, 0.05f);
    glVertex3f(0.0f, ponta_y + 0.2f, 0.0f);
    glEnd();

    // Contornos da ponta
    glColor3f(0.8f, 0.7f, 0.6f);  // Cor mais escura para os contornos da ponta
    glBegin(GL_LINE_LOOP);
    glVertex3f(-0.05f, ponta_y, 0.05f);
    glVertex3f(0.05f, ponta_y, 0.05f);
    glVertex3f(0.0f, ponta_y + 0.2f, 0.0f);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex3f(0.05f, ponta_y, 0.05f);
    glVertex3f(0.05f, ponta_y, -0.05f);
    glVertex3f(0.0f, ponta_y + 0.2f, 0.0f);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex3f(0.05f, ponta_y, -0.05f);
    glVertex3f(-0.05f, ponta_y, -0.05f);
    glVertex3f(0.0f, ponta_y + 0.2f, 0.0f);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex3f(-0.05f, ponta_y, -0.05f);
    glVertex3f(-0.05f, ponta_y, 0.05f);
    glVertex3f(0.0f, ponta_y + 0.2f, 0.0f);
    glEnd();
}

void Obelisco(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Iniciar();
    
    // Configurações de profundidade
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);  // Garante que objetos mais próximos sejam renderizados corretamente
    
    // 1. Base circular
    DesenharBaseCircular();
    
    // 2. Corpo do obelisco (
    DesenharObeliscoComContornos();
    
    glFlush();
}

void Iniciar() {
    // Converter coordenadas polares para cartesianas
    a[0] = raio * cos(angulo);  // x = r * cos(θ)
    a[2] = raio * sin(angulo);  // z = r * sin(θ)
    a[1] = altura_cam;          // y = altura

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(a[0], a[1], a[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, largura/altura, 0.1, 100.0);
}

void Teclado(unsigned char key, int x, int y) {
    const float PASSO_ANGULAR = 0.1f;  // Velocidade de rotação
    const float PASSO_ALTURA = 0.2f;   // Velocidade de mudança de altura
    const float PASSO_ZOOM = 0.5f;     // Velocidade de zoom

    switch (key) {
        case 27:  // ESC - Sair
            exit(0);
            break;
        case 'a': // Girar câmera para esquerda
            angulo += PASSO_ANGULAR;
            break;
        case 'd': // Girar câmera para direita
            angulo -= PASSO_ANGULAR;
            break;
        case 'w': // Aproximar câmera (zoom in)
            if (raio > 2.0f) raio -= PASSO_ZOOM;
            break;
        case 's': // Afastar câmera (zoom out)
            if (raio < 20.0f) raio += PASSO_ZOOM;
            break;
        case 'q': // Aumentar altura da câmera
            if (altura_cam < 15.0f) altura_cam += PASSO_ALTURA;
            break;
        case 'e': // Diminuir altura da câmera
            if (altura_cam > 1.0f) altura_cam -= PASSO_ALTURA;
            break;
        case 'r': // Resetar posição da câmera
            raio = 8.0f;
            altura_cam = 4.0f;
            angulo = 0.0f;
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
   glutInit(&argc, argv);
   //glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH );
   glutInitWindowSize(largura, altura);
   glutInitWindowPosition(50, 50);
   glutCreateWindow("Obelisco de Washington");
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glutDisplayFunc(Obelisco);
   glutKeyboardFunc(Teclado);
   glutMainLoop();
   return 0;
}