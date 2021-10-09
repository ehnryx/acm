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

const int N = 2e5+1;
int val[N], p[N], nxt[N], have[N];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n, k;
  cin >> n >> k;
  unordered_map<string,int> idx;
  vector<pair<int,int>> order;
  for(int i=1; i<=n; i++) {
    string s;
    cin >> s >> val[i];
    if(isdigit(s.back())) {
      if(s.back() == '1') {
        s.pop_back();
        idx[s] = i;
      } else {
        s.pop_back();
        p[i] = idx[s];
        nxt[p[i]] = i;
      }
    }
    order.push_back(make_pair(val[i], i));
  }
  sort(order.begin(), order.end());

  set<pair<int,int>> single, pair;
  ll cur = 0;
  for(int i=0; i<k; i++) {
    cur += val[order[i].second];
    have[order[i].second] = true;
  }
  for(int i=0; i<k; i++) {
    if(p[order[i].second] && !have[p[order[i].second]]) {
      cur += val[p[order[i].second]];
      have[p[order[i].second]] = true;
      pair.insert(make_pair(val[p[order[i].second]], p[order[i].second]));
      single.insert(order[i]);
    } else if(have[nxt[order[i].second]]) {
      pair.insert(order[i]);
    } else {
      single.insert(order[i]);
    }
  }

  while(single.size() + pair.size() > k) {
    assert(!single.empty());
    auto it = prev(single.end());
    cur -= it->first;
    have[it->second] = false;
    if(p[it->second]) {
      pair.erase(make_pair(val[p[it->second]], p[it->second]));
      single.insert(make_pair(val[p[it->second]], p[it->second]));
    }
    single.erase(it);
  }

  ll ans = cur;
  set<tuple<int,int,int>> in;
  set<pii> out;
  for(auto [_,i] : pair) {
    assert(nxt[i]);
    in.insert(make_tuple(val[i] + val[nxt[i]], i, nxt[i]));
  }
  for(int i=1; i<=n; i++) {
    if(!have[i] && (!p[i] || have[p[i]])) {
      out.insert(make_pair(val[i], i));
    }
  }

  while(clock() < 3.7*CLOCKS_PER_SEC) {
    if(in.empty()) break;
    auto it = prev(in.end());
    auto [v, i, j] = *it;
    in.erase(it);
    cur -= v;
    have[i] = have[j] = false;

    out.insert(make_pair(val[i], i));
    int a = out.begin()->second;
    out.erase(out.begin());
    if(nxt[a]) out.insert(make_pair(val[nxt[a]], nxt[a]));
    if(out.empty()) break;
    int b = out.begin()->second;
    out.erase(out.begin());
    if(nxt[b]) out.insert(make_pair(val[nxt[b]], nxt[b]));

    have[a] = have[b] = true;
    cur += val[a] + val[b];
    ans = min(ans, cur);
    if(p[a]) {
      assert(have[p[a]]);
      in.insert(make_tuple(val[p[a]] + val[a], p[a], a));
    }
    if(p[b]) {
      assert(have[p[b]]);
      in.insert(make_tuple(val[p[b]] + val[b], p[b], b));
    }
  }

  cout << ans << nl;

  return 0;
}
