//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

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

ll power(ll n, ll e, ll m) {
  ll r = 1;
  for(;e;e/=2) {
    if(e&1) r = r*n % m;
    n = n*n % m;
  }
  return r;
}

void add(string& s) {
  int carry = 1;
  for(int i=(int)s.size()-1; i>=0; i--) {
    s[i] += carry;
    if(s[i] > '9') {
      s[i] = '0';
      carry = 1;
    } else {
      carry = 0;
    }
  }
  if(carry) s.insert(s.begin(), '1');
}

string sub(string s) {
  int borrow = 1;
  for(int i=(int)s.size()-1; i>=0; i--) {
    s[i] -= borrow;
    if(s[i] < '0') {
      s[i] = '9';
      borrow = 1;
    } else {
      borrow = 0;
    }
  }
  if(s[0] == '0') s = s.substr(1);
  return s;
}

bool match_suffix(const string& t, const string& s, int r) {
  for(int i=0; i<r; i++) {
    int j = (int)t.size() - (r-i);
    if(j<0) return false;
    if(s[i] != t[j]) return false;
  }
  return true;
}

bool match_prefix(const string& t, const string& s, int l) {
  for(int i=l; i-l<t.size() && i<s.size(); i++) {
    if(s[i] != t[i-l]) return false;
  }
  return true;
}

pair<ll,string> solve(const string& s, int t, int len, ll curAns, const string& curBest) {
  int n = s.size();
  string out;
  for(int i=0; i<n-len; i++) {
    out.push_back('0');
  }

  string start = s.substr(t, len);
  string prefix = s.substr(0, t);
  add(prefix);
  int need = len - (int)start.size();
  for(int i=0; i<need; i++) {
    int j = (int)prefix.size() - (need-i);
    assert(j >= 0);
    start.push_back(prefix[j]);
  }
  out += start;
  assert(start.size() == len);
  assert(out.size() == n);

  if(!match_suffix(sub(start), s, t)) return make_pair(-1, out);
  for(int j=t; j<n; j+=len) {
    len = start.size();
    if(!match_prefix(start, s, j)) return make_pair(-1, out);
    add(start);
  }
  return make_pair(t, out);
}

ll answer(int ans, string best) {
  //cerr<<"got [ans, best]: "<<ans<<", "<<best<<nl;
  reverse(best.begin(), best.end());
  while(best.back() == '0') best.pop_back();
  reverse(best.begin(), best.end());
  int n = best.size();
  ll cnt = 1;
  for(int i=0; i<n; i++) {
    int c = best[i] - '0';
    cnt += (ll) n * (c - (i == 0)) * power(10, n-1-i, MOD) % MOD;
    //cerr << "follow: "<< (ll) n * (c - (i == 0)) * power(10, n-1-i, MOD) % MOD << nl;
    if(i > 0) {
      cnt += (ll) 9 * power(10, n-i-1, MOD) * (n-i) % MOD;
      //cerr<<"smaller: "<< (ll) 9 * power(10, n-i-1, MOD) * (n-i) % MOD << nl;
    }
  }
  //cerr<<"cnt: "<<cnt<<nl;
  return (cnt + MOD - ans) % MOD;
}

// TODO
// double-check correctness
// read limits carefully
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  string s;
  cin >> s;
  int n = s.size();

  ll ans = -1;
  string best = "z";
  for(int len=1; len<=n; len++) {
    for(int i=0; i<len; i++) {
      if(s[i] == '0') continue;
      auto [cur, token] = solve(s, i, len, ans, best);
      if(cur != -1 && token < best) {
        best = token;
        ans = cur;
      }
    }
    if(ans != -1) {
      cout << answer(ans, best) << nl;
      return 0;
    }
  }

  assert(ans == -1);
  if(ans == -1) {
    cout << answer(ans, "1" + s) << nl;
  } else {
    cout << answer(ans, best) << nl;
  }

  return 0;
}
