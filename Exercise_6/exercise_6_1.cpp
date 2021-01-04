#include <iostream>
#include <cstdlib>
#include <ctime>
//#include "mc_scverify.h"

static const int N = 10000;
static const int RUNS = 10;

// Only 1 multiplier, 1 adder & 1 memory interface available
#pragma hls_design top
//void CCS_BLOCK(calc)(int Mem[5][N]){
void calc(int Mem[5][N]){
  for (int i=0; i<N; ++i){
    Mem[0][i] = Mem[1][i]*Mem[2][i] - Mem[3][i]*Mem[4][i];
  }
}

void test_function(){
  // Generate random arrays
  int Mem[5][N];
  for (int i=0; i<N; ++i){
    Mem[1][i] = rand() % 64;
    Mem[2][i] = rand() % 64;
    Mem[3][i] = rand() % 64;
    Mem[4][i] = rand() % 64;
  }
  // Call the function
  calc(Mem);
  // Print results
  // for (int i=0; i<N; ++i){
  //   std::cout << Mem[0][i] << std::endl;
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


