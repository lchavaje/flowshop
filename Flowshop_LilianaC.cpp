/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define jobs 10
#define maq 5
#define pob 16
#define mitad 8
#define halfjobs 5

using namespace std;
void poblacion(int[pob][jobs]);
void tiempo_total(int[pob][jobs],int[maq][jobs],int[jobs][maq+1],int[pob]);
void seleccion(int[pob][jobs],int[pob],int[mitad][jobs]);
void cruza(int[mitad][jobs], int [pob][jobs]);
void mutacion(int[pob][jobs]);
void reemplazo(int[pob][jobs], int[pob][jobs]);
void campeon(int[pob][jobs],int[maq][jobs],int[jobs][maq+1],int[pob]);
int main()
{
    srand(time(NULL));
    
    int datos[jobs][maq+1]={{1,45,31,54,54,64},   
                        {2,44,7,52,66,57},         
                        {3,26,19,65,34,27},
                        {4,74,83,94,76,60},
                        {5,19,41,31,50,33},
                        {6,20,28,42,63,29},
                        {7,23,30,10,27,26},
                        {8,46,19,11,5,36},
                        {9,76,76,34,6,91},
                        {10,57,31,33,8,19}};          
                  
    int mpoblacion[pob][jobs]={{0}};
    int mtiempos[maq][jobs]={{0}};
    int cmax[pob]={0};
    int mseleccionados[mitad][jobs]={{0}};
    int mhijos[pob][jobs]={{0}};
    int w=0;
    poblacion(mpoblacion);
    while(w<50){
        tiempo_total(mpoblacion,mtiempos,datos,cmax);
        seleccion(mpoblacion,cmax,mseleccionados);
        cruza(mseleccionados,mhijos);
        mutacion(mhijos);
        reemplazo(mpoblacion, mhijos);
        cout<<" Nueva población número "<<w+1<< ":";  /* Impresión de la nueva población para la próxima */
        cout<<endl;
        for (int m=0;m<pob;m++){                /* iteración */
            cout<<endl;
            for(int n=0;n<jobs;n++){
                cout<<" "<<mhijos[m][n];
            }
        }
        cout<<endl;
        w++;
    }
    campeon(mhijos,mtiempos,datos,cmax);    /*Se determina la mejor secuencia respecto al tiempo */
    return 0;
}

//La funcion campeon determina cuál de las secuencias es más rápida
void campeon(int mhijos[pob][jobs],int mtiempos[maq][jobs],int datos[jobs][maq+1],int cmax[pob]){
    tiempo_total(mhijos,mtiempos,datos,cmax); /*calcula los tiempos de proceso para la última población*/
    int cmin=cmax[0];  
    int mfil=0;             
    for(int m=0;m<pob;m++){ /*compara el tiempo de cada secuencia y escoge el menor*/
        if(cmax[m]<cmin){
            cmin=cmax[m];
            mfil=m;
        }
    }
    cout<<endl;
    cout<<endl;
    cout<<"La mejor secuencia de trabajo es: ";
    cout<<endl;
    for(int m=0;m<jobs;m++){
        cout<<" "<<mhijos[mfil][m];
    }
}
    

// La función reemplazo cambia la población existente por la de hijos con mutaciones

void reemplazo(int mpoblacion[pob][jobs],int mhijos[pob][jobs]){
    for(int m=0;m<pob;m++){
        for(int n=0;n<jobs;n++){
            mpoblacion[m][n]=mhijos[m][n];
        }
    }
    /*cout<<" Nueva población: "<<" ";      Impresión de hijos después de mutación  
    for (int m=0;m<pob;m++){
        cout<<endl;
        for(int n=0;n<jobs;n++){
            cout<<" "<<mpoblacion[m][n];
        }
    }*/

}

//La función mutación intercambia posiciones aleatorias de un vector. El número de 
// vectores con posiciones intercambiadas es del 10% de la población.

void mutacion(int mhijos[pob][jobs]){
    int i,x,y,z;
    
    double de=ceil(pob*0.10);   /* se calcula el 10% de la población */
    int d=(int)de;              /* se cambia a número entero */
    cout<<endl;
    /*cout<<endl<<"El 10% de la población es "<<d<< " y es el número máximo de vectores mutados.";
    cout<<endl;
    cout<<endl;*/
    
    for(int m=0;m<d;m++){   /* Este ciclo es para que sólo se ejecute para el 10% */
        i=rand()%pob;   /*se seleccionan números aleatorios del 0 al 15 */
        x=rand()%jobs; /*se seleccionan números aleatorios del 0 al 15 */
        y=rand()%jobs;
        z=mhijos[i][x];
        mhijos[i][x]=mhijos[i][y];    /*se intercambian las posiciones */
        mhijos[i][y]=z;
    }
    /*cout<<" Hijos con mutaciones: "<<" ";      Impresión de hijos después de mutación  
    for (int m=0;m<pob;m++){
        cout<<endl;
        for(int n=0;n<jobs;n++){
            cout<<" "<<mhijos[m][n];
        }
    }
    cout<<endl;
    cout<<endl;*/
}

// La función cruza genera nuevas secuencias basadas en las contenidas en los seleccionados.
void cruza(int mseleccionados[mitad][jobs],int mhijos[pob][jobs]){
    int i,j,h,v;
    bool s;
    int aux[jobs];
    for(int m=0;m<pob;m++){
        for(int au=0;au<jobs;au++){
            aux[au]=au+1;   /*Se genera vector auxiliar con números del 1 al 10 */
        }
        i=rand()%mitad;     /* Se selecciona número aleatorio del 0 al 7 */
        j=rand()%mitad;     /* Se selecciona número aleatorio del 0 al 7 */
        for(int n=2;n<7;n++){
            mhijos[m][n]=mseleccionados[i][n]; /* El padre 1 es el de la fila i y se guardan */
            for(int k=0;k<jobs;k++){     /* las posiciones 2 a 6 */
                if(mhijos[m][n]==aux[k]){    /* los números utilizados para llenar las posiciones*/
                    aux[k]=0;               /* 2 a 6 se descartan del vector auxiliar y se */
                }                           /* igualan a cero */
            }
        }
        h=0;
        while(h<2){ /*Se rellenan las posiciones del 0 y 1 de cada vector */
            s=true;
            v=0;
            while(s){
                if(aux[mseleccionados[j][v]-1]!=0){ /* se verifica que las posiciones de aux */
                    mhijos[m][h]=mseleccionados[j][v]; /*sean números distintos a cero y rellena */
                    aux[mseleccionados[j][v]-1]=0;
                    h++;
                }
                v++;
                if (h==2){
                    s=false;
                }
            }
        }
        int f=7;    /* se rellenan las posiciones 7, 8 y 9 de cada vector */
        while(f<10){
            for(int n=0;n<jobs;n++){
                for(int k=0;k<jobs;k++){
                    if(mseleccionados[j][n]==aux[k]){
                        mhijos[m][f]=mseleccionados[j][n];
                        aux[k]=0;
                        f++;
                    }
                }

            }
        }
    }
    cout<<endl;
    cout<<endl;
    /*cout<<" Hijos: "<<" ";      Impresión de hijos después de cruza     
    for (int m=0;m<pob;m++){
        cout<<endl;
        for(int n=0;n<jobs;n++){
            cout<<" "<<mhijos[m][n];
        }
    }*/
}

// La función seleccion sirve para escoger vectores de la población original para cruza
void seleccion(int mpoblacion[pob][jobs],int cmax[pob],
int mseleccionados[mitad][jobs]){               /* Creación de la función selección */
    int r,j;
    int vecaux[pob]={0};    /* se crea un vector auxiliar con números del 0 al 15 */
    for(int v=0;v<pob;v++){
        vecaux[v]=v;
    }
    for(int k =0; k<pob;k++){
        r = rand()%pob;     /* se genera un número aleatorio */
        swap(vecaux[k],vecaux[r]); /* se reordena aleatoriamente el vector auxiliar */
    }
    /*cout<<endl;     Impresión del vector con orden aleatorio para competencia 
    cout<<endl<<"Vector auxiliar con orden aleatorio para competencia:";    
    cout<<endl;
    for(int w=0;w<pob;w++) {
            cout<<vecaux[w]<<" ";
        }*/
    j=0;
//en el siguiente ciclo se comparan los tiempos de dos secuencias aleatorias utilizando
// el vector auxiliar para no repetir secuencias. Se selecciona la secuencia que tome
// menos tiempo y se guarda en seleccionados.
    for(int m=0; m < mitad;m++){                    
        if (cmax[vecaux[j]] < cmax[vecaux[j+1]]){ 
            for(int n=0;n<jobs;n++){            
                mseleccionados[m][n] = mpoblacion[vecaux[j]][n];  
            }                                        
        }
        else{
            for(int n=0;n<jobs;n++){
                mseleccionados[m][n] = mpoblacion[vecaux[j+1]][n];
            }
        }
    j=j+2;    
    }
    cout<<endl;
    cout<<endl<<"Seleccionados:";   /* Impresión de matriz de seleccionados */
    cout<<endl;
    for(int m=0;m<mitad;m++){
        cout<<endl;
        for(int n=0;n<jobs;n++){
            cout<<mseleccionados[m][n]<<" ";
        }
    } 
}

//La función tiempo_total crea una matriz con vectores que indican el tiempo acumulado. //
// El tiempo acumulado total de cada secuencia se guarda en un vector. //

void tiempo_total(int mpoblacion[pob][jobs],int mtiempos[maq][jobs],int datos[jobs][maq+1],
int cmax[pob]){
    int reloj=0;
    int orden=0;    
    for(int p=0;p<pob;p++){    
        for(int m=0;m<jobs;m++){        /* ciclo que suma los tiempos para la máquina 1 */
            reloj=reloj+datos[mpoblacion[p][orden]-1][1]; /* según el orden de secuencia*/
            mtiempos[0][m]=reloj;   /*guarda los tiempos acumulados en la fila 1*/
            orden++;
        }
        reloj=0;
        orden=0;
//el siguiente ciclo va sumando los tiempos del primer trabajo de la secuencia para
// cada máquina. Cuando el primer trabajo de la secuencia termina en la máquina 1,
// inmediatamente continúa en la 2 sin tener que esperar. El mismo proceso es para todas
// las máquinas.
        for(int s=1;s<maq;s++) {
            mtiempos[s][0]=mtiempos[s-1][0]+datos[mpoblacion[p][0]-1][s+1];
        }
// Para el resto de las columnas, se debe de tomar en cuenta que el trabajo se haya
// terminado y que la máquina esté libre. Para esto se debe de comparar el tiempo de la
// celda de arriba(tiempo cuando termina el trabajo)con la celda de la izquierda para
// verificar que la máquina esté disponible. El que tenga el tiempo mayor es en el que
// puede empezar el trabajo.
        for(int m=1;m<maq;m++) {
            for(int n=1;n<jobs;n++) {
                if (mtiempos[m-1][n]>mtiempos[m][n-1]) {
                    mtiempos[m][n]=mtiempos[m-1][n]+datos[mpoblacion[p][n]-1][m+1];
                }
                else{
                    mtiempos[m][n]=mtiempos[m][n-1]+datos[mpoblacion[p][n]-1][m+1];
                }
            }
        }
        /*cout<<endl; Impresión de la matriz de tiempos
        cout<<endl<<"Tiempos totales para trabajo terminado:"; 
        cout<<endl;
        for(int m=0;m<maq;m++) {
            cout<<endl;
            for(int n=0;n<jobs;n++) {
                cout<<mtiempos[m][n]<<" ";
            }
        }*/
       
        cmax[p]=mtiempos[maq-1][jobs-1]; /*el tiempo total de las secuencias se guarda */
    }                                   /* en un vector, para evaluar aptitud*/
    cout<<endl;
    cout<<endl<<"Tiempos totales de procesamiento:";  /*Impresión del tiempo total de */  
    cout<<endl;                                 /*cada secuencia de la población */
    for(int m=0;m<pob;m++) {
            cout<<cmax[m]<<" ";
        }
}

//La función poblacion crea una matriz con vectores que indican el orden en el cual se //
// realiza el trabajo en cada máquina //
void poblacion(int mpoblacion[pob][jobs]){
    int vecaux[jobs]={0};
    for(int o=0;o<pob;o++){       /* Este ciclo genera un vector auxiliar con valores*/
        for(int vec=1;vec<=jobs;vec++){ /* del 1 al 10 */
            vecaux[vec-1]=vec;
        }
        for(int pos=0;pos<jobs;pos++){
            bool senal=true;
            while(senal){    
                int p=rand()%10;   /* se genera un número aleatorio del 0 al 9 */
                if (vecaux[p]!=100000){ /* se guarda en p si no se ha usado previamente */
                    mpoblacion[o][pos]=vecaux[p]; /* se guarda el valor de la posición p*/
                    vecaux[p]=100000;   /* este comando se utiliza para no volver a usar*/
                    senal=false;        /* en la matriz y se descarta */
                }
            }
        }
    }
    cout<<endl<<"Población original:";      /* Impresión de la población inicial  */
    cout<<endl;
    for(int m=0;m<pob;m++){
        cout<<endl;
        for(int n=0;n<jobs;n++) {
            cout<<mpoblacion[m][n]<<" ";
        }
    }
    cout<<endl;
}
























