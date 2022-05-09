#include "w_edge.h"
#include "we_graph.h"
#include <queue>
#include <vector>

class prim_mst_lz {
private:
    bool *marked;
    queue<w_edge> mst;
    priority_queue<w_edge, vector<w_edge>, compare<w_edge>> pq;
    
    void visit(we_graph G, int v) {
    marked[v] = true;
    for (w_edge e : G.adj(v))
        if (!marked[e.other(v)])
            pq.emplace(e);
    }
    
public:
    prim_mst_lz() {}
    prim_mst_lz(we_graph G) {
        marked = new bool[G.V()];
        visit(G, 0);
        while (!pq.empty() && mst.size() < G.V() - 1) {
            w_edge e = pq.top();
            pq.pop();
            int v = e.either(), w = e.other(v);
            if (marked[v] && marked[w]) continue;
            mst.emplace(e);
            if (!marked[v]) visit (G, v);
            if (!marked[w]) visit (G, w);
        }
    }
    
    queue<w_edge> mstl() { return mst; }
    
    friend ostream & operator<< (ostream &cout, prim_mst_lz& mst) {
        queue<w_edge> q = mst.mstl();
        while (!q.empty()) {
            cout << endl << q.front();
            q.pop();
        }
        return cout;
    }
};
