#include <iostream>
#include <ctime>
#include <bitset>

// Function that counts one-bits in a 32-bit number
unsigned short int countBits(unsigned int in_num){
  unsigned short int oneBits = 0;
  // Check the last digit, then shift by one
  for (int i=0; i<32; i++){
    if (in_num&1){
      oneBits++;
    }
    in_num = in_num >> 1;
  }
  return oneBits;
}

 // Function that checks the output of
// countBits using random numbers as input
void test_countBits(){
  // Generate a random number
  unsigned long long int limit = UINT_MAX;
  unsigned int rand_num = rand() % (limit+1);
  // Call countBits and validate the result
  unsigned short int res = countBits(rand_num);
  std::cout << "The input number is " << rand_num << std::endl;
  std::cout << "In binary: " << std::bitset<32>(rand_num) << std::endl;
  std::cout << "Function countBits returns " << res << " one-bits." << std::endl;
}

int main(){
  // Initialize random seed
  srand(time(NULL));
  // Number of tests
  const int test_cases = 5;
  for (int i=0; i<test_cases; i++){
    test_countBits();
    std::cout << std::endl;
  }
}