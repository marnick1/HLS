#include <iostream>
#include <bitset>
 // Configure project's include path to
// also contain ${workspaceFolder}/include
#include <ac_int.h>
#include <ac_fixed.h>

int main(){
  // Question A
  std::cout << "Question A:" << std::endl;

  ac_int<8,false> a,b;  // 8−bit unsigned integer
  a = 0;
  b = 255;
   // In unsigned multiplication, we add the bits of each number
  // (8-bit)*(8-bit)=(16-bit)
  ac_int<16,false> tmp1 = a*b;
  std::cout << "a=" << a << ": " << std::bitset<8>(a) << std::endl;
  std::cout << "b=" << b << ": " << std::bitset<8>(b) << std::endl;
  std::cout << "a*b=" << tmp1 << ": " << std::bitset<16>(tmp1) << std::endl;

  ac_int<9,true> c,d;   // 9−bit signed integer
  c = 255;
  d = -256;
    // In signed multiplication, we add the bits of each number,
   // then substract 1 so that we don't calculate the sign bit twice
  // (9-bit)*(9-bit)=(17-bit)
  ac_int<17,true> tmp2 = c*d;
  std::cout << "c=" << c << ": " << std::bitset<9>(c) << std::endl;
  std::cout << "d=" << d << ": " << std::bitset<9>(d) << std::endl;
  std::cout << "c*d=" << tmp2 << ": " << std::bitset<17>(tmp2) << std::endl;

    // A 16-bit unsigned number can be converted to a 17-bit signed one
   // In addition, we add 1 bit to the number with the most bits
  // (17-bit)+(17-bit)=(18-bit)
  ac_int<18,true> e = tmp1 + tmp2; // Result is 18-bit
  std::cout << "e=a*b+c*d=" << e << ": " << std::bitset<18>(e) << std::endl;

  // Question B
  std::cout << std::endl << "Question B:" << std::endl;

  ac_fixed<5,2,false> f;  //5−bit unsigned fixed−point type with 2 integer bits
  f = 3.875;
  std::cout << "f=" << f << ": ";
  for (int i=f.length()-1; i>=0; i--){
    std::cout << f[i];
  }
  std::cout << std::endl;
  
  ac_fixed<5,4,true> g;   // 5−bit signed fixed−point type with 4 integer bits
  g = 7.5;
  std::cout << "g=" << g << ": ";
  for (int i=g.length()-1; i>=0; i--){
    std::cout << g[i];
  }
  std::cout << std::endl;

     // A 5-bit unsigned number can be converted to a 6-bit signed one
    // In signed multiplication, we add the bits of each number,
   // then substract 1 so that we don't calculate the sign bit twice
  // (6-bit)*(5-bit)=(10-bit)
   // In real number multiplication, the bits after the radix point are added
  // (3-bits after .)*(1-bit after .)=(4-bits after .)
  ac_fixed<10,6,true> h = f * g; // Result is 10-bit with a 6-bit integer part (10-4)
  std::cout << "h=f*g=" << h << ": ";
  for (int i=h.length()-1; i>=0; i--){
    std::cout << h[i];
  }
  std::cout << std::endl;
}