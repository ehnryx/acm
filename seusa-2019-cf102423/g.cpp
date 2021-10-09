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
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 11092019;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Bucket {
  vector<int> val;
  vector<ll> sum;
  Bucket() {
    val.push_back(-INF);
    sum.push_back(0);
  }
  bool operator < (int x) const {
    return -val.back() < x;
  }
  friend bool operator < (int x, const Bucket& v) {
    return x < -v.val.back();
  }
  void insert(int v, ll cnt) {
    ll nxt = (sum.back() + cnt) % MOD;
    sum.push_back(nxt);
    val.push_back(-v);
  }
  void pop() {
    val.pop_back();
    sum.pop_back();
  }
  ll query(int v) const {
    int suf = lower_bound(val.begin(), val.end(), -v) - val.begin();
    assert(suf>0);
    return (sum.back() + MOD - sum[suf-1]) % MOD;
  }
};

const int N = 1e6+2;
vector<int> adj[N];
int val[N], p[N];
ll ans[N];
int maxlen = 0;

Bucket lis[N];
void solve(int u) {
  int i = upper_bound(lis, lis+N, val[u]) - lis;
  assert(i>0 && i<N);
  ll cnt = lis[i-1].query(val[u]);
  lis[i].insert(val[u], cnt);
  ans[i] += cnt;
  maxlen = max(maxlen, i);
  for(int v:adj[u]) {
    solve(v);
  }
  lis[i].pop();
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin>>n;
  for(int i=1;i<=n;i++) {
    cin>>val[i];
  }
  for(int i=2;i<=n;i++) {
    cin>>p[i];
    adj[p[i]].push_back(i);
  }

  fill(lis,lis+N,Bucket());
  lis[0].insert(-1, 1);
  solve(1);
  ll out = (ans[maxlen]%MOD + MOD) % MOD;
  cout<<maxlen<<" "<<out<<nl;

  return 0;
}
