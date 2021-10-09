#include <iostream>
#include <iomanip>
#include <cassert>
#include <algorithm>
#include <cstring>
#include <vector>
#include <map>
#include <queue>
#include <random>
#include <chrono>
#include <utility>
using namespace std;

typedef long long ll;
typedef long double ld;

const char nl = '\n';
const ll MOD = 1e9+7;

mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
  os<<"[ "; for(T it:v) { os<<it<<", "; }
  return os<<"]";
}

ll power(ll n, ll e) {
  ll r = 1;
  for(;e;e/=2) {
    if(e&1) r = r*n % MOD;
    n = n*n % MOD;
  }
  return r;
}

ll inv(ll n) {
  return power(n, MOD-2);
}

ll query(ll v) {
  cout<<"ask "<<v<<endl;
  ll res;
  cin>>res;
  return res;
}

void answer(ll v) {
  cout<<"degree "<<v<<endl;
  return;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout<<fixed<<setprecision(13);

  vector<ll> p;
  while(p.size()<13) {
    ll v = rng()%MOD;
    bool ok = true;
    for(ll j=2;j*j<=v;j++) {
      if(v%j==0) {
        ok = false;
        break;
      }
    }
    if(ok) p.push_back(v);
  }

  ll pts[13];
  auto valid = [&](int d) -> bool {
    vector<ll> a[d+1];
    ll g[d+1];
    for(int i=0;i<=d;i++) {
      ll x = 1;
      for(int j=0;j<=d;j++) {
        a[i].push_back(x);
        x = x*p[i] % MOD;
      }
      g[i] = pts[i];
    }

    for(int t=0;t<=d;t++) {
      int piv = -1;
      for(int i=t;i<=d;i++) {
        if(a[i][t]) {
          piv = i;
          break;
        }
      }
      if(piv==-1) assert(false);
      swap(a[piv],a[t]);
      swap(g[piv],g[t]);
      for(int i=t+1;i<=d;i++) {
        ll r = a[i][t]*inv(a[t][t]) % MOD;
        for(int j=t;j<=d;j++) {
          a[i][j] = (a[i][j] + MOD - r*a[t][j] % MOD) % MOD;
        }
        g[i] = (g[i] + MOD - r*g[t] % MOD) % MOD;
      }
    }

    ll r[d+1];
    for(int i=d;i>=0;i--) {
      ll cur = g[i];
      for(int j=d;j>i;j--) {
        cur = (cur + MOD - a[i][j]*r[j] % MOD) % MOD;
      }
      r[i] = cur * inv(a[i][i]) % MOD;
    }

    for(int t=11;t<13;t++) {
      ll cur = 0;
      ll x = 1;
      for(int i=0;i<=d;i++) {
        cur += r[i]*x % MOD;
        x = x*p[t] % MOD;
      }
      if(cur % MOD != pts[t]) return false;
    }
    return true;
  };

  pts[11] = query(p[11]);
  pts[12] = query(p[12]);
  for(int i=0;i<=10;i++) {
    pts[i] = query(p[i]);
    if(valid(i)) {
      answer(i);
      return 0;
    }
  }

  return 0;
}
