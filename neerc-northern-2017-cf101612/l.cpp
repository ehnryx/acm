#include <bits/stdc++.h>
using namespace std;

#define FILENAME "little"

typedef long long ll;
typedef long double ld;
const char nl = '\n';

const ll INFLL = 0x3f3f3f3f3f3f3f3f;

ll mul(ll a, ll b) {
  assert(a>0 && b>0);
  if(a > INFLL/b) return INFLL;
  return a*b;
}

ll power(ll n, int e) {
  ll r = 1;
  for(;e;e/=2) {
    if(e&1) r = mul(r,n);
    n = mul(n,n);
  }
  return r;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  if(fopen(FILENAME ".in", "r")) {
    freopen(FILENAME ".in", "r", stdin);
    freopen(FILENAME ".out", "w", stdout);
  }

  ll n;
  cin >> n;
  if(__builtin_popcountll(n) == 1) {
    cout << -1 << nl;
    return 0;
  }

  set<vector<ll>> ans;
  for(int i=1; i<=60; i++) {
    ld root = pow(n, 1./i);
    for(ll j=max((ld)0,root-421); j<=root+421; j++) {
      if(j<2) continue;
      // if perfect power
      if(power(j,i) == n) {
        vector<ll> cur;
        for(int k=0; k<i; k++) {
          cur.push_back(j);
        }
        ans.insert(move(cur));
      }
      // not perfect power
      for(int ii=0; ii<=i; ii++) {
        if(mul(power(j,ii), power(j-1,i-ii)) == n) {
          vector<ll> cur;
          for(int k=0; k<i-ii; k++) {
            cur.push_back(j-1);
          }
          for(int k=0; k<ii; k++) {
            cur.push_back(j);
          }
          ans.insert(move(cur));
        }
        if(mul(power(j,ii), power(j+1,i-ii)) == n) {
          vector<ll> cur;
          for(int k=0; k<ii; k++) {
            cur.push_back(j);
          }
          for(int k=0; k<i-ii; k++) {
            cur.push_back(j+1);
          }
          ans.insert(move(cur));
        }
      }
    }
  }

  cout << ans.size() << nl;
  for(const auto& row : ans) {
    cout << row.size();
    for(ll it : row) {
      cout << " " << it;
    }
    cout << nl;
  }

  return 0;
}
