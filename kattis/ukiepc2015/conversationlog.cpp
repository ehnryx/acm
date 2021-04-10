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

  string line;
  getline(cin, line);
  int n = stoi(line);
  map<string, vector<string>> say;
  map<string, int> cnt;
  for(int i=0; i<n; i++) {
    getline(cin, line);
    istringstream in(line);
    string name;
    in >> name;
    while(in >> line) {
      say[name].push_back(line);
      cnt[line] += 1;
    }
  }

  vector<string> have;
  for(auto it=say.begin(); it!=say.end(); it++) {
    sort(it->second.begin(), it->second.end());
    auto jt = unique(it->second.begin(), it->second.end());
    if(it == say.begin()) {
      have.insert(have.end(), it->second.begin(), jt);
    } else {
      have.resize(set_intersection(have.begin(), have.end(),
            it->second.begin(), jt, have.begin()) - have.begin());
    }
  }

  if(have.empty()) {
    have.push_back("ALL CLEAR");
  }

  vector<pair<int, string>> order;
  for(string s : have) {
    order.emplace_back(-cnt[s], s);
  }
  sort(order.begin(), order.end());

  for(auto [_, s] : order) {
    cout << s << nl;
  }

  return 0;
}
