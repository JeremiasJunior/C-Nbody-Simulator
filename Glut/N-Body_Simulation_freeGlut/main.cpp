#include <GL/glut.h>
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


int p_amount = 5;
int p_spacement;
GLsizei x = 400;
GLsizei y = 400;

int this_p = 0;
int p_count = 0;

float g_const = 1000;

union g_vector{

    GLdouble gf_x;
    GLdouble gf_y;
    GLdouble gf_z;

};
struct P_info {


    GLdouble pos_x;
    GLdouble pos_y;
    GLdouble pos_z;

    int P_mass = 1;

};
struct P_info *particle;
union g_vector *gf_vector;
void particle_instantiate(int p_amount);

float pit_teorem3d (GLdouble x, GLdouble y, GLdouble z);

void p_render();

void gravity_dyanamic ();

float g_module(float p_distance, float p1_mass, float p2_mass, float g_const);

int p_input(){

    puts("particle amount : \n");
    scanf("%d", &p_amount);

    if(p_amount <= 0)
        return 2;

    printf("particle spacement : \n");
    scanf("%d", &p_spacement);

}
void reshape(int width,int height) {

double w2h = (height>0) ? (double)width/height : 1;
glViewport(0,0, width,height);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();


   /* orthogonal projection */
   glOrtho(-p_spacement,p_spacement,-p_spacement,p_spacement, -p_spacement,p_spacement);


   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
 }

void draw_axes(){

    /*  Length of axes */
    double len = 2.0;
    glColor3f(1.0,1.0,1.0);

    glBegin(GL_POINTS);
    for (int i = 0; i < p_amount; i++)
    glVertex3d(particle[i].pos_x,particle[i].pos_y,particle[i].pos_z);

    glEnd();

}
void p_render(void){

 glClear(GL_COLOR_BUFFER_BIT);
 glLoadIdentity();

 glRotated(0,1,0,0);
 glRotated(0,0,1,0);

 draw_axes();

 glFlush();
 glutSwapBuffers();
gravity_dyanamic();
}

int main(int argc, char **argv){

    p_input();



    particle = (struct P_info*)malloc(p_amount * sizeof (struct P_info));
    gf_vector = (union g_vector*)malloc(p_amount * sizeof(union g_vector));

    if (!particle){
        printf ("** Erro: Memoria Insuficiente **");
          exit;
    }else{
          printf ("** Memoria Alocada com Sucesso **\n\n");
          printf("memory usage %d bytes\n", sizeof(particle) * p_amount);
      }
    particle_instantiate(p_amount);
    puts ("iniciando glut\n");

    /*glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000,600);
    glutInitWindowPosition(GLUT_SCREEN_HEIGHT/2, GLUT_SCREEN_WIDTH/2);
    glutCreateWindow("Opengl");

    glutDisplayFunc(p_render);
    glutReshapeFunc(reshape);
    glClearColor(0,0,0,1);
    glutMainLoop();*/

    this_p = 0;
    while(true)
        gravity_dyanamic();

    free(particle);
    free(gf_vector);
    return 0;


}

void particle_instantiate(int p_amount){
    srand(time(NULL));

    int i;
    for(i = 0; i < p_amount; i++){


    particle[i].pos_x = rand() % p_spacement;
    particle[i].pos_y = rand() % p_spacement;
    particle[i].pos_z = rand() % p_spacement;
    }


}

float pit_teorem3d (GLdouble x, GLdouble y, GLdouble z) {

    GLdouble xup2 = x * x;
    GLdouble yup2 = y * y;
    GLdouble zup2 = z * z;
    //float *var_return;
    return sqrtf (xup2 + zup2 + yup2);

 }

float g_module(float p_distance, float p1_mass, float p2_mass, float g_const){

    float var_return;

    var_return = g_const * (p1_mass * p2_mass) / (p_distance * p_distance);

    return var_return;

}

void gravity_dyanamic (){

    if(p_count > p_amount - 1)
        p_count = 0;
    if(this_p > p_amount -1)
        this_p = 0;

    for (this_p = 0; this_p <= p_amount; this_p++){ // traça uma linha entre as duas particulas

    gf_vector[p_count].gf_x = particle[this_p].pos_x - particle[p_count].pos_x;
    gf_vector[p_count].gf_y = particle[this_p].pos_y - particle[p_count].pos_y;
    gf_vector[p_count].gf_z = particle[this_p].pos_z - particle[p_count].pos_z;

    }


    if(this_p != p_count && pit_teorem3d(gf_vector->gf_x, gf_vector->gf_y, gf_vector->gf_z)!= 0){ // adiciona um modulo baseado na fg=g.m1.m2/d^2

    particle[this_p].pos_x += -gf_vector[p_count].gf_x * g_module(pit_teorem3d(gf_vector->gf_x, gf_vector->gf_y, gf_vector->gf_z), particle[this_p].P_mass, particle[p_count].P_mass, g_const);
    particle[this_p].pos_y += -gf_vector[p_count].gf_y * g_module(pit_teorem3d(gf_vector->gf_x, gf_vector->gf_y, gf_vector->gf_z), particle[this_p].P_mass, particle[p_count].P_mass, g_const);
    particle[this_p].pos_z += -gf_vector[p_count].gf_z * g_module(pit_teorem3d(gf_vector->gf_x, gf_vector->gf_y, gf_vector->gf_z), particle[this_p].P_mass, particle[p_count].P_mass, g_const);

    }
    this_p++;
    printf("\n***particle %d\n*x = %d\n*y = %d\n*z = %d\n",this_p, particle[this_p].pos_x,particle[this_p].pos_y,particle[this_p].pos_z);
}
