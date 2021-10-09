#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

int inverse(ll n) {
  ll res = 1;
  for (int e=MOD-2; e>0; e/=2) {
    if (e&1) res = res*n % MOD;
    n = n*n % MOD;
  }
  return res;
}

const int N = 1<<19;
ll t[2*N], b[2*N], dt[2*N], db[2*N];

void build() {
  for (int i=N-1; i>0; i--) {
    t[i] = t[2*i] * t[2*i+1] % MOD;
    b[i] = b[2*i] | b[2*i+1];
  }
}

void push(int i) {
  if (db[i]) {
    t[2*i] = t[2*i]*dt[i] % MOD;
    dt[2*i] = dt[2*i]*dt[i] % MOD;
    b[2*i] |= db[i];
    db[2*i] |= db[i];
    t[2*i+1] = t[2*i+1]*dt[i] % MOD;
    dt[2*i+1] = dt[2*i+1]*dt[i] % MOD;
    b[2*i+1] |= db[i];
    db[2*i+1] |= db[i];
    db[i] = 0;
    dt[i] = 1;
  }
}

void pull(int i) {
  t[i] = t[2*i] * t[2*i+1] % MOD;
  b[i] = b[2*i] | b[2*i+1];
}

void update(int l, int r, int v, ll bm, int i, int s, int e) {
  if (r<s || e<l) return;
  if (l<=s && e<=r) {
    t[i] = t[i]*v % MOD;
    dt[i] = dt[i]*v % MOD;
    b[i] |= bm;
    db[i] |= bm;
    return;
  }
  push(i);
  int m = (s+e)/2;
  update(l, r, v, bm, 2*i, s, m);
  update(l, r, v, bm, 2*i+1, m+1, e);
  pull(i);
}

pair<ll,ll> query(int l, int r, int i, int s, int e) {
  if (r<s || e<l) return { 1, 0 };
  if (l<=s && e<=r) {
    return { t[i], b[i] };
  }
  push(i);
  int m = (s+e)/2;
  ll lv, rv, lb, rb;
  tie(lv,lb) = query(l, r, 2*i, s, m);
  tie(rv,rb) = query(l, r, 2*i+1, m+1, e);
  return { lv*rv % MOD, lb|rb };
}

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  vector<int> primes, invp;
  for (int i=2; i<300; i++) {
    bool ok = true;
    for (int j=2; j<i; j++) {
      if (i%j == 0) {
        ok = false;
        break;
      }
    }
    if (ok) {
      primes.push_back(i);
      invp.push_back(inverse(i));
    }
  }
  int sz = primes.size();

  fill(t, t+2*N, 1);
  fill(dt, dt+2*N, 1);

  int n, q;
  cin >> n >> q;

  for (int i=1; i<=n; i++) {
    cin >> t[i+N];
    for (int j=0; j<sz; j++) {
      if (t[i+N]%primes[j] == 0) {
        b[i+N] |= 1LL<<j;
      }
    }
  }
  build();

  for (int l, r, x; q--; ) {
    string s;
    cin >> s;
    if (s == "MULTIPLY") {
      cin >> l >> r >> x;
      ll bm = 0;
      for (int i=0; i<sz; i++) {
        if (x%primes[i] == 0) {
          bm |= 1LL<<i;
        }
      }
      update(l, r, x, bm, 1, 0, N-1);
    } else {
      cin >> l >> r;
      ll res, bm;
      tie(res, bm) = query(l, r, 1, 0, N-1);
      for (int i=0; i<sz; i++) {
        if (bm&1LL<<i) {
          res = (res*(primes[i]-1) % MOD) * invp[i] % MOD;
        }
      }
      cout << res << nl;
    }
  }

  return 0;
}
