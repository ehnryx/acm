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
  int n, L; ld P;
  cin >> n >> L >> P;
  vector<ld> logs, loglogs;
  for(int i=0; i<n; i++) {
    int s;
    cin >> s;
    if(s == 1) continue;
    logs.push_back(log((ld)s));
    loglogs.push_back(log(logs.back()));
  }
  n = size(logs);
  ld logp = log(P);

  ld logl = -1e48;
  ld logr = 0;
  for(int bs=0; bs<199; bs++) {
    ld logm = (logl + logr) / 2;
    ld need = 0;
    for(int i=0; i<n; i++) {
      need += ceil((logm - loglogs[i]) / logp);
    }
    if(need <= L) {
      logr = logm;
    } else {
      logl = logm;
    }
  }

  priority_queue<ld> all;
  for(int i=0; i<n; i++) {
    int need = ceil((logr - loglogs[i]) / logp);
    L -= need;
    all.push(pow(P, need) * logs[i]);
  }
  assert(0 <= L);
  assert(L <= 2 * n);
  while(L--) {
    ld nxt = all.top() * P;
    all.pop();
    all.push(nxt);
  }

  ld ans = 0;
  while(not empty(all)) {
    ans += all.top();
    all.pop();
  }
  cout << exp(-ans) << nl;
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
