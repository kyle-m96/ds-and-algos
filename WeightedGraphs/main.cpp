#include "GraphType.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    we_graph wg ("graph.txt");
    prim_mst_lz mst(wg);
    
    cout << "The MST of weighted graph is: " << mst;
    
    return 0;
}
