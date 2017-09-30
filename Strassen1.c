#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 1048576/32

void soma(int **a, int **b, int **c, int tam){
    int i,j;
    for(i = 0; i < tam; i++)
      for(j = 0; j < tam; j++)
        c[i][j] = a[i][j] + b[i][j];
}

void subtra(int **a, int **b, int **c, int tam){
    int i,j;
    for(i = 0; i < tam; i++)
      for(j = 0; j < tam; j++)
        c[i][j] = a[i][j] - b[i][j];
}

void multi(int **a, int **b,int **c, int tam){
int i,j,k,aux;
  for(i = 0; i < tam; i++){
      for(j = 0; j < tam; j++){
          aux = 0;
          for(k = 0; k < tam; k++){
              aux += a[i][k] * b[k][j];
          }
          c[i][j] = aux;
      }
  }

}

void multit(int **a, int **b,int **c, int tam, int e, int f, int end){
  if (end < tam){
      if (e < tam){
          if (f < tam){
              c[end][e] += a[end][f] * b[f][e];
              f++;
              return multit(a, b, c, tam, e, f,end);
          }
          f = 0;
          e++;
          return multit(a, b, c, tam, e, f,end);
      }
      e = 0;
      end++;
      return  multit(a, b, c, tam, e, f,end);
    }
  else{
    return;
  }
}


void divide(int **a, int **b, int tamB, int ia, int jb){
  int i,j,i1,j1;
  for(i = 0,i1 = ia; i < tamB; i++,i1++)
    for(j = 0,j1 = jb; j < tamB; j++,j1++)
      b[i][j] = a[i1][j1];
}

void junta(int **a, int **b, int tamB, int ia, int ib){
  int i,j,i1,j1;
  for(i = 0,i1 = ia; i < tamB; i++,i1++)
    for(j = 0,j1 = ib; j < tamB; j++,j1++)
      a[i1][j1] = b[i][j];
}

int** cria(int **a, int tam){
  int i;
  a = (int **) malloc((tam) * sizeof(int*));
  for(i = 0; i < tam; i++)
    a[i] = (int *)malloc((tam-1) * sizeof(int));
  if(a == NULL)
    exit(1);
  return a;
}

void strassen(int **a, int **b, int **c, int tam){
  if (tam == 1){
        c[0][0] = a[0][0] * b[0][0];
        return;
  }
  int **A11 = NULL;
  int **A12 = NULL;
  int **A21 = NULL;
  int **A22 = NULL;
  int **B11 = NULL;
  int **B12 = NULL;
  int **B21 = NULL;
  int **B22 = NULL;

  A11 = cria(A11,tam/2);
  A12 = cria(A12,tam/2);
  A21 = cria(A21,tam/2);
  A22 = cria(A22,tam/2);
  B11 = cria(B11,tam/2);
  B12 = cria(B12,tam/2);
  B21 = cria(B21,tam/2);
  B22 = cria(B22,tam/2);

  int **C11 = NULL;
  int **C12 = NULL;
  int **C21 = NULL;
  int **C22 = NULL;
  int **S1 = NULL;
  int **S2 = NULL;

  C11 = cria(C11,tam/2);
  C12 = cria(C12,tam/2);
  C21 = cria(C21,tam/2);
  C22 = cria(C22,tam/2);
  S1 = cria(S1,tam/2);
  S2 = cria(S2,tam/2);

  int **m1 = NULL;
  int **m2 = NULL;
  int **m3 = NULL;
  int **m4 = NULL;
  int **m5 = NULL;
  int **m6 = NULL;
  int **m7 = NULL;

  m1 = cria(m1,tam/2);
  m2 = cria(m2,tam/2);
  m3 = cria(m3,tam/2);
  m4 = cria(m4,tam/2);
  m5 = cria(m5,tam/2);
  m6 = cria(m6,tam/2);
  m7 = cria(m7,tam/2);
  int i;

  divide(a,A11,tam/2,0,0);
  divide(a,A12,tam/2,0,tam/2);
  divide(a,A21,tam/2,tam/2,0);
  divide(a,A22,tam/2,tam/2,tam/2);
  divide(b,B11,tam/2,0,0);
  divide(b,B12,tam/2,0,tam/2);
  divide(b,B21,tam/2,tam/2,0);
  divide(b,B22,tam/2,tam/2,tam/2);

  // m1
  soma(A11, A22, S1, tam/2);
  soma(B11, B22, S2, tam/2);
  strassen(S1, S2, m1, tam/2);

  //m2
  soma(A21, A22, S1, tam/2);
  strassen(S1, B11, m2, tam/2);

  //m3
  subtra(B12, B22, S2, tam/2);
  strassen(A11, S2, m3, tam/2);

  //m4
  subtra(B21, B11, S2, tam/2);
  strassen(A22, S2, m4, tam/2);

  //m5
  soma(A11, A12, S1, tam/2);
  strassen(S1, B22, m5, tam/2);

  //m6
  subtra(A21, A11, S1, tam/2);
  soma(B11, B12, S2, tam/2);
  strassen(S1, S2, m6, tam/2);

  //m7
  subtra(A12, A22, S1, tam/2);
  soma(B21, B22, S2, tam/2);
  strassen(S1, S2, m7, tam/2);

  //C11
  soma(m1, m4, C11, tam/2);
  subtra(C11, m5, C11, tam/2);
  soma(C11, m7, C11, tam/2);

  //C12
  soma(m3, m5, C12, tam/2);

  //C21
  soma(m2, m4, C21, tam/2);

  //C22
  subtra(m1, m2, C22, tam/2);
  soma(C22, m3, C22, tam/2);
  soma(C22, m6, C22, tam/2);


  junta(c,C11,tam/2,0,0);
  junta(c,C12,tam/2,0,tam/2);
  junta(c,C21,tam/2,tam/2,0);
  junta(c,C22,tam/2,tam/2,tam/2);
  for(i = 0; i < tam/2;i++){
    free(A11[i]);
    free(A12[i]);
    free(A21[i]);
    free(A22[i]);
    free(B11[i]);
    free(B12[i]);
    free(B21[i]);
    free(B22[i]);
    free(m1[i]);
    free(m2[i]);
    free(m3[i]);
    free(m4[i]);
    free(m5[i]);
    free(m6[i]);
    free(m7[i]);
    free(S1[i]);
    free(S2[i]);
  }
  free(A11);free(A12);free(A21);free(A22);free(B11);free(B12);free(B21);free(B22);free(C11);free(C12);free(C21);free(C22);
  free(m1);free(m2);free(m3);free(m4);free(m5);free(m6);free(m7);free(S1);free(S2);
}

int main (){
  int **a = NULL;
  int **b = NULL;
  int **c = NULL;
  int **d = NULL;
  int i=0,j=0;
  srand(time(NULL));
  clock_t start;

  a = cria(a,TAM);
  b = cria(b,TAM);
  c = cria(c,TAM);
  d = cria(d,TAM);

  for(i = 0; i < TAM; ++i){
    for(j = 0; j < TAM; ++j){
      a[i][j] = rand()%10;
    }
  }

  for(i = 0; i < TAM; i++){
    for(j = 0; j < TAM; j++){
      b[i][j] = rand()%10;
    }
  }

  start = clock();
  multi(a, b, c, TAM);
  start = clock() - start;
  printf("O tempo da multiplicacao normal = %lf\n", (double) (start)/CLOCKS_PER_SEC);

  for(i = 0; i < TAM; i++){
    free(c[i]);
  }
  free(c);
  c = cria(c,TAM);

  start = clock();
  strassen(a,b,c,TAM);
  start = clock() - start;

  printf("O tempo da multiplicacao strassen = %lf\n", (double) (start)/CLOCKS_PER_SEC);

  // printf("*\tRESULTADO \t*\n");
  // for(i = 0; i < TAM; i++){
  //   for(j = 0; j < TAM; j++){
  //     printf("%4d ",c[i][j] );
  //   }
  //   printf("\n");
  // }
  for(i = 0; i < TAM; i++){
    free(a[i]);
    free(b[i]);
    free(c[i]);
  }

  free(a);
  free(b);
  free(c);


  return 0;
}
