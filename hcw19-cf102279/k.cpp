#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// DON'T USE THESE MACROS DURING ICPC PRACTICE
#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
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

ll inv(ll n) {
  ll r = 1;
  for(int e=MOD-2;e;e/=2) {
    if(e&1) r = r*n % MOD;
    n = n*n % MOD;
  }
  return r;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  const int N = 1e4+1;
  vector<int> pr;
  for(int i=2;i<N;i++) {
    bool ok = true;
    for(int j=2;j<i;j++) {
      if(i%j==0) ok = false;
    }
    if(ok) pr.push_back(i);
  }

  int n;
  cin>>n;
  int ans[n+1];
  memset(ans, -1, sizeof ans);

  if(n<5) {
    ll p[n+1];
    for(int i=2;i<=n;i++) {
      cout << "? " << 1 << " " << i << endl;
      cin>>p[i];
      assert(p[i]!=-1);
    }
    for(int i=0;i<pr.size();i++) {
      for(int j=0;j<i;j++) {
        if((ll)pr[i]*pr[j]%MOD == p[2]) {
          ans[1] = pr[j];
          ans[2] = pr[i];
          assert(ans[1]<ans[2]);
        }
      }
    }
    for(int i=3;i<=n;i++) {
      ans[i] = p[i] * inv(p[i-1]) % MOD;
    }
  }

  else {
    ll p[n+2], s[n+2];
    p[0] = s[n+1] = 1;
    for(int i=(n+1)/2;i<=n;i++) {
      cout << "? " << 1 << " " << i << endl;
      cin>>p[i];
      assert(p[i]!=-1);
    }
    for(int i=(n+1)/2;i>1;i--) {
      cout<< "? " << i << " " << n << endl;
      cin>>s[i];
      assert(s[i]!=-1);
    }
    for(int i=1;i<(n+1)/2;i++) {
      ans[i] = p[n] * inv(s[i+1] * p[i-1] % MOD) % MOD;
      p[i] = p[i-1] * ans[i] % MOD;
    }
    for(int i=n;i>(n+1)/2;i--) {
      ans[i] = p[n] * inv(p[i-1] * s[i+1] % MOD) % MOD;
      s[i] = s[i+1] * ans[i] % MOD;
    }
    int cnt = 0;
    for(int i=1;i<=n;i++) {
      if(ans[i]==-1) {
        ans[i] = p[n] * inv(p[i-1] * s[i+1] % MOD) % MOD;
        cnt++;
      }
    }
    assert(cnt<=1);
  }

  cout<<"! ";
  for(int i=1;i<=n;i++) {
    cout<<ans[i]<<" ";
  }
  cout << endl;

  return 0;
}
