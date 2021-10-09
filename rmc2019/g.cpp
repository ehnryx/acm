//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma")
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
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int M = 1e9+9;
const int O = 1e9+7;
const int P = 101;
const int Q = 1789;
const int N = 1e6 + 1;
string s[N];
vector<ll> hs[N], os[N];

ll power(ll n, ll e, ll m) {
  ll r = 1;
  for(;e;e/=2) {
    if(e&1) r = r*n % m;
    n = n*n % m;
  }
  return r;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;
  set<pair<ll,ll>> all;
  for(int i=0; i<n; i++) {
    cin >> s[i];
    int len = s[i].size();
    hs[i].resize(len+1);
    os[i].resize(len+1);
    ll cp = 1;
    ll op = 1;
    for(int j=0; j<len; j++) {
      hs[i][j+1] = (hs[i][j] + cp * s[i][j]) % M;
      os[i][j+1] = (os[i][j] + op * s[i][j]) % O;
      cp = cp * P % M;
      op = op * Q % O;
    }
    all.insert(make_pair(hs[i][len], os[i][len]));
  }

  ll invp = power(P, M-2, M);
  ll invq = power(Q, O-2, O);
  vector<string> ans;
  for(int i=0; i<n; i++) {
    int len = s[i].size();
    for(int j=0; j<len; j++) {
      ll cur = hs[i][j] + (hs[i][len] - hs[i][j+1]) * invp;
      ll cor = os[i][j] + (os[i][len] - os[i][j+1]) * invq;
      cur = (cur % M + M) % M;
      cor = (cor % O + O) % O;
      if(all.count(make_pair(cur, cor))) {
        ans.push_back(s[i]);
        break;
      }
    }
  }

  if(ans.empty()) {
    cout << "NO TYPOS" << nl;
  } else {
    for(const string& t : ans) {
      cout << t << nl;
    }
  }

  return 0;
}
