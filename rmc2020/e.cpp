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

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());



// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n;
  cin >> n;
  vector<int> v(n);
  for(int i=0; i<n; i++) {
    cin >> v[i];
  }
  list<pair<int,int>> cur;
  for(int i=0, cnt=1; i<n; i++) {
    if(i+1 == n || v[i] != v[i+1]) {
      cur.emplace_back(v[i], cnt);
      cnt = 1;
    } else {
      cnt++;
    }
  }

  vector<vector<int>> ans;
  while(cur.size() > 1) {
    vector<int> out;
    vector<list<pair<int,int>>::iterator> rem;
    for(auto it=cur.begin(); it!=cur.end(); it++) {
      int sad = 0;
      sad += (it != cur.begin() && prev(it)->first > it->first);
      sad += (next(it) != cur.end() && next(it)->first > it->first);
      for(int j=0; j<min(sad,it->second); j++) {
        out.push_back(it->first);
      }
      it->second -= sad;
      if(it->second <= 0) {
        rem.push_back(it);
      }
    }
    for(auto it : rem) {
      cur.erase(it);
    }
    for(auto it=next(cur.begin()); it!=cur.end(); it++) {
      if(it->first == prev(it)->first) {
        it->second += prev(it)->second;
        cur.erase(prev(it));
      }
    }
    ans.push_back(move(out));
  }

  cout << ans.size() << nl;
  for(const auto& rem : ans) {
    for(int it : rem) {
      cout << it << " ";
    }
    cout << nl;
  }
  for(const auto& [val, cnt] : cur) {
    for(int j=0; j<cnt; j++) {
      cout << val << " ";
    }
  }
  cout << nl;

  return 0;
}
