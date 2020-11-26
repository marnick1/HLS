#include <iostream>
#include <ctime>

static const int N = 5;
static const int M = 3;

static const int RUNS = 10;
 
void compute_row_sum(short a[N][M], short row_sum[N]){
  ROWS:for (int i=0; i < N; i++){
    row_sum[i] = 0;
    COLS:for (int j=0; j < M; j++){
      row_sum[i] += a[i][j];
    }
  }
}

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
  
  return 0;
}

