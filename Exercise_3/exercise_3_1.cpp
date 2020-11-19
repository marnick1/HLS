#include <iostream>
#include <ctime>
 // Configure project's include path to
// also contain ${workspaceFolder}/include
#include <ac_int.h>
#include <ac_channel.h>

typedef ac_int<4,false> dtype;

class RunLengthEncoder {
private:
  // Internal state
  dtype current_num;
  dtype last_num;
  dtype count;
public:
  // Constructor - initialize internal state
  RunLengthEncoder(){
    count = 0;
  }
  // Top-level interface
  void run(ac_channel<dtype> &in, ac_channel<dtype> &out){
    if (in.available(1)){
      if (count==0){
        // If there is no value being checked, read a new one
        current_num = in.read();
        count = 1;
      } else {
        // Otherwise, check for same consecutive values
        last_num = current_num;
        current_num = in.read();
        if (last_num==current_num){
          // If value remained the same, increase count
          count++;
        } else {
          // If value changed, write results to output
          out.write(last_num);
          out.write(count);
          // Reset state for the new value
          count = 1;
        }
      }
    }
  }
  // Print private variable
};

void test_runlength_encode(){
  ac_channel<dtype> in;
  ac_channel<dtype> out;
  RunLengthEncoder buffer;
  // Generate values for input
  std::cout << "Input:  ";
  for (int i=30; i>0; ){
    dtype in_num = rand() % 16;
    int repeat = rand() % 10 + 1;
    repeat = (repeat>i) ? i : repeat;
    while (repeat>0){
      in.write(in_num);
      std::cout << in_num << " ";
      repeat--;
      i--;
    }
  }
  std::cout << std::endl;
  // Call RunLengthEncoder.run and check its results
  while(in.available(1)){
    buffer.run(in, out);
  }
  std::cout << "Output: ";
  while(out.available(2)){
    std::cout << out.read() << " ";
    std::cout << out.read() << " | ";
  }
  std::cout << std::endl;
     // Output doesn't print the last value of input stream because
    // there is always one value being processed in the internal state.
   // Considering continuous stream, output will never block as long as 
  // the values keep changing periodically.
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
