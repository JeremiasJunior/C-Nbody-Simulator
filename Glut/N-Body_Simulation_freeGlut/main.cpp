#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


int p_amount = 5;
int p_spacement;

int this_p = 0;
int p_count = 0;

float g_const = 1;

union g_vector{

    float *gf_x;
    float *gf_y;
    float *gf_z;

};

struct P_info {


    float *pos_x;
    float *pos_y;
    float *pos_z;

    int P_mass;

};
struct P_info *particle;
union g_vector *gf_vector;
void particle_instantiate(int p_amount);

float *pit_teorem3d (float *x, float *y, float *z);

void p_render();

void gravity_dyanamic ();

float *g_module(float p_distance, float p1_mass, float p2_mass, float g_const);

void window_start();

int p_input(){

    puts("particle amount : \n");
    scanf("%d", &p_amount);

    if(p_amount <= 0)
        return 2;

    printf("particle spacement : \n");
    scanf("%d", &p_spacement);

}

int main(int argc, char **argv){

    p_input();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(640,480);
    glutCreateWindow("OpenGL");


    particle = (struct P_info*)malloc(p_amount * sizeof (struct P_info));
    gf_vector = (union g_vector*)malloc(p_amount * sizeof(union g_vector));

    if (!particle){
        printf ("** Erro: Memoria Insuficiente **");
          exit;
    }else{
          printf ("** Memoria Alocada com Sucesso **\n\n");
          printf("memory usage %d bytes", sizeof(particle) * p_amount);
      }
    particle_instantiate(p_amount);


    return 0;
    free(particle);
    free(gf_vector);
}

void particle_instantiate(int p_amount){
    srand(time(NULL));

    int i;
    for(i = 0; i < p_amount; i++){


    particle[i].pos_x = (float*)(rand() % p_spacement);
    particle[i].pos_y = (float*)(rand() % p_spacement);
    particle[i].pos_z = (float*)(rand() % p_spacement);
    }


}

float *pit_teorem3d (float *x, float *y, float *z) {

    float xup2 = *x * *x;
    float yup2 = *y * *y;
    float zup2 = *z * *z;
    float *var_return;
    *var_return = sqrtf (xup2 + zup2 + yup2);


    return var_return;


 }

float *g_module(float p_distance, float p1_mass, float p2_mass, float g_const){

    float *var_return;

    *var_return = g_const * (p1_mass * p2_mass) / (p_distance * p_distance);

    return var_return;

}

void gravity_dyanamic (){
    /*


    */

    if(p_count > p_amount - 1)
        p_count = 0;

    for (this_p = 0; this_p <= p_amount; this_p++){

    gf_vector[p_count].gf_x = (float *)(particle[this_p].pos_x - particle[p_count].pos_x);
    gf_vector[p_count].gf_y = (float *)(particle[this_p].pos_y - particle[p_count].pos_y);
    gf_vector[p_count].gf_z = (float *)(particle[this_p].pos_z - particle[p_count].pos_z);

    }



    if(this_p != p_count && pit_teorem3d(gf_vector->gf_x, gf_vector->gf_y, gf_vector->gf_z)!= 0){

    *particle[this_p].pos_x = -*gf_vector[p_count].gf_x * *g_module(*pit_teorem3d(gf_vector->gf_x, gf_vector->gf_y, gf_vector->gf_z), particle[this_p].P_mass, particle[p_count].P_mass, g_const);
    *particle[this_p].pos_y = -*gf_vector[p_count].gf_y * *g_module(*pit_teorem3d(gf_vector->gf_x, gf_vector->gf_y, gf_vector->gf_z), particle[this_p].P_mass, particle[p_count].P_mass, g_const);
    *particle[this_p].pos_z = -*gf_vector[p_count].gf_z * *g_module(*pit_teorem3d(gf_vector->gf_x, gf_vector->gf_y, gf_vector->gf_z), particle[this_p].P_mass, particle[p_count].P_mass, g_const);


    }


}

void p_render(){


}
