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

  const int M = 11;
  map<string, int> to_i;
  to_i["lower"] = 1;
  to_i["middle"] = 2;
  to_i["upper"] = 3;

  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;

    vector<pair<vector<int>, string>> all;
    while (n--) {
      string name, s, junk;
      cin >> name >> s >> junk;
      vector<int> level;
      for (int i = 0; i < s.size(); ) {
        int j = s.find('-', i);
        if(j == -1) j = s.size();
        level.push_back(to_i[s.substr(i, j - i)]);
        i = j + 1;
      }
      reverse(begin(level), end(level));
      level.resize(M, 2);
      name.pop_back();
      all.emplace_back(level, name);
    }

    sort(begin(all), end(all), [](const auto& a, const auto& b) {
      for (int i = 0; i < min(a.first.size(), b.first.size()); i++) {
        if (a.first[i] > b.first[i]) return true;
        else if (a.first[i] < b.first[i]) return false;
      }
      return a.second < b.second;
    });

    for (const auto& [_, s] : all) {
      cout << s << nl;
    }
    cout << string(30, '=') << nl;
  }

  return 0;
}
