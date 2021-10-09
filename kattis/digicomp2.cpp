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
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  ll n,m;
  cin>>n>>m;
  char t[m+1];
  int a[m+1],b[m+1];
  vector<ll> cnt(m+1);
  vector<int> deg(m+1);
  for(int i=1;i<=m;i++) {
    cin>>t[i]>>a[i]>>b[i];
    deg[a[i]]++;
    deg[b[i]]++;
  }

  queue<int> tod;
  cnt[1] = n;
  for(int i=0;i<=m;i++) {
    if(deg[i]==0) {
      tod.push(i);
    }
  }
  while(!tod.empty()) {
    int u = tod.front();
    tod.pop();
    if(u==0) continue;
    cnt[a[u]] += cnt[u]/2;
    cnt[b[u]] += cnt[u]/2;
    if(cnt[u]%2 == 1) {
      if(t[u]=='L') {
        t[u] = 'R';
        cnt[a[u]]++;
      } else {
        t[u] = 'L';
        cnt[b[u]]++;
      }
    }
    if(--deg[a[u]] == 0) {
      tod.push(a[u]);
    }
    if(--deg[b[u]] == 0) {
      tod.push(b[u]);
    }
  }

  for(int i=1;i<=m;i++) {
    cout<<t[i];
  }
  cout<<nl;

  return 0;
}
