#include <iostream>
#include <ctime>

// Function that calculates the checksum of a number
unsigned int checksum(unsigned int in_num){
  unsigned int remainder = 0;
  unsigned int result = 0;
   // Max value of a 32-bit unsigned integer is
  // 4,294,967,295 which contains 10 decimal digits
  for (int i=0; i<10; i++){
    remainder = in_num % 10;
    in_num = in_num / 10;
    if (i&1){
      remainder = remainder*2;
      remainder = (remainder%10) + (remainder/10);
    }
    result += remainder;
  }
  return result;
}

 // Function that checks the output of
// checksum using random numbers as input
void test_checksum(){
  // Generate a random number
  unsigned long long int limit = UINT_MAX;
  unsigned int rand_num = rand() % (limit+1);
  // Call checksum and validate the result
  unsigned int res = checksum(rand_num);
  std::cout << "The input number is " << rand_num << std::endl;
  std::cout << "Function checksum returns " << res << "." << std::endl;
}

int main(){
  // Initialize random seed
  srand(time(NULL));
  // Number of tests
  const int test_cases = 5;
  for (int i=0; i<test_cases; i++){
    test_checksum();
    std::cout << std::endl;
  }
}