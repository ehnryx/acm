#include <bits/stdc++.h>
using namespace std;

//%:include "utility/defines.h"
//%:include "utility/fast_input.h"
%:include "utility/output.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int testnum = 0;
  for(string s; getline(cin, s); ) {
    istringstream in(s);
    vector<string> all;
    while(in >> s) {
      all.push_back(s);
    }
    reverse(begin(all), end(all));
    vector<string> res;
    for(const string& v : all) {
      if(isalnum(v.back())) {
        res.push_back(v);
      } else {
        assert(res.size() >= 2);
        string first = res.back();
        res.pop_back();
        string second = res.back();
        res.pop_back();
        if(!isdigit(first.back()) || !isdigit(second.back())) {
          res.push_back(second);
          res.push_back(first);
          res.push_back(v);
        } else if(v[0] == '+') {
          res.push_back(to_string(stoi(first) + stoi(second)));
        } else if(v[0] == '-') {
          res.push_back(to_string(stoi(first) - stoi(second)));
        } else if(v[0] == '*') {
          res.push_back(to_string(stoi(first) * stoi(second)));
        } else {
          assert(false);
        }
      }
    }
    reverse(begin(res), end(res));
    cout << "Case " << ++testnum << ": " << res << nl;
  }

  return 0;
}
