#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

void parse(int& pos, int& neg, string it) {
  if(it[0] == '~') {
    neg |= 1 << (stoi(it.substr(2)) - 1);
  } else {
    pos |= 1 << (stoi(it.substr(1)) - 1);
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int T;
  cin >> T;
  while(T--) {
    int n, m;
    cin >> n >> m;
    string line;
    getline(cin, line);
    vector<pair<int, int>> bms;
    for(int i=0; i<m; i++) {
      getline(cin, line);
      istringstream in(line);
      int pos = 0;
      int neg = 0;
      in >> line;
      parse(pos, neg, line);
      while(in >> line) {
        in >> line;
        parse(pos, neg, line);
      }
      bms.emplace_back(pos, neg);
    }

    bool ok = false;
    for(int bm=0; bm<1<<n && !ok; bm++) {
      bool cur = true;
      for(auto [pos, neg] : bms) {
        cur &= ((pos & bm) || (neg & ~bm));
      }
      ok |= cur;
    }

    cout << (ok ? "" : "un") << "satisfiable" << nl;
  }

  return 0;
}
