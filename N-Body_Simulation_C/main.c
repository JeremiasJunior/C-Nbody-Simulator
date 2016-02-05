#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>
#include <time.h>


int p_amount = 5;





struct P_info {


    float *pos_x;
    float *pos_y;
    float *pos_z;

    int P_mass;

};

void particle_instantiate(int p_amount, struct P_info p[]);

float pitTeorem3D (float *x, float *y, float *z);

struct P_info particle[];
particle = malloc(sizeof(particle)*p_amount);

int main(){


   // struct P_info particle[p_amount];

    int i;

    particle_instantiate(p_amount, particle);
   // particle[0].pos_x = 50;
   // particle[1].pos_y = 35;
 //   particle[2].pos_z = 15;



    for(i = 0; i < p_amount; i++){

    printf("p %i\nx = %d\ny = %d\nz = %d\n\n", i, particle[i].pos_x
                                                , particle[i].pos_y
                                                , particle[i].pos_z);

    }

}

void particle_instantiate(int p_amount, struct P_info p[]){
   // srand(time(NULL));
   // struct P_info par_struct[p_amount];
    int i;
    for(i = 0; i < p_amount; i++){


    [i].pos_x = 45;
    par_struct[i].pos_y = 16;
    par_struct[i].pos_z = 5;


    }


}

/*float pitTeorem3D (float *x, float *y, float *z) {

    float *xup2 = *toPythagoream.x * *toPythagoream.x;
    float *yup2 = *toPythagoream.y * *toPythagoream.y;
    float *zup2 = *toPythagoream.z * *toPythagoream.z;

    return sqrtf (xup2 + zup2 + yup2);


 }*/

