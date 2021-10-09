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


const int M = 1e6+2;
vector<pii> start[M], last[M];

const int N = 3e5+1;
vector<int> adj[N];
int par[N];
int cost[N];
multiset<ll> vals[N];

void solve(int u) {
  int best = 0;
  int second = 0;
  int child = -1;
  for(int v:adj[u]) {
    solve(v);
    if(vals[v].size() > best) {
      second = best;
      best = vals[v].size();
      child = v;
    } else if(vals[v].size() > second) {
      second = vals[v].size();
    }
  }

  if(child != -1) {
    swap(vals[u], vals[child]);
    vector<ll> big;
    for(int i=0; i<second; i++) {
      auto it = prev(vals[u].end());
      big.push_back(*it);
      vals[u].erase(it);
    }
    for(int v:adj[u]) {
      if(v == child) continue;
      int i = 0;
      for(auto it=vals[v].rbegin(); it!=vals[v].rend(); it++) {
        big[i++] += *it;
      }
    }
    for(const ll& v:big) {
      vals[u].insert(v);
    }
  }
  if(cost[u]) {
    vals[u].insert(cost[u]);
  }
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;
  for(int i=0; i<n; i++) {
    int s, e;
    cin >> s >> e >> cost[i];
    start[s].push_back(pii(e,i));
    last[e].push_back(pii(s,i));
  }

  int cur = n;
  for(int i=0; i<M; i++) {
    sort(last[i].begin(), last[i].end(), greater<pii>());
    for(pii it:last[i]) {
      cur = par[it.second];
    }
    sort(start[i].begin(), start[i].end(), greater<pii>());
    for(int j=0; j<start[i].size(); j++) {
      if(j == 0) par[start[i][j].second] = cur;
      else par[start[i][j].second] = start[i][j-1].second;
    }
    if(!start[i].empty()) {
      cur = start[i].back().second;
    }
  }

  for(int i=0; i<n; i++) {
    //cerr<<i<<" <- "<<par[i]<<nl;
    adj[par[i]].push_back(i);
  }

  solve(n);
  const auto& res = vals[n];
  ll ans = 0;
  for(auto it=res.rbegin(); it!=res.rend(); it++) {
    ans += *it;
    cout << ans << nl;
  }
  for(int i=res.size(); i<n; i++) {
    cout << ans << nl;
  }

  return 0;
}
