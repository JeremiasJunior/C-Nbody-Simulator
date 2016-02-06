#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GL/gl.h>


#include <stdlib.h>

size_t p_amount = 5;
int p_spacement;

struct P_info {


    float *pos_x;
    float *pos_y;
    float *pos_z;

    int P_mass;

};
struct P_info *particle;

void particle_instantiate(int p_amount);

float pit_teorem3d (float *x, float *y, float *z);

void gravity_dyanamic ();

int main(){

  //  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
//////////////////////////////////////////
    puts("particle amount : ");         //
    scanf("%d", &p_amount);             //
    if(p_amount <= 0)                   //
        return 2;                       //
    printf("particle spacement : ");    //
    scanf("%d", &p_spacement);          //
//////////////////////////////////////////


    particle = malloc(p_amount * sizeof(struct P_info));

    particle_instantiate(p_amount);

    printf("memory usage %d bytes", sizeof(particle) * p_amount);


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

float pit_teorem3d (float *x, float *y, float *z) {

    float xup2 = *x * *x;
    float yup2 = *y * *y;
    float zup2 = *z * *z;

    return sqrtf (xup2 + zup2 + yup2);


 }

void gravity_dyanamic (){

//fg = g.m1.m2/d.d



}

