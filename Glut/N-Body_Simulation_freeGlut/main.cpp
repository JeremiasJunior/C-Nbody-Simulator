#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


int p_amount = 5;
int p_spacement;
int count_this = 0;
int count_those = 0;

struct P_info {


    float *pos_x;
    float *pos_y;
    float *pos_z;

    int P_mass;

};
struct P_info *particle;

void particle_instantiate(int p_amount);

float pit_teorem3d (float *x, float *y, float *z);

void p_render();

void gravity_dyanamic ();

float g_module(float p_distance, float p1_mass, float p2_mass, float g_const);

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
}

void particle_instantiate(int p_amount){
    srand(time(NULL));

    int i;
    for(i = 0; i < p_amount; i++){


//    particle[i].pos_x = rand() % p_spacement;
  //  particle[i].pos_y = rand() % p_spacement;
    //particle[i].pos_z = rand() % p_spacement;


    }


}

float pit_teorem3d (float *x, float *y, float *z) {

    float xup2 = *x * *x;
    float yup2 = *y * *y;
    float zup2 = *z * *z;

    return sqrtf (xup2 + zup2 + yup2);


 }

float g_module(float p_distance, float p1_mass, float p2_mass, float g_const){

    float var_return;

    var_return = g_const * (p1_mass * p2_mass) / (p_distance * p_distance);

    return var_return;

}

void gravity_dyanamic (){
    /*








    */
    if(count_gambiarra > p_amount - 1){
        count_those = 0;

    }

    //gForceVectores[count] = (this.transform.position - particles[count].transform.position);
    particle[count_gambiarra] = (particle_gambiarra -)



}

void p_render(){


}
