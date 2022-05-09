#include "w_edge.h"
#include "we_graph.h"
#include "prim_mst_lz.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    we_graph wg ("graph.txt");
    prim_mst_lz mst(wg);
    
    cout << "The MST of weighted graph is: " << mst;
    
    return 0;
}
