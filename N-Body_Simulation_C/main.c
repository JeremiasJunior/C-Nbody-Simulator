#include <stdio.h>
#include <stdlib.h>
//#include <CL/cl.h>
#include <time.h>


size_t p_amount = 5;





struct P_info {


    float *pos_x;
    float *pos_y;
    float *pos_z;

    int P_mass;

};
struct P_info *particle;

//void particle_instantiate(int p_amount, struct P_info p[]);

//float pitTeorem3D (float *x, float *y, float *z);

//struct P_info* particle = malloc(p_amount * sizeof(P_info));

int main(){


    p_amount = 5;

    particle = malloc(p_amount * sizeof(struct P_info));

    particle_instantiate(p_amount);

    int i;
    for(i = 0; i < p_amount; i++){

    printf("p %i\nx = %d\ny = %d\nz = %d\n\n", i, particle[i].pos_x
                                                , particle[i].pos_y
                                                , particle[i].pos_z);
    }

    return 0;

}

void particle_instantiate(int p_amount){
   // srand(time(NULL));
   // struct P_info par_struct[p_amount];
    int i;
    for(i = 0; i < p_amount; i++){


    particle[i].pos_x = 45;
    particle[i].pos_y = 16;
    particle[i].pos_z = 5;


    }


}

/*float pitTeorem3D (float *x, float *y, float *z) {

    float *xup2 = *toPythagoream.x * *toPythagoream.x;
    float *yup2 = *toPythagoream.y * *toPythagoream.y;
    float *zup2 = *toPythagoream.z * *toPythagoream.z;

    return sqrtf (xup2 + zup2 + yup2);


 }*/

