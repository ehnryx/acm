//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

bool unary(const string& s) {
  return count(s.begin(), s.end(), '1') == s.size();
}

const vector<pair<char,function<bool(int,int,int)>>> funcs = {
  { '+', [](int a, int b, int c) { return a+b == c; } },
  { '-', [](int a, int b, int c) { return a-b == c; } },
  { '*', [](int a, int b, int c) { return a*b == c; } },
  { '/', [](int a, int b, int c) { return b != 0 && b*c == a; } },
};
map<char,function<bool(int,int,int)>> eval(funcs.begin(), funcs.end());

bool valid(const string& x, int base) {
  for(char c : x) {
    if(isdigit(c) && c-'0' >= base) return false;
    if(isalpha(c) && c-'a'+10 >= base) return false;
  }
  return true;
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int T;
  cin >> T;
  while(T--) {
    string x, y, z;
    char op, eq;
    cin >> x >> op >> y >> eq >> z;
    string ans;
    if(unary(x) && unary(y) && unary(z)) {
      int xval = x.size();
      int yval = y.size();
      int zval = z.size();
      if(eval[op](xval, yval, zval)) {
        ans.push_back('1');
      }
    }
    for(int base=2; base<=36; base++) {
      try {
        if(!valid(x, base)) throw 0;
        if(!valid(y, base)) throw 0;
        if(!valid(z, base)) throw 0;
        int xval = stoi(x, 0, base);
        int yval = stoi(y, 0, base);
        int zval = stoi(z, 0, base);
        if(eval[op](xval, yval, zval)) {
          if(base == 36) {
            ans.push_back('0');
          } else {
            ans.push_back(base<10 ? base+'0' : base-10+'a');
          }
        }
      } catch(...) {
      }
    }
    if(ans.empty()) {
      cout << "invalid" << nl;
    } else {
      cout << ans << nl;
    }
  }

  return 0;
}
