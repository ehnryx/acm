#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

struct Tree {
  string tour;
  operator string() const { return tour; }

  struct Node {
    int v;
    Node(int _v): v(_v) {}
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;
  };
  Node* root = nullptr;

  Tree(const vector<int>& vals) {
    for(int x : vals) {
      if(root == nullptr) {
        root = new Node(x);
      } else {
        add_val(root, x);
      }
    }
    build(root);
  }
  void add_val(Node* u, int x) {
    if(x < u->v) {
      if(u->left == nullptr) {
        u->left = new Node(x);
        u->left->parent = u;
      } else {
        add_val(u->left, x);
      }
    } else {
      if(u->right == nullptr) {
        u->right = new Node(x);
        u->right->parent = u;
      } else {
        add_val(u->right, x);
      }
    }
  }
  void build(Node* u) {
    if(u->left) {
      tour.push_back('L');
      build(u->left);
      tour.push_back('U');
    }
    if(u->right) {
      tour.push_back('R');
      build(u->right);
      tour.push_back('U');
    }
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int n, m;
  cin >> n >> m;
  set<string> all;
  for(int i=0; i<n; i++) {
    vector<int> a(m);
    for(int j=0; j<m; j++) {
      cin >> a[j];
    }
    all.insert(Tree(a));
  }
  cout << all.size() << nl;

  return 0;
}
