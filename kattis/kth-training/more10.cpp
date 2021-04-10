//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n;
  cin >> n;

  vector<pair<int,int>> same, diff;
  unordered_map<string,int> idx;
  int sid = 0;

  function<vector<int>(string)> generate = [&](string t) -> vector<int> {
    if(t.size() == 3) {
      if(!idx.count(t)) idx[t] = sid++;
      return {idx[t]};
    }
    vector<int> out;
    for(char c='a'; c<='z'; c++) {
      vector<int> cur = generate(string(1, c) + t);
      out.insert(out.end(), cur.begin(), cur.end());
    }
    return out;
  };

  function<void(string)> group = [&](string s) {
    if(!idx.count(s)) idx[s] = sid++;
    string t = (s.size() > 3 ? s.substr(s.size() - 3) : s);
    for(int v : generate(t)) {
      same.emplace_back(idx[s], v);
    }
  };

  for(int i=0; i<n; i++) {
    string a, b, op;
    cin >> a >> op >> b;
    if(!idx.count(a)) idx[a] = sid++;
    if(!idx.count(b)) idx[b] = sid++;
    group(a);
    group(b);
    if(op == "is") {
      same.emplace_back(idx[a], idx[b]);
    } else {
      diff.emplace_back(idx[a], idx[b]);
    }
  }

  vector<int> dsu(sid, -1);
  function<int(int)> find = [&](int i) {
    if(dsu[i] == -1) return i;
    return dsu[i] = find(dsu[i]);
  };
  function<void(int,int)> link = [&](int i, int j) {
    i = find(i); j = find(j);
    if(i == j) return;
    dsu[i] = j;
  };

  for(auto [a, b] : same) {
    link(a, b);
  }

  for(auto [a, b] : diff) {
    if(find(a) == find(b)) {
      cout << "wait what?" << nl;
      return 0;
    }
  }

  cout << "yes" << nl;

  return 0;
}
