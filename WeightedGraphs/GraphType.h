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

// Default constructor
w_edge::w_edge() {
    this->v = -1;
    this->w = -1;
    this->cost = 0;
}

// Constructor
w_edge::w_edge(const unsigned int &a,
              const unsigned int &b, const double &c) {
    v = a;
    w = b;
    cost = c;
}

// Get methods
unsigned int w_edge::get_v() { return v; }
unsigned int w_edge::get_v() const { return v; }
unsigned int w_edge::get_w() { return w; }
unsigned int w_edge::get_w() const { return w; }
double w_edge::get_cost() const { return cost; }

// Set methods
void w_edge::set_v(unsigned int v) { this->v = v; }
void w_edge::set_w(unsigned int w) { this->w = w; }
void w_edge::set_cost(double cost) { this-> cost = cost; }

// Returns a vertex
unsigned int w_edge::either() { return v; }
unsigned int w_edge::other(unsigned int a) {
    if (v == a) { return w; }
    else { return v; }
}

// Overload operators
bool w_edge::operator<(const w_edge e) const {
    return (cost < e.get_cost());
}

bool w_edge::operator>(const w_edge e) const {
    return (cost > e.get_cost());
}

ostream & operator<<(ostream &cout, w_edge e) {
    cout << e.get_v() << "->" << e.get_w();
    return cout;
}

ifstream & operator>>(ifstream &fin, w_edge &e) {
    unsigned int end_pt1, end_pt2;
    double cost;
    
    if (fin >> end_pt1) {
        e.set_v(end_pt1);
        if (fin >> end_pt2) {
            e.set_w(end_pt2);
            if (fin >> cost) {
                e.set_cost(cost);
            } else {
                cout << "Error: no weight provided for edge (" << end_pt1
                    << "," << end_pt2 << ")" << endl;
                exit(1);
            }
        } else {
            cout << "Error: no end point for edge with left vertex " << end_pt1 << endl;
            exit(1);
        }
    }
    return fin;
}
