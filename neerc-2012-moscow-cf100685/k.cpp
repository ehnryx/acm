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
  string line;
  getline(cin, line);
  string all;
  for(int i=0; i<n; i++) {
    getline(cin, line);
    all += line + " ";
  }
  transform(all.begin(), all.end(), all.begin(), [](char c) {
    return isalpha(c) ? c : ' ';
  });

  cin >> n;
  unordered_set<string> bad;
  for(int i=0; i<n; i++) {
    string s;
    cin >> s;
    transform(s.begin(), s.end(), s.begin(), [](char c) { return tolower(c); });
    bad.insert(s);
  }

  istringstream in(all);
  vector<string> words;
  unordered_map<string,int> cnt;
  unordered_map<string,int> pcnt;
  for(string s; in >> s; ) {
    transform(s.begin(), s.end(), s.begin(), [](char c) { return tolower(c); });
    if(!bad.count(s)) {
      cnt[s]++;
      if(!words.empty()) {
        pcnt[words.back() + "_" + s]++;
      }
      words.push_back(s);
    }
  }
  int m = words.size();

  cin >> n;
  for(int i=0; i<n; i++) {
    string a, b;
    cin >> a >> b;
    transform(a.begin(), a.end(), a.begin(), [](char c) { return tolower(c); });
    transform(b.begin(), b.end(), b.begin(), [](char c) { return tolower(c); });
    ld pairs = (ld) (pcnt[a + "_" + b] + pcnt[b + "_" + a]) / (m-1);
    if(a == b) pairs /= 2;
    ld other = (ld)cnt[a]/m * (ld)cnt[b]/m;
    if(other > 0) {
      cout << pairs / other << nl;
    } else {
      cout << 0 << nl;
    }
  }

  return 0;
}
