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


//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, m;
  cin >> n >> m;
  vector<int> total(n);
  for(int i=0; i<n; i++) {
    cin >> total[i];
  }
  sort(begin(total), end(total), greater<>());

  vector<int> have = total;
  vector<bool> good(n, true);

  int q;
  cin >> q;
  queue<int> todo;

  vector<int> last;
  for(int round=1; round<=q; round++) {
    if(round % m == 0) {
      for(int i=0; i<n; i++) {
        if(have[i] == 0) {
          //cerr << "HEAL " << i << nl;
          have[i] = total[i] / 2;
          break;
        }
      }
    }

    vector<int> cur;

    string t;
    cin >> t;
    if(t == "APPROACH") {
      int v;
      cin >> v;
      todo.push(v);
    }

    else {
      int need = todo.front();
      todo.pop();
      //cerr << "ATTACK ! " << need << nl;

      while(need > 0) {
        int use = -1;
        for(int i=0; i<n; i++) {
          if(good[i] and (use == -1 or have[i] > have[use])) {
            use = i;
          }
        }
        if(use == -1 or have[use] == 0) {
          return void(cout << "overrun" << nl);
        }

        int atk = min(need, have[use]);
        //cerr << "USE " << use << " -> " << have[use] << " " << need << nl;
        need -= atk;
        have[use] -= atk;
        good[use] = false;
        cur.push_back(use);
      }
    }

    for(int i : last) {
      good[i] = true;
    }
    last = cur;
  }

  cout << "success" << nl;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int T = 1;
#ifdef MULTI_TEST
  cin >> T;
#endif
  for(int testnum=1; testnum<=T; testnum++) {
    solve_main(testnum, cin);
  }

  return 0;
}
