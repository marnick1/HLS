#include <iostream>
#include <cstdlib>
#include <ctime>
//#include "mc_scverify.h"

static const int N = 10; // rows
static const int M = 26; // cols
static const int RUNS = 1;

// Dual-port memories available
#pragma hls_design top
//void CCS_BLOCK(mean_filter)(int img[N][M], int out[N][M]){
void mean_filter(int img[N][M], int out[N][M]){
  // Solution 2
  int kernel[6];
  // scan the image row by row
  ROW:for (int i=0; i<N; ++i) {
    // scan each row pixel by pixel from left to right
    COL:for (int j=-2; j<M; j+=2) {
      // Shift kernel
      kernel[0] = (j>=0)  ? kernel[2]   : 0;
      kernel[1] = (j>=0)  ? kernel[3]   : 0;
      kernel[2] = (j>=0)  ? kernel[4]   : 0;
      kernel[3] = (j>=0)  ? kernel[5]   : 0;
      kernel[4] = (j<M-2) ? img[i][j+2] : 0;
      kernel[5] = (j<M-3) ? img[i][j+3] : 0;
      // compute the mean
      if (j>=0){
        out[i][j]   = (kernel[0]+kernel[1]+kernel[2]+kernel[3]+kernel[4]) / 5;
        out[i][j+1] = (kernel[1]+kernel[2]+kernel[3]+kernel[4]+kernel[5]) / 5;
      }
    }
  }
}

void test_function(){
  // Generate random arrays
  int img_in[N][M];
  int img_out[N][M];
  for (int i=0; i<N; ++i){
    for (int j=0; j<M; ++j){
      img_in[i][j] = rand() % 256;
    }
  }
  // Call the function
  mean_filter(img_in, img_out);
  // Print results
  // for (int i=0; i<N; ++i){
  //   std::cout << "Input: \t \t";
  //   for (int j=0; j<M; ++j){
  //     std::cout << img_in[i][j] << "\t";
  //   }
  //   std::cout << std::endl;
  //   std::cout << "Output: \t";
  //   for (int j=0; j<M; ++j){
  //     std::cout << img_out[i][j] << "\t";
  //   }
  //   std::cout << std::endl;
  // }
}

//CCS_MAIN(int argc, char* argv[]){
int main(){
  // Initialize random seed
  srand(time(NULL));
  // Number of tests
  for (int i=0; i<RUNS; i++){
    test_function();
  }
}
