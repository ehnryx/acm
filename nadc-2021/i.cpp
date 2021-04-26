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

vector<int> parse_interval(string s) {
  if(s.find('-') != -1) {
    int l = stoi(s.substr(0, s.find('-')));
    int r = stoi(s.substr(s.find('-') + 1));
    vector<int> res(r-l+1);
    iota(begin(res), end(res), l);
    return res;
  } else {
    return {stoi(s)};
  }
}

vector<int> parse_time(string s, int n) {
  if(s == "*") {
    vector<int> res(n);
    iota(begin(res), end(res), 0);
    return res;
  }
  s.push_back(',');
  vector<int> res;
  for(int i=0, j=s.find(','); j!=-1; j=s.find(',', i=j+1)) {
    vector<int> cur = parse_interval(s.substr(i, j - i));
    res.insert(end(res), begin(cur), end(cur));
  }
  return res;
}

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
  int total = 0;
  set<tuple<int,int,int>> have;
  while(n--) {
    string h, m, s;
    cin >> h >> m >> s;
    vector<int> hours = parse_time(h, 24);
    vector<int> minutes = parse_time(m, 60);
    vector<int> seconds = parse_time(s, 60);
    for(int i : hours) {
      for(int j : minutes) {
        for(int k : seconds) {
          have.insert(tuple(i, j, k));
          total++;
        }
      }
    }
  }
  cout << size(have) << " " << total << nl;

  return 0;
}
