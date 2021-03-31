#include<omp.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main(){
    long i;
    long acertos=0;
    long n=100000000;
    #pragma omp parallel for reduction(+:acertos) num_threads(16)
    for(i=0;i<n;i++){
        unsigned int d=(int)i;
        double x =(double) rand_r(&d)/RAND_MAX; 
        double y = (double) rand_r(&d)/RAND_MAX;
        double z =(double) x*x+y*y;
        if(z<1.0){
            acertos++;
        }
    }    
    double pi=(double)(4.0*acertos/n);
    printf("VALOR PI: %lf",pi);
    return 0;
}
