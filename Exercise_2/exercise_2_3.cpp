#include <iostream>
#include <bitset>
#include <ctime>
 // Configure project's include path to
// also contain ${workspaceFolder}/include
#include <ac_int.h>
#include <ac_channel.h>

void runlength_encode(ac_channel<ac_int<4,false> > &in, ac_channel<ac_int<4,false> > &out){
  ac_int<4,false> new_num;
  ac_int<4,false> check_num;
  ac_int<4,false> count = 0;
  // Check buffer for 10 available values
  if (in.available(10)){
    new_num = in.read();
    count++;
    for (int i=0; i<9; i++){
      // Check for same consecutive values
      check_num = in.read();
      if (new_num==check_num){
        // If value remains the same, increase count
        count++;
      } else {
        // If value changes, write results to output
        out.write(new_num);
        out.write(count);
        // Reset state for new value
        new_num = check_num;
        count = 1;
      }
    }
    out.write(new_num);
    out.write(count);
  }
}

void test_runlength_encode(){
  ac_channel<ac_int<4,false> > in;
  ac_channel<ac_int<4,false> > out;
  // Generate values for input
  std::cout << "Input:  ";
  for (int i=10; i>0; ){
    ac_int<4,false> in_num = rand() % 16;
    int repeat = rand() % 5 + 1;
    repeat = (repeat>i) ? i : repeat;
    while (repeat>0){
      in.write(in_num);
      std::cout << in_num << " ";
      repeat--;
      i--;
    }
  }
  std::cout << std::endl;
  // Call runlength_encode and check its results
  runlength_encode(in, out);
  std::cout << "Output: ";
  while(out.available(2)){
    std::cout << out.read() << " ";
    std::cout << out.read() << " | ";
  }
  std::cout << std::endl;
}

int main(){
  // Initialize random seed
  srand(time(NULL));
  // Number of tests
  const int test_cases = 5;
  for (int i=0; i<test_cases; i++){
    test_runlength_encode();
    std::cout << std::endl;
  }
}
