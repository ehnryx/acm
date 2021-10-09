#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+9;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ll power(ll b, int e) {
  ll res = 1;
  for ( ; e>0; e/=2) {
    if (e&1) res = res*b % MOD;
    b = b*b % MOD;
  }
  return res;
}

const int N = 5e3+1;
int a[N];
ll dp[N];
ll fact[N], inv[N];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;

  FOR(i,1,n) {
    cin >> a[i];
  }
  sort(a+1, a+1+n);

  fact[0] = 1;
  FOR(i,1,n) {
    fact[i] = i*fact[i-1] % MOD;
    inv[i] = power(i,MOD-2);
  }

  dp[0] = 1;
  FOR(i,1,n) {
    ll bad = 0;
    unordered_map<int,int> cnt;
    ll cur = 1;
    DOWN(j,1,i) {
      bad += dp[j-1] * fact[i-j] % MOD * cur % MOD;
      cur = cur * inv[++cnt[a[j]]] % MOD;
    }
    dp[i] = (fact[i] * cur % MOD - bad % MOD + MOD) % MOD;
  }
  cout << dp[n] << nl;

  return 0;
}
