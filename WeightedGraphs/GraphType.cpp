#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

template <class T>
struct compare {
    bool operator() (const T a, const T b) { return a > b; }
};

class w_edge {
public:
    w_edge();
    // Default constructor
    
    w_edge(const unsigned int &a,
           const unsigned int &b, const double &c);
    // Constructs new w_edge object and sets its data fields
    // as follows: v=a, w=b, cost=c
    
    unsigned int get_v();
    unsigned int get_v() const;
    unsigned int get_w();
    unsigned int get_w() const;
    double get_cost() const;
    
    void set_v(unsigned int);
    void set_w(unsigned int);
    void set_cost(double);
    
    unsigned int either();
    // Returns vertex v
    
    unsigned int other(unsigned int a);
    // Returns vertex w if a=v, otherwise it returns v
    
    bool operator<(const w_edge) const;
    // Compares two edges according to their weights
    
    bool operator>(const w_edge) const;
    // Compares two edges according to their weights
    
    friend ifstream & operator>>(ifstream &, w_edge&);
    // Read a weighted edge from an input stream and
    // updated the w_edge object
    
    friend ofstream & operator<<(ifstream &, w_edge&);
    // Write a weighted edge to an output stream
};

w_edge::w_edge() {
    this->v = -1;
    this->w = -1;
    this->cost = 0;
}

w_edge:w_edge(const unsigned int &a,
              const unsigned int &b, const double &c) {
    v = a;
    w = b;
    cost = c;
}

