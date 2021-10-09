#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef __int128 lll;
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const lll one = 1;
const ll mask = ~0LL;

const int N = 1<<19;
vector<int> adj[N];
int col[N],sz[N],pre[N];

int prid = 0;
int build(int u) {
  sz[u] = 1;
  pre[u] = prid++;
  for(int v:adj[u]) {
    sz[u] += build(v);
  }
  return sz[u];
}

lll st[2*N];
void update(int x, lll v) {
  st[x+=N] = v;
  for(x/=2;x;x/=2) {
    st[x] = st[2*x]^st[2*x+1];
  }
}
lll query(int l, int r) {
  lll res = 0;
  for(l+=N,r+=N;l<r;l/=2,r/=2) {
    if(l&1) res ^= st[l++];
    if(r&1) res ^= st[--r];
  }
  return res;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n,m;
  cin>>n>>m;
  for(int i=1;i<=n;i++) {
    cin>>col[i];
  }
  for(int i=2;i<=n;i++) {
    int par;
    cin>>par;
    adj[par].push_back(i);
  }
  build(1);
  for(int i=1;i<=n;i++) {
    update(pre[i],one<<col[i]);
  }

  for(int i=0;i<m;i++) {
    int t,x;
    cin>>t>>x;
    if(t==0) {
      lll res = query(pre[x], pre[x]+sz[x]);
      cout<<__builtin_popcountll(res&mask)+__builtin_popcountll(res>>64)<<nl;
    } else {
      update(pre[x],one<<t);
    }
  }

  return 0;
}
