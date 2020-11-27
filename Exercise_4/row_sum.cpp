#include <iostream>
#include <cstdlib>
#include <ctime>

//#include "mc_scverify.h"

static const int N = 5;
static const int M = 3;

static const int RUNS = 10;

#pragma hls_design top
//void CCS_BLOCK(compute_row_sum)(short a[N][M], short row_sum[N]){
void compute_row_sum(short a[N][M], short row_sum[N]){
  // // Solution 1
  // ROWS:for (int i=0; i < N; i++){
  //   row_sum[i] = 0;
  //   COLS:for (int j=0; j < M; j++){
  //     row_sum[i] += a[i][j];
  //   }
  // }
  // Solution 2
  short sum;
  ROWS:for (int i=0; i<N; i++){
    sum = 0;
    COLS:for (int j=0; j<M; j++){
      sum += a[i][j];
    }
    row_sum[i] = sum;
  }
  // // Solution 3
  // short sum = 0;
  //   int i = 0;
  //   int j = 0;
  //   Merged: while((i*M+j)<(N*M)){
  //     std::cout << i << " " << j << std::endl;
  //     sum += a[i][j];
  //     j++;
  //     if (j==M){
  //       row_sum[i] = sum;
  //       sum = 0;
  //       j = 0;
  //       i++;
  //     }
  //   }
  // }
}

//CCS_MAIN(int argc, char* argv[]){
int main(){
  short x[N][M];
  short row_sum_of_x[N];

  // reseed RNG
  std::srand(std::time(NULL));

  // run RUNS tests
  for (int k=1; k<=RUNS; k++){
    std::cout << "Test " << k << std::endl;

    // fill input matrix with random values
    // for simplicity keep values below 20
    std::cout << "Array:" << std::endl;
    for (int i=0; i < N; i++) {
      for (int j=0; j < M; j++) {
        x[i][j] = std::rand() % 20;
        std::cout << x[i][j] << "\t";
      }
      std::cout << std::endl;
    }

    // call DUT
    compute_row_sum(x, row_sum_of_x);

    // print out the computed sums of each row
    std::cout << "Row Sum:" << std::endl;
    for (int i=0; i < N; i++){
      std::cout << row_sum_of_x[i] << "\t";
    }
    std::cout << std::endl << std::endl;
  }
}