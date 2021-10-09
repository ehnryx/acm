#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct LinkedList {
  struct Node {
    char c;
    Node* left;
    Node* right;
    Node(char c, Node* l, Node* r): c(c), left(l), right(r) {}
    void reverse() {
      swap(left, right);
    }
  };

  unordered_map<char,Node*> pos;

  LinkedList(const string& s, int n, int a, int b) {
    Node* pre = nullptr;
    for (int i = 1; i <= n; i++) {
      Node* cur = new Node(s[i-1], pre, nullptr);
      if (pre != nullptr) pre->right = cur;
      pre = cur;
      if (i == a) pos['L'] = cur;
      if (i == b) pos['R'] = cur;
    }
  }

  void move_left(char x) {
    Node* cur = pos[x];
    Node* nxt = cur->left;
    if (nxt->left == cur) nxt->reverse();
    pos[x] = nxt;
  }

  void move_right(char x) {
    Node* cur = pos[x];
    Node* nxt = cur->right;
    if (nxt->right == cur) nxt->reverse();
    pos[x] = nxt;
  }

  void reverse() {
    Node* pre = pos['L']->left;
    Node* nxt = pos['R']->right;
    if (pre != nullptr) pre->right = pos['R'];
    if (nxt != nullptr) nxt->left = pos['L'];
    swap(pos['L']->left, pos['R']->right);
    pos['L']->reverse();
    pos['R']->reverse();
    swap(pos['L'], pos['R']);
  }

  char query(char x) {
    return pos[x]->c;
  }
};

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int n, a, b;
  cin >> n >> a >> b;
  string s;
  cin >> s;
  LinkedList snake(s, n, a, b);

  int q;
  cin >> q;
  char t, x, y;
  while (q--) {
    cin >> t;
    if (t == 'S') {
      cin >> x >> y;
      if (y == 'L') snake.move_left(x);
      else snake.move_right(x);
    }
    else if (t == 'R') {
      snake.reverse();
    } else {
      cin >> x;
      cout << snake.query(x);
    }
  }
  cout << nl;

  return 0;
}
