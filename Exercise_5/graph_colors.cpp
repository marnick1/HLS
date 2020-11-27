#include <iostream>
#include <bitset>
#include <cstdlib>
#include <ctime>
#include <ac_int.h>

//#include "mc_scverify.h"

static const int V = 6;
typedef ac_int<V,false> dtype;

static const int RUNS = 5;

#pragma hls_design top
//void CCS_BLOCK(color_nodes)(dtype adj_G[V], dtype nodeColor[V], short &totalColors){
void color_nodes(dtype adj_G[V], dtype nodeColor[V], short &totalColors){
  dtype maxColor = 0;
  // For every node
  NODES:for (short i=0; i<V; ++i){
    dtype color = 1;
    dtype edge = adj_G[i];
    dtype neighbor = 0;
    // For every neighbor
    NEIGHBORS:for (short j=0; j<V-1; ++j){
      dtype temp = neighbor|nodeColor[j];
      color = (edge[j] && (j<i)) ? (dtype)~(temp) : color;
      neighbor = (edge[j] && (j<i)) ? (temp) : neighbor;
    }
    ARBITER:for (short j=0; j<V; j++){
      if (color[j]){
        nodeColor[i] = 1 << j;
        maxColor = (maxColor<(1<<j)) ? (dtype)(1<<j) : maxColor;
        break;
      }
    }
  }
  DECODER1_HOT:for (short j=0; j<V; j++){
    if (maxColor[j]){
      totalColors = j+1;
      break;
    }
  }
}

//CCS_MAIN(int argc, char* argv[]){
int main(){
  short totalColors;
  dtype nodeColor[V];
  dtype Adj_G[V];

  std::srand(std::time(NULL));

  for (int k=0; k<RUNS; k++){
    std::cout << "Run " << k+1 << std::endl;
    // Randomly generate adjacency matrix
    for (int i=0; i<V; ++i){
      Adj_G[i] = std::rand() % (1<<V); // range [0, 2^V-1]
      Adj_G[i][i] = 0; // diagonal = 0
    }
    // Make graph non-directive
    for (int i=0; i<V; ++i){
      for (int j=0; j<V; ++j){
        Adj_G[j][i] = Adj_G[i][j];
        std::cout << Adj_G[i][j] << " ";
      }
      std::cout << std::endl;
    }
    // Call DUT - color the graph
    color_nodes(Adj_G, nodeColor, totalColors);
    // Print results
    std::cout << "Colors:" << std::endl;
    for (int i = 0; i<V; ++i){
      std::cout << std::bitset<V>(nodeColor[i]) << std::endl;
    }
    std::cout << "Color number = " << totalColors << std::endl;
  }
}