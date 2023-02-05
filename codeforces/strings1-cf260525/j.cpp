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
  int n;
  cin >> n;
  static constexpr int M = 26;
  vector<int> length(M);
  for(int i=0; i<n; i++) {
    string s;
    cin >> s;
    vector<int> cur(M);
    int prefix = 0;
    int suffix = 0;
    for(int j=0, have=0; j<size(s); j++) {
      have++;
      if(j+1 == size(s) or s[j] != s[j+1]) {
        cur[s[j] - 'a'] = max(cur[s[j] - 'a'], have);
        if(prefix == 0) prefix = have;
        suffix = have;
        have = 0;
      }
    }
    vector<int> nxt = cur;
    if(length[s.front() - 'a']) {
      nxt[s.front() - 'a'] = max(nxt[s.front() - 'a'], 1 + prefix);
    }
    if(length[s.back() - 'a']) {
      if(s.front() != s.back()) {
        nxt[s.back() - 'a'] = max(nxt[s.back() - 'a'], 1 + suffix);
      } else {
        nxt[s.back() - 'a'] = max(nxt[s.back() - 'a'], 1 + suffix + prefix);
      }
    }
    if(prefix == size(s)) {
      nxt[s.back() - 'a'] = max<int>(nxt[s.back() - 'a'], (length[s.back() - 'a'] + 1) * (size(s) + 1) - 1);
    }
    for(int j=0; j<26; j++) {
      if(length[j]) {
        nxt[j] = max(nxt[j], 1);
      }
    }
    length = nxt;
  }

  cout << *max_element(begin(length), end(length)) << nl;
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
