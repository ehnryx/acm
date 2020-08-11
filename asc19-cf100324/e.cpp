#pragma GCC optimize("O3")
#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "formula1"

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef double ld;
typedef complex<ld> pt;
#define stold stod

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
///*
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif
//*/

  string s;
  cin >> s;

  vector<string> all;
  bool neg = false;
  for(int i=0; i<s.size(); ) {
    int j = min(s.find("+", i), s.find("-", i));
    if(j == -1) {
      j = s.size();
    }
    if(i != j) {
      all.push_back((neg ? "-" : "") + s.substr(i, j-i));
    }
    i = j + 1;
    neg = (s[j] == '-');
  }

  ld ans = 0;
  map<vector<char>,ld> collect;
  for(string t : all) {
    bool found = false;
    for(int i=0; i<t.size(); i++) {
      if(!isalpha(t[i])) continue;
      found = true;
      vector<char> vars;
      if(i+1 < t.size()) {
        if(t[i+1] == '^') {
          vars = {t[i], t[i]};
        } else {
          vars = {t[i], t[i+1]};
        }
      } else {
        vars = {t[i]};
      }
      string num = t.substr(0, i);
      if(num.empty() || num.back() == '-') {
        num.push_back('1');
      }
      ld coeff = stold(num);
      sort(vars.begin(), vars.end());
      collect[vars] += coeff;
      break;
    }
    if(!found) {
      ans += stold(t);
    }
  }

  vector<ld> coeff;
  vector<vector<char>> vars;
  for(const auto& [v, c] : collect) {
    coeff.push_back(c);
    vars.push_back(v);
  }

  vector<char> letter;
  for(char c : s) {
    if(!isalpha(c)) continue;
    if(find(letter.begin(), letter.end(), c) == letter.end()) {
      letter.push_back(c);
    }
  }
  if(letter.empty()) {
    cout << ans << nl;
    return 0;
  }

  int m = coeff.size();
  function<ld(vector<ld>)> calc = [=](const vector<ld>& v) {
    ld res = 0;
    for(int i=0; i<m; i++) {
      ld cur = coeff[i];
      for(char c : vars[i]) {
        int j = find(letter.begin(), letter.end(), c) - letter.begin();
        cur *= v[j];
      }
      res += cur;
    }
    return res;
  };

  uniform_real_distribution<ld> paul(0, 1);
  int n = letter.size();
  vector<ld> value;
  for(int i=0; i<n; i++) {
    value.push_back(paul(rng));
  }

  vector<ld> steps = {1e-1, 1e-2, 1e-3, 1e-4, 1e-5, 1e-6, 1e-7, 1e-8};
  vector<int> freqs = {20, 200, 2000, 20000, 40000, 2000, 2000, 200};
  int T = steps.size();
  ld cur = calc(value);
  for(int j=0; j<T; j++) {
    ld step = steps[j];
    for(int bs=0; bs<freqs[j]; bs++) {
      vector<ld> to = value;
      ld best = cur;
      for(int i=0; i<2*n; i++) {
        vector<ld> nv = value;
        nv[i/2] += (i%2 ? step : -step);
        if(nv[i/2] < 0 || nv[i/2] > 1) continue;
        ld ncur = calc(nv);
        if(ncur > best) {
          best = ncur;
          to = nv;
        }
      }
      value = to;
      cur = best;
    }
  }

  cout << ans + cur << nl;
  for(int i=0; i<n; i++) {
    cout << letter[i] << "=" << value[i] << nl;
  }

  return 0;
}
