#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ll egcd(ll a, ll b, ll& x, ll& y) {
  if (!b) { x=1; y=0; return a; }
  ll d = egcd(b,a%b,y,x); y -= x*(a/b); return d;
}

const int N = 1e5+1;
ll fact[N], invf[N];

void init() {
  ll y;
  fact[0] = invf[0] = 1;
  for (int i = 1; i < N; i++) {
    fact[i] = i*fact[i-1] % MOD;
    egcd(fact[i], MOD, invf[i], y);
    if (invf[i] < 0) invf[i] += MOD;
  }
}

ll ncr(int n, int r) {
  return (fact[n] * invf[r] % MOD) * invf[n-r] % MOD;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
  init();

  int T;
  cin >> T;
  while (T--) {
    int a, b;
    cin >> a >> b;
    cout << 2*ncr(a-1, b) % MOD << nl;
  }

  return 0;
}
