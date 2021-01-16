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

  int n, m, add;
  cin >> n >> m >> add;
  map<string,int> have;
  have["Jane Eyre"] = add;

  string line;
  getline(cin, line);
  for(int i=0; i<n; i++) {
    getline(cin, line);
    line = line.substr(1);
    int end = line.find('"');
    string s = line.substr(0, end);
    have[s] = stoi(line.substr(end + 2));
  }

  vector<tuple<int,string,int>> to_add;
  for(int i=0; i<m; i++) {
    getline(cin, line);
    int first = line.find('"');
    int end = line.find('"', first + 1);
    int t = stoi(line.substr(0, first - 1));
    int p = stoi(line.substr(end + 2));
    string s = line.substr(first + 1, end - first - 1);
    to_add.emplace_back(t, s, p);
  }
  sort(to_add.begin(), to_add.end(), greater<tuple<int,string,int>>());

  ll ans = 0;
  while(have.count("Jane Eyre")) {
    while(!to_add.empty() && get<0>(to_add.back()) <= ans) {
      have[get<1>(to_add.back())] = get<2>(to_add.back());
      to_add.pop_back();
    }
    ans += have.begin()->second;
    have.erase(have.begin());
  }
  cout << ans << nl;

  return 0;
}
