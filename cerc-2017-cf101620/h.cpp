#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Node {
  string name;
  map<string,Node*> child;
  int size;
  int expand;
  Node(const string& s = "/"): name(s) {
    size = 0;
    expand = 0;
  }

  int count(const string& s) const {
    return child.count(s);
  }

  pii build(int t) {
    for (const pair<string,Node*>& n : child) {
      pii res = n.second->build(t);
      size += res.first;
      expand += res.second;
    }
    if (size >= t) expand++;
    return pii(size, expand);
  }

  void print() {
    char type;
    if (child.empty()) type = ' ';
    else if (expand > 1) type = '-';
    else type = '+';
    cout << type << " " << name << " " << size << nl;

    if (expand > 1) {
      for (const pair<string,Node*>& n : child) {
        n.second->print();
      }
    }
  }
};

Node* root = new Node();

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;

  int m;
  string s;
  for (int i = 0; i < n; i++) {
    cin >> s >> m;
    int pre = -1;
    Node* cur = root;
    for (int j = 0; j < s.size(); j++) {
      if (s[j] == '/') {
        if (pre != -1) {
          string name = s.substr(pre, j-pre+1);
          if (!cur->count(name)) cur->child[name] = new Node(cur->name + name);
          cur = cur->child[name];
        }
        pre = j+1;
      }
    }
    cur->size += m;
  }

  int threshold;
  cin >> threshold;

  root->build(threshold);
  root->print();

  return 0;
}
