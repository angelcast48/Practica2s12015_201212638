
#include <stdio.h>
#include <stdlib.h>
# include <time.h>
#include <sys/time.h>
#include <math.h>

/*
*
*/
struct nodoArbol {
int dato;
int fe;
struct nodoArbol *Izq, *Der;
};
typedef struct nodoArbol NodoArbol; 
NodoArbol* crearNodo(int id) {
NodoArbol * aux;
aux = (NodoArbol*) malloc(sizeof (NodoArbol));
aux -> dato = id;
aux -> Izq = aux -> Der = NULL;
aux -> fe = 0;
return aux;
}
void rotacionIzqIzq(NodoArbol** n, NodoArbol* n1) {
(*n) -> Izq = n1 -> Der;
n1 -> Der = (*n);
if (n1 -> fe == -1) {
(*n) -> fe = 0;
n1 -> fe = 0;
} else {
(*n) -> fe = -1;
n1 -> fe = 1;
}
(*n) = n1;
}

void rotacionDerDer(NodoArbol** n, NodoArbol * n1) {
(*n) -> Der = n1 -> Izq;
n1 -> Izq = (*n);
if (n1 -> fe == +1) {
(*n) -> fe = 0;
n1 -> fe = 0;
} else {
(*n) -> fe = +1;
n1 -> fe = -1;
}
(*n) = n1;
}
void rotacionIzqDer(NodoArbol** n, NodoArbol * n1) {
NodoArbol* n2;
n2 = n1 -> Der;
(*n) -> Izq = n2 -> Der;
n2 -> Der = *n;
n1 -> Der = n2 -> Izq;
n2 -> Izq = n1;
if (n2 -> fe == +1) {
n1 -> fe = -1;
} else {
n1 -> fe = 0;
}
if (n2 -> fe == -1) {
(*n) -> fe = 1;
} else {
(*n) -> fe = 0;
}
n2 -> fe = 0;
(*n) = n2;
}

void rotacionDerIzq(NodoArbol** n, NodoArbol * n1) {
NodoArbol* n2;
n2 = n1 -> Izq;
(*n) -> Der = n2 -> Izq;
n2 -> Izq = *n;
n1 -> Izq = n2 -> Der;
n2 -> Der = n1;
if (n2 -> fe == +1) {
(*n) -> fe = -1;
} else {
(*n) -> fe = 0;
}
if (n2 -> fe == -1) {
n1 -> fe = 1;
} else {
n1 -> fe = 0;
}
n2 -> fe = 0;
(*n) = n2;
}
void insertar(NodoArbol** raiz, int digi, int* h) {
NodoArbol* n1;
if (!(*raiz)) {
*raiz = crearNodo(digi);
*h = 1;
} else if (digi < (*raiz) -> dato) {
insertar(&((*raiz) -> Izq), digi, h);
if (*h) {
switch ((*raiz)->fe) {
case 1: (*raiz) -> fe = 0;
(*h) = 0;
break;
case 0: (*raiz) -> fe = -1;
break;
case -1:
n1 = (*raiz) -> Izq;
if (n1 -> fe == -1) {
rotacionIzqIzq(raiz, n1);
} else {
rotacionIzqDer(raiz, n1);
}
(*h) = 0;
}
}
} else if (digi > (*raiz) -> dato) {
insertar(&((*raiz) -> Der), digi, h);
if (*h) {
switch ((*raiz) -> fe) {
case 1:
n1 = (*raiz) -> Der;
if (n1 -> fe == +1) {
rotacionDerDer(raiz, n1);
} else {
rotacionDerIzq(raiz, n1);
}
(*h) = 0;
break;
case 0: (*raiz) -> fe = +1;
break;
case -1: (*raiz) -> fe = 0;
(*h) = 0;
break;
}
}
} else {
printf(" ¡Se ha encontrado un número existente: %i, del metodo Inorden y Preorden!\n",digi);
(*h) = 0;
}
}
void preorden(NodoArbol* raiz) {
if (raiz) {
printf(" %i ", raiz->dato);
preorden(raiz->Izq);
preorden(raiz->Der);
}
}
void inorden(NodoArbol* raiz) {
if (raiz) {
inorden(raiz -> Izq);
printf(" %i ", raiz->dato);
inorden(raiz -> Der); 
}
}














void metodoBurbuja(int array[], int n) {
    int i, j, temp;
    for (i = 1; i < n; i++) {
        for (j = 0; j < n - 1; j++) {
            if (array[j] > array[j + 1]) {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
    int a;
    for (a = 0; a < n; a++) {
        printf("%d  ", array[a]);
    }

}

int main(){
FILE *fp;
fp=fopen("./grafica.dat","w+");
   NodoArbol* raiz;
    raiz = NULL; 
FILE* archivo = NULL;
double tiempo;
clock_t inicio,parada;
      int i=0;
      int array[10000];
      int a;
      int h;
archivo = fopen("prueba.txt", "r");
printf("Ingresar arbol:\n"); 
inicio=clock();
while (feof(archivo) == 0) {
    fscanf(archivo, "%d\n", &a);
    insertar(&raiz, a, &h);
    array[i] = a;
    i++;
    h++;

   }
parada=clock();
tiempo=(double)(parada- inicio) / CLOCKS_PER_SEC;
printf("%.16g milisegundos\n", tiempo* 1000.0);

printf("SALIDA ORDENADA:\n");
int it;
double time;
double pos;
inicio=clock();
for(it=0;it<h;it++){ 
    inorden(raiz);
    time=(double)clock()/ CLOCKS_PER_SEC;
    pos=(double)i;
    fprintf(fp,"%f,%f \n",time,pos);
} 
return 0;
parada=clock();
tiempo=(double)(parada- inicio) / CLOCKS_PER_SEC;
printf("\n%.16g milisegundos\n", tiempo* 1000.0);
//Eso te dará el tiempo en milisegundos.   
printf("ORDENAMIENTO BURBUJA:\n");
inicio = clock();
metodoBurbuja(array, i);
parada = clock();
tiempo = (double) (parada - inicio) / CLOCKS_PER_SEC;
printf("\n%.16g Milisegundos \n", tiempo * 1000.0);
  /* Using while instead of if below makes the code slightly more robust. */
}


