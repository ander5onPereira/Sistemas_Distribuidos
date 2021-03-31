#include<omp.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main(){
    long i;
    long acertos=0;
    long n=100000000;
    #pragma omp parallel 
    {
    double x,y,z;
    unsigned int d=omp_get_thread_num();
    #pragma omp for reduction(+:acertos)
    for(i=0;i<n;i++){
        x =(double) rand_r(&d)/RAND_MAX; 
        y = (double) rand_r(&d)/RAND_MAX;
        z =(double) x*x+y*y;
        if(z<1.0){
            acertos++;
        }
    }    
    }
    double pi=(double)(4.0*acertos/n);
    printf("VALOR PI: %lf",pi);
    return 0;
}
