#include <iostream>
#include <vector>
#include <fstream>

class we_graph {
private:
    unsigned int num_V; // Total number of vertices in the graph
    unsigned int num_E; // Total number of edges in the graph
    vector<vector<w_edge>> adj_list;    // Contiguous array of pointers
                                        // to vector of we_edge pointers
                                        // (referencing the we_edge objects
                                        // in the edge_list)
    
public:
    we_graph() {};
    
    friend ostream & operator<<(ostream &cout, we_graph &wg) {
        // Overloads stream insertion operator to write a weighted
        // edge graph to an output stream
        for (int v=0; v<wg.V(); v++)
            for (w_edge e: wg.adj(v))
                cout << e << endl;
    }
    
    friend ifstream & operator>>(ifstream &file, we_graph &wg) {
        // Overloads stream extraction operator to read a weighted
        // edge graph from an input stream and update the we_graph object {
        int num_V, num_E;
        w_edge e(-1, -1, 0);
        file >> num_V;
        file >> num_E;
        wg.set_V(num_V);
        wg.set_E(num_E);
        we.resize(num_V);
        while (file >> e)
            wg.add_edge(e);
        return file;
    }
    
    we_graph(unsigned int n) {
        // Constructor that creates an empty graph with V = n vertices in the
        // adj_list contiguous array (with empty we_edge vectors)
        num_V = n;
        resize(num_V);
    }
    
    we_graph(string filename) {
        ifstream file;
        w_edge e(-1, -1, 0);
        
        file.open(filename);
        if (file.fail()) {
            cout << "Error opening file.";
            exit(1);
        } else {
            operator>>(file, *this);
        }
    }
    
    unsigned int V() { return num_V; }
    // Return total number of vertices in the graph
    
    unsigned int E() { return num_E; }
    // Return total number of edges in the graph
    
    void edge_list() {
        // A list of all edges in the graph
        for (int v=0; v<num_V; v++)
            for (w_edge w : adj_list[v])
                cout << w << " , ";
        cout << endl;
    }
    
    void addEdge(w_edge e) {
        // Adds a new we_edge to the edge_list and coresponding pointers
        // to adj_list array at indices v = e.either() and w = e.other(v)
        adj_list[e.either()].emplace_back(e);
        adj_list[e.other(e.either())].emplace_back(e);
    }
    
    vector<w_edge> adj(unsigned int v) { return adj_list[v]; }
    // Returns a vector of edges that are incident to vertex v
    
    void set_V(unsigned int num_V) { this->num_V = num_V; }
    void set_E(unsigned int num_E) { this->num_E = num_E; }
    
    void resize(int num_V) { adj_list.resize(num.V); }
};
