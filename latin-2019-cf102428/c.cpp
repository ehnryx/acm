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

const int N = 1e5+1;
int a[N];
vector<int> last[N];
vector<pii> start[N];
ll value[N], ans[N];

int dsu[N];
int find(int i) {
  if(dsu[i]==-1) return i;
  return dsu[i] = find(dsu[i]);
}
void link(int i, int j) {
  //cerr<<"merging "<<i<<" into "<<j<<nl;
  if(find(i)!=find(j)) dsu[find(i)] = find(j);
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  memset(dsu, -1, sizeof dsu);

  int n, L, U;
  cin >> n >> L >> U;

  for(int i=1; i<=n; i++) {
    cin >> a[i];
  }

  int m;
  cin >> m;
  for(int i=0; i<m; i++) {
    int s,t,x;
    cin >> s >> t >> x;
    last[t].push_back(i);
    start[s].push_back(make_pair(i,x));
  }

  ll offset = 0;
  map<ll,int> vals;

  auto update = [&](int i, ll v) {
    if(vals.count(v)) {
      link(i, vals[v]);
    } else {
      vals[v] = i;
      value[i] = v;
    }
  };

  for(int i=1; i<=n; i++) {
    //cerr<<"@ time "<<i<<nl;
    for(pii it:start[i]) {
      ll v = it.second - offset;
      update(it.first, v);
      //cerr<<"init "<<it.first<<" w/ value "<<v<<nl;
    }

    offset += a[i];
    //cerr<<"offset set to "<<offset<<nl;
    if(!vals.empty() && vals.begin()->first + offset < L) {
      int g = vals.begin()->second;
      while(!vals.empty() && vals.begin()->first + offset < L) {
        link(vals.begin()->second, g);
        vals.erase(vals.begin());
      }
      update(g, L - offset);
    }
    if(!vals.empty() && vals.rbegin()->first + offset > U) {
      int g = vals.rbegin()->second;
      while(!vals.empty() && vals.rbegin()->first + offset > U) {
        link(vals.rbegin()->second, g);
        vals.erase(prev(vals.end()));
      }
      update(g, U - offset);
    }

    for(int j:last[i]) {
      ans[j] = value[find(j)] + offset;
      //cerr<<"setting ans for "<<j<<" -> read value "<<find(j)<<nl;
    }
  }

  for(int i=0; i<m; i++) {
    cout << ans[i] << nl;
  }

  return 0;
}
