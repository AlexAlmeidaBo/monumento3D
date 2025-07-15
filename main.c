#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#define M_PI 3.14159265358979323846

int largura=500, altura=500;

// Protótipos das funções
void Obelisco(void);
void Iniciar(void);
void DesenharCirculo(float raio, float y, int segmentos);
void DesenharBaseCircular(void);
void DesenharObeliscoComContornos(void);
//void DesenharCenarioFundo(void);
void Teclado(unsigned char key, int x, int y);
void DesenharEstruturaBase(void);
void DesenharCaminhos(void);
void drawEllipticalGrassAndPaths(void);

// Variáveis para controle da câmera em coordenadas polares
float raio = 8.0f;        // Distância da câmera ao centro
float altura_cam = 4.0f;  // Altura da câmera
float angulo = 0.0f;      // Ângulo de rotação em radianos
float a[3] = {0.0f, 0.0f, 0.0f};  // Coordenadas cartesianas da câmera

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
    // Base circular cinza sólida
    glColor3f(0.75f, 0.75f, 0.75f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, 0.0f, 0.0f);
    for(int i = 0; i <= 360; i += 2) {
        float angle = i * M_PI / 180.0f;
        glVertex3f(cos(angle) * 2.0f, 0.005f, sin(angle) * 2.0f);
    }
    glEnd();

    // Listras brancas curvas nos quadrantes (seguindo o círculo)
    glColor3f(1.0f, 1.0f, 1.0f);
    float raio_interno = 0.0f;
    float raio_externo = 2.0f;
    float angulos_centrais[] = {0, 90, 180, 270}; // Norte, Leste, Sul, Oeste
    float abertura = 15.0f; // graus

    for (int i = 0; i < 4; i++) {
        float angulo_central = angulos_centrais[i];
        float inicio = angulo_central - abertura / 2.0f;
        float fim = angulo_central + abertura / 2.0f;

         glBegin(GL_TRIANGLE_STRIP);
        for (float ang = inicio; ang <= fim; ang += 1.0f) {
            float rad = ang * M_PI / 180.0f;
            glVertex3f(cos(rad) * raio_interno, 0.01f, sin(rad) * raio_interno);
            glVertex3f(cos(rad) * raio_externo, 0.01f, sin(rad) * raio_externo);
        }
        glEnd();
    }

    // Círculo de acabamento
    glColor3f(0.65f, 0.65f, 0.65f);
    DesenharCirculo(2.0f, 0.02f, 100);

    
}

void DesenharObeliscoComContornos() {
    // Corpo do obelisco com dimensões aumentadas
    float corpo_y = 0.01f;
    float altura_corpo = 3.6f;  // Dobro da altura anterior
    float base_largura = 0.4f;  // Dobro da largura anterior
    float topo_largura = 0.1f;  // Dobro da largura do topo
    
    // Primeiro desenha as faces preenchidas
    glBegin(GL_QUADS);
    glColor3f(0.9f, 0.9f, 0.9f);
    
    // Face frontal
    glVertex3f(-base_largura, corpo_y, base_largura);
    glVertex3f(base_largura, corpo_y, base_largura);
    glVertex3f(topo_largura, corpo_y + altura_corpo, topo_largura);
    glVertex3f(-topo_largura, corpo_y + altura_corpo, topo_largura);
    
    // Face direita
    glVertex3f(base_largura, corpo_y, base_largura);
    glVertex3f(base_largura, corpo_y, -base_largura);
    glVertex3f(topo_largura, corpo_y + altura_corpo, -topo_largura);
    glVertex3f(topo_largura, corpo_y + altura_corpo, topo_largura);
    
    // Face traseira
    glVertex3f(base_largura, corpo_y, -base_largura);
    glVertex3f(-base_largura, corpo_y, -base_largura);
    glVertex3f(-topo_largura, corpo_y + altura_corpo, -topo_largura);
    glVertex3f(topo_largura, corpo_y + altura_corpo, -topo_largura);
    
    // Face esquerda
    glVertex3f(-base_largura, corpo_y, -base_largura);
    glVertex3f(-base_largura, corpo_y, base_largura);
    glVertex3f(-topo_largura, corpo_y + altura_corpo, topo_largura);
    glVertex3f(-topo_largura, corpo_y + altura_corpo, -topo_largura);
    glEnd();

    // Contornos do corpo
    glLineWidth(2.0f);
    glColor3f(0.7f, 0.7f, 0.7f);
    
    // Desenha os contornos das faces
    glBegin(GL_LINE_LOOP);
    glVertex3f(-base_largura, corpo_y, base_largura);
    glVertex3f(base_largura, corpo_y, base_largura);
    glVertex3f(topo_largura, corpo_y + altura_corpo, topo_largura);
    glVertex3f(-topo_largura, corpo_y + altura_corpo, topo_largura);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex3f(base_largura, corpo_y, base_largura);
    glVertex3f(base_largura, corpo_y, -base_largura);
    glVertex3f(topo_largura, corpo_y + altura_corpo, -topo_largura);
    glVertex3f(topo_largura, corpo_y + altura_corpo, topo_largura);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex3f(base_largura, corpo_y, -base_largura);
    glVertex3f(-base_largura, corpo_y, -base_largura);
    glVertex3f(-topo_largura, corpo_y + altura_corpo, -topo_largura);
    glVertex3f(topo_largura, corpo_y + altura_corpo, -topo_largura);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex3f(-base_largura, corpo_y, -base_largura);
    glVertex3f(-base_largura, corpo_y, base_largura);
    glVertex3f(-topo_largura, corpo_y + altura_corpo, topo_largura);
    glVertex3f(-topo_largura, corpo_y + altura_corpo, -topo_largura);
    glEnd();

    // Ponta do obelisco (também aumentada)
    float ponta_y = corpo_y + altura_corpo;
    float altura_ponta = 0.4f;  // Dobro da altura da ponta
    
    // Faces da ponta
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.9f, 0.8f);
    
    // Face frontal da ponta
    glVertex3f(-topo_largura, ponta_y, topo_largura);
    glVertex3f(topo_largura, ponta_y, topo_largura);
    glVertex3f(0.0f, ponta_y + altura_ponta, 0.0f);
    
    // Face direita da ponta
    glVertex3f(topo_largura, ponta_y, topo_largura);
    glVertex3f(topo_largura, ponta_y, -topo_largura);
    glVertex3f(0.0f, ponta_y + altura_ponta, 0.0f);
    
    // Face traseira da ponta
    glVertex3f(topo_largura, ponta_y, -topo_largura);
    glVertex3f(-topo_largura, ponta_y, -topo_largura);
    glVertex3f(0.0f, ponta_y + altura_ponta, 0.0f);
    
    // Face esquerda da ponta
    glVertex3f(-topo_largura, ponta_y, -topo_largura);
    glVertex3f(-topo_largura, ponta_y, topo_largura);
    glVertex3f(0.0f, ponta_y + altura_ponta, 0.0f);
    glEnd();
}


void DesenharEstruturaBase() {
    // Estrutura retangular branca com dimensões menores
    glColor3f(0.95f, 0.95f, 0.95f);
    float largura = 0.6f;      // Reduzido de 0.8f para 0.6f
    float profundidade = 0.4f; // Reduzido de 0.6f para 0.4f
    float altura = 0.6f;      // Reduzido de 0.8f para 0.6f
    
    // Posicionar encostado no obelisco
    float pos_x = 0.4f;  // Alinhado com a face direita do obelisco
    
    // Frente
    glBegin(GL_QUADS);
    glVertex3f(pos_x, 0.0f, profundidade/2);
    glVertex3f(pos_x + largura, 0.0f, profundidade/2);
    glVertex3f(pos_x + largura, altura, profundidade/2);
    glVertex3f(pos_x, altura, profundidade/2);
    
    // Direita
    glVertex3f(pos_x + largura, 0.0f, profundidade/2);
    glVertex3f(pos_x + largura, 0.0f, -profundidade/2);
    glVertex3f(pos_x + largura, altura, -profundidade/2);
    glVertex3f(pos_x + largura, altura, profundidade/2);
    
    // Trás
    glVertex3f(pos_x + largura, 0.0f, -profundidade/2);
    glVertex3f(pos_x, 0.0f, -profundidade/2);
    glVertex3f(pos_x, altura, -profundidade/2);
    glVertex3f(pos_x + largura, altura, -profundidade/2);
    
    // Esquerda (conectada ao obelisco)
    glVertex3f(pos_x, 0.0f, -profundidade/2);
    glVertex3f(pos_x, 0.0f, profundidade/2);
    glVertex3f(pos_x, altura, profundidade/2);
    glVertex3f(pos_x, altura, -profundidade/2);
    
    // Topo
    glVertex3f(pos_x, altura, profundidade/2);
    glVertex3f(pos_x + largura, altura, profundidade/2);
    glVertex3f(pos_x + largura, altura, -profundidade/2);
    glVertex3f(pos_x, altura, -profundidade/2);
    glEnd();
    
    // Janelas pretas ajustadas para a nova escala
    glColor3f(0.1f, 0.1f, 0.1f);
    float janela_y = 0.2f;        // Ajustado para a nova altura
    float janela_altura = 0.25f;  // Reduzido para manter proporção
    float janela_largura = 0.15f; // Reduzido para manter proporção
    
    // Janelas frontais
    for(int i = 0; i < 2; i++) {
    float x = pos_x + 0.1f + (i * 0.25f);  // ajuste de posição e espaçamento
    glBegin(GL_QUADS);
    glVertex3f(x, janela_y, profundidade/2 + 0.001f);
    glVertex3f(x + janela_largura, janela_y, profundidade/2 + 0.001f);
    glVertex3f(x + janela_largura, janela_y + janela_altura, profundidade/2 + 0.001f);
    glVertex3f(x, janela_y + janela_altura, profundidade/2 + 0.001f);
    glEnd();
    }
    
    // Porta na face direita (x = 1.0f), centralizada em Z
    glColor3f(0.1f, 0.1f, 0.1f);  // Cor preta

    float porta_largura = 0.2f;
    float porta_altura = 0.4f;
    float x_porta = pos_x + largura + 0.001f;  
    float z_porta = -porta_largura / 2.0f;  // centralizada em Z

    glBegin(GL_QUADS);
    glVertex3f(x_porta, 0.0f, z_porta);
    glVertex3f(x_porta, 0.0f, z_porta + porta_largura);
    glVertex3f(x_porta, porta_altura, z_porta + porta_largura);
    glVertex3f(x_porta, porta_altura, z_porta);
    glEnd();

}

void DesenharCaminhos() {
    glColor3f(0.8f, 0.8f, 0.8f);
    
    // Caminhos circulares
    float raios[] = {3.0f, 6.0f};
    for(int i = 0; i < 2; i++) {
        glBegin(GL_LINE_STRIP);
        for(int j = 0; j <= 360; j += 5) {
            float angle = j * M_PI / 180.0f;
            glVertex3f(cos(angle) * raios[i], -0.009f, sin(angle) * raios[i]);
        }
        glEnd();
    }
    
    // Caminhos diagonais
    glBegin(GL_LINES);
    glVertex3f(-6.0f, -0.009f, 6.0f);
    glVertex3f(6.0f, -0.009f, -6.0f);
    
    glVertex3f(-6.0f, -0.009f, -6.0f);
    glVertex3f(6.0f, -0.009f, 6.0f);
    glEnd();
}

void drawEllipticalGrassAndPaths() {
    // Grama elíptica
    glColor3f(0.2f, 0.5f, 0.2f); // Verde mais escuro
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, 0.0f, 0.0f);
    for(int i = 0; i <= 360; i += 2) {
        float angle = i * M_PI / 180.0f;
        float x = 8.0f * cos(angle);  // Raio maior
        float z = 6.0f * sin(angle);  // Raio menor
        glVertex3f(x, -0.01f, z);
    }
    glEnd();

    // Trilhas elípticas sobrepostas e rotacionadas
    float trilhaLargura = 0.55f;
    float a = 7.2f; // semi-eixo maior
    float b = 5.4f; // semi-eixo menor
    float angulos[3] = {0.0f, 120.0f, 240.0f};
    glColor3f(0.92f, 0.91f, 0.85f); // Cor clara para trilha
    for(int t = 0; t < 3; t++) {
        float theta = angulos[t] * M_PI / 180.0f;
        glPushMatrix();
        glRotatef(angulos[t], 0, 1, 0);
        glBegin(GL_QUAD_STRIP);
        for(int i = 0; i <= 360; i += 2) {
            float angle = i * M_PI / 180.0f;
            float x1 = (a - trilhaLargura/2) * cos(angle);
            float z1 = (b - trilhaLargura/2) * sin(angle);
            float x2 = (a + trilhaLargura/2) * cos(angle);
            float z2 = (b + trilhaLargura/2) * sin(angle);
            glVertex3f(x1, 0.01f, z1);
            glVertex3f(x2, 0.01f, z2);
        }
        glEnd();
        glPopMatrix();
    }
}

void Obelisco(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    Iniciar();
    //DesenharCenarioFundo();
    drawEllipticalGrassAndPaths();
    DesenharBaseCircular();
    DesenharEstruturaBase();
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
    const float RAIO_MIN = 4.0f;       // Novo limite mínimo
    const float RAIO_MAX = 10.0f;      // Novo limite máximo

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
            if (raio > RAIO_MIN) raio -= PASSO_ZOOM;
            break;
        case 's': // Afastar câmera (zoom out)
            if (raio < RAIO_MAX) raio += PASSO_ZOOM;
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

float converterGrausParaRadianos(float graus) {
    return graus * M_PI / 180.0f;
}

int main(int argc, char** argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(largura, altura);
   glutInitWindowPosition(50, 50);
   glutCreateWindow("Obelisco de Washington");
   //glClearColor(0.4f, 0.7f, 1.0f, 1.0f);  // Cor de fundo azul clara
   glutDisplayFunc(Obelisco);
   glutKeyboardFunc(Teclado);
   glutMainLoop();
   return 0;
}