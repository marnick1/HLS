#include <iostream>
#include <bitset>
#include <ctime>
 // Configure project's include path to
// also contain ${workspaceFolder}/include
#include <ac_int.h>

// Struct for canonic signed digit representation
template <int W>
struct CSD {
  ac_int<W,false> x_p;
  ac_int<W,false> x_m;
  CSD(){
    x_p = 0;
    x_m = 0;
  }
};

// Function for converting a binary number to CSD
template <int W>
void csd_encode(ac_int<W,true> &num, CSD<W> &num_csd){
  // Split to sign and magnitude
  ac_int<1,false> sign = num[W-1];
  ac_int<W+1,false> magnitude = abs(num);
  // Create an empty position at magnitude[-1]
  magnitude = magnitude << 1;
  // Calculate the CSD of the positive number
  magnitude[W] = magnitude[W] ? magnitude[W] : magnitude[W-1];
  ac_int<1,false> theta;
  ac_int<1,false> gamma = 0;
  for (int i=1; i<W; i++){
    theta = magnitude[i]^magnitude[i-1];
    gamma = (~gamma)&theta;
    if (magnitude[i+1]==sign){
      num_csd.x_p[i-1] = gamma;
    } else {
      num_csd.x_m[i-1] = gamma;
    }
  }
  if (sign){
    num_csd.x_m[W-1] = magnitude[W];
  } else {
    num_csd.x_p[W-1] = magnitude[W];
  }
}

// Function for multiplying a binary number with a CSD
template <int W>
ac_int<2*W,true> csd_mult (ac_int<W,true> &in, const CSD<W> &constant_csd){
  ac_int<2*W,true> shift = in;
  ac_int<2*W,true> product = 0;
  for (int i=0; i<W; i++){
    if (constant_csd.x_p[i]){
      product += shift << i;
    } else if (constant_csd.x_m[i]){
      product -= shift << i;
    }
  }
  return product;
}

 // Function that checks csd_encode and
// csd_mult using random numbers as input
void test_csd(){
  // Define bit-width
  static const int bitWidth = 16;
  // Find number limits for this bit-width
  unsigned long long int MIN_VAL = 1;
  for (int i=0; i<bitWidth-1; i++){
    MIN_VAL = MIN_VAL << 1;
  }
  unsigned long long int MAX_VAL = MIN_VAL - 1;
  // Genarate two numbers
  ac_int<bitWidth,true> num1 = (rand() + rand()) % (MAX_VAL+MIN_VAL+1) - MIN_VAL;
  ac_int<bitWidth,true> num2 = (rand() + rand()) % (MAX_VAL+MIN_VAL+1) - MIN_VAL;
  std::cout << "num1: " << num1 << std::endl;
  std::cout << "num2: " << num2 << std::endl;
  // Convert num1 to CSD representation
  CSD<bitWidth> num1_csd;
  csd_encode<bitWidth>(num1, num1_csd);
  std::cout << "Number to encode: " << std::bitset<bitWidth>(num1) << " " << num1 <<std::endl;
  std::cout << "Positive part:    " << std::bitset<bitWidth>(num1_csd.x_p) << " " << num1_csd.x_p <<std::endl;
  std::cout << "Negative part:    " << std::bitset<bitWidth>(num1_csd.x_m) << " " << num1_csd.x_m <<std::endl;
  std::cout << "Pos - Neg parts:  " << std::bitset<bitWidth>(num1_csd.x_p-num1_csd.x_m) << " " << num1_csd.x_p-num1_csd.x_m <<std::endl;
  // Multiply num1 * num2, where num1 is CSD and num2 is binary
  ac_int<bitWidth*2,true> product = csd_mult (num2, num1_csd);
  std::cout << "Num1 * Num2:      " << std::bitset<bitWidth*2>(product) << " " << product <<std::endl;
}

int main(){
  // Initialize random seed
  srand(time(NULL));
  // Number of tests
  const int test_cases = 5;
  for (int i=0; i<test_cases; i++){
    test_csd();
    std::cout << std::endl;
  }
}