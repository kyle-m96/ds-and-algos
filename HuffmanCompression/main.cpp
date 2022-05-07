#include <cstdlib>
#include <iostream>
#include <fstream>
#include <memory>
#include <bitset>
#include <sstream>
#include <vector>
#include <queue>

using namespace std;

template <class T>
struct compare {
  bool operator() (const T a, const T b) { return a > b; }
};

class Node {
  private:
    char ch;
    int freq;
    shared_ptr<Node> left, right;
    
  public:
    Node (char ch, int freq, shared_ptr<Node> left, shared_ptr<Node> right) {
      this->ch = ch;
      this->freq = freq;
      this->left = left;
      this->right = right;
    }
    bool isLeaf() { return left == nullptr && right == nullptr; }
    bool operator< (Node that) { return this->freq > that.get_freq(); }
    void sel_val (char val) { ch = val; }
    char get_val() { return ch; }
    shared_ptr<Node> get_left() { return left; }
    shared_ptr<Node> get_right() { return right; }
    int get_freq() { return freq; }
}

class Huffman {
  private:
    vector<int> freq;
    shared_ptr<Node> root;
    int R=128;
    
  public:
    Huffman() { freq.resize(R); }
    vector<int> getFrequencies() { return freq; }
    shared_ptr<Node> buildTrie() {
      priority_queue<shared_ptr<Node>, vector<shared_ptr<Node>>, compare<shared_ptr<Node>>> pq;
      shared_ptr<Node> z;
      for (int i=0; i<R; i++) {
        if (freq[i] > 0) {
          pq.push(make_shared<Node>(i, freq[i], nullptr, nullptr));
        }
      }

      while (pq.size() > 1) {
        shared_ptr<Node> x = pq.top();
        pq.pop();
        shared_ptr<Node> y = pq.top();
        pq.pop();
        shared_ptr<Node> parent = shared_ptr<Node>(new Node('\0', x->get_freq() + y->get_freq(), x, y));
        pq.push(parent);
      }
      shared_ptr<Node> a;
      a = pq.top();
      pq.pop();

      return a;
    }
    shared_ptr<Node> readTrie(istream& in) {
      bitset<1> bit;
      in >> bit;
      if (bit.any()) {
        bitset<8> Ch;
        in >> Ch;
        char c(Ch.to_ulong());
        return static_cast<shared_ptr<Node>>(new Node(c, 0, nullptr, nullptr));
      }
      shared_ptr<Node> x = readTrie(in);
      shared_ptr<Node> y = readTrie(in);
      return static_cast<shared_ptr<Node>>(new Node('\0', 0, x, y));
    }
    void writeTrie(shared_ptr<Node> x, ostream &out) {
      bitset<8> Ch;
      if (x->isLeaf()) {
        out << true;
        out << (Ch = x->get_val());
        return;
      }
      out << false;
      writeTrie(x->get_left(), out);
      writeTrie(x->get_right(), out);
    }
    void expand(ifstream& in, ostream& out) {
      shared_ptr<Node> root = readTrie(in);
      bitset<1> bit;
     while (in >> bit) {
      shared_ptr<Node> x = root;
      while (!x->isLeaf()) {
        if (bit.none()) {
          x = x->get_left();
        } else {
          x = x->get_right();
        }
        if (!x->isLeaf()) {
          in >> bit;
        }
      }
    }
    out << x->get_val();
    }
};

int main(int argc, char** argv) {
  string mode;
	Huffman h;
  
	ifstream inFile("compressed.txt");
	ofstream outFile("output.txt");
  
	if (inFile.fail()) { exit(1); }
	if (outFile.fail()) { exit(1); }

  cout << "Enter mode: ";
	cin >> mode;
  
	if (mode == "-e") {
    h.expand(inFile, outFile);
		outFile.close();
		string data;
		ifstream in("output.txt");
		while (!in.eof()) {
      in >> data;
			cout << data;
		}
  } else if (mode == "-c") {
      cout << "Compression is not available.";
	}
  
	inFile.close();
  
	return 0;
}
