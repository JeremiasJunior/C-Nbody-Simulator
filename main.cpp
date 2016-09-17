// Created by : Jeremias Junior //

#include <iostream>
#include <GLUT/glut.h> //MAC OS
#include <ctime>
#include <cmath>

float screen_pos[3] = {-8,-15,30};
float screen_rot = 0;

#define B_AMOUNT 300     // Amount of bodys.
#define DISTANCE 25      // Distance Between Bodys.
#define G_CONST 6.674E-11// Gravity Constant.
double B_CONST = 1E7;

bool can_simul = false;

typedef struct vector3{
    
    double x, y, z;
    double Module(){return sqrt((x*x) + (y*y) + (z*z));}
    
}vector3;

typedef struct body_struct{
    
    vector3 pos;
    vector3 force;
    vector3 sent;
    
    double mass = 1;
    
}body_struct;

body_struct body[B_AMOUNT];

double g_module(double massI, double massJ, double distance, double g_const = G_CONST, double b_const = B_CONST){
    
    return b_const * (g_const * (massI * massJ) / ((distance * distance + 0.2f)));
}
void gravity_dynamic(body_struct *b, unsigned int b_amount = B_AMOUNT){
    
    for(int i = 0; i < b_amount; i++){
        
        for(int j = 0; j < b_amount; j++){
            
            if(i == j) j++;
            
            b[i].sent.x = b[j].pos.x - b[i].pos.x;
            b[i].sent.y = b[j].pos.y - b[i].pos.y;
            b[i].sent.z = b[j].pos.z - b[i].pos.z;

            b[i].force.x += g_module(b[i].mass, b[j].mass, b[i].sent.Module()) * (b[i].sent.x);
            b[i].force.y += g_module(b[i].mass, b[j].mass, b[i].sent.Module()) * (b[i].sent.y);
            b[i].force.z += g_module(b[i].mass, b[j].mass, b[i].sent.Module()) * (b[i].sent.z);
        }
        
        b[i].pos.x += b[i].force.x;
        b[i].pos.y += b[i].force.y;
        b[i].pos.z += b[i].force.z;

        
    }
    
    
}


void DrawCube( GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength);

void changeSize(int w, int h) {

    if (h == 0)
        h = 1;
    
    float ratio =  w * 1.0 / h;
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(60, ratio, 0.01f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);

    
}
void keyboard(unsigned char key, int x, int y){
    
    switch (key){
        
        case 'w':
            screen_pos[1] -= 5;
        break;
        case 's':
            screen_pos[1] += 5;
        break;
        case 'a':
            screen_pos[0] -= 5;
        break;
        case 'd':
            screen_pos[0] += 5;
        break;
        case 'q':
            screen_pos[2] -= 5;
        break;
        case 'e':
            screen_pos[2] += 5;
        break;
        case 'p':
            if(can_simul)
            can_simul = false;
            else
            can_simul = true;
        break;
        case 'z':
            screen_rot -= 1;
        break;
        case 'x':
            screen_rot += 1;
        break;
        case 'b':
            B_CONST -= 0.005;
        break;
        case 'B':
            B_CONST += 0.005;
        break;

    }
}
int t = 0;
void renderScene(void) {
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0f, 0.0f, -10, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    
    glTranslated(screen_pos[0], screen_pos[1], screen_pos[2]);

    glRotatef(screen_rot, 0, 0, 0);
    
    glColor3f(1, 0, 0);

    for(int i = 0; i < B_AMOUNT; i++){
        DrawCube(body[i].pos.x, body[i].pos.y, body[i].pos.z, 0.2f);
    }
    if(can_simul){
        gravity_dynamic(body);
        t++;
    }
    
    printf("t = %i\n", t);

    glutSwapBuffers();
}
int main(int argc, char** argv) {

    for (int i = 0; i < B_AMOUNT; i++){
        
        if(i < B_AMOUNT/2){
            body[i].pos.x = rand() % DISTANCE;
            body[i].pos.y = rand() % DISTANCE;
            body[i].pos.z = rand() % DISTANCE;
        }
        else{
            body[i].pos.x = rand() % DISTANCE + 90;
            body[i].pos.y = rand() % DISTANCE;
            body[i].pos.z = rand() % DISTANCE;
        }
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(GLUT_SCREEN_WIDTH/2 ,GLUT_SCREEN_HEIGHT/2);
    glutInitWindowSize(1000  ,500);
    glutCreateWindow("n-body simulation");
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);
    glutKeyboardFunc(keyboard);
    
    glutMainLoop();
    return 0;
}
void DrawCube( GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength )
{
    GLfloat halfSideLength = edgeLength * 1;

    GLfloat vertices[] =
    {
        // front face
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top right
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom right
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom left
        
        // back face
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top left
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom left
        
        // left face
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom left
        
        // right face
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom left
        
        // top face
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // bottom right
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // bottom left
        
        // top face
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // top left
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // top right
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength  // bottom left
    };
    
    glPolygonMode( GL_FRONT_AND_BACK, GL_QUADS);
    glColor3f((rand() % 10) / 10, 1, 0);
    glEnableClientState( GL_VERTEX_ARRAY );
    glVertexPointer( 3, GL_FLOAT, 0, vertices );
    glDrawArrays( GL_QUADS, 0, 24 );
    
    glDisableClientState( GL_VERTEX_ARRAY );
}