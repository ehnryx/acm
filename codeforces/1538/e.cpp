%:include <bits/stdc++.h>
using namespace std;

%:include "../../../lca/misc/fast_input.h"
%:include "../../../lca/data_structure/splay_tree.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

struct data_t {
  ll res;
  string left, right;
};

int count(const string& s, const string& t) {
  int res = 0;
  int pos = 0;
  while((pos = s.find(t, pos)) != -1) {
    pos++;
    res++;
  }
  return res;
}

data_t operator + (const data_t& a, const data_t& b) {
  int need_left = min(3 - size(a.left), size(b.left));
  int need_right = min(3 - size(b.right), size(a.right));
  return data_t(
      a.res + b.res + count(a.right + b.left, "haha"),
      a.left + b.left.substr(0, need_left),
      a.right.substr(size(a.right) - need_right) + b.right);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  fast_input cin;

  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    static constexpr int N = 50;
    splay_tree<splay_node<string, data_t>, N> st;
    string a;
    while(n--) {
      string op;
      cin >> a >> op;
      if(op == ":=") {
        string s;
        cin >> s;
        int len = min((int)size(s), 3);
        st[a] = data_t(count(s, "haha"), s.substr(0, len), s.substr(size(s) - len));
      } else {
        string s, t;
        cin >> s >> op >> t;
        st[a] = st[s] + st[t];
      }
    }
    cout << st[a].res << nl;
  }

  return 0;
}
