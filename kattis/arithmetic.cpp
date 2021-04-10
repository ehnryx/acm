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

  string s;
  cin >> s;

  string bin;
  for(char c : s) {
    bin += bitset<3>(c - '0').to_string();
  }
  reverse(begin(bin), end(bin));
  while(size(bin) % 4) {
    bin.push_back('0');
  }
  if(size(bin) > 4 && bin.substr(size(bin) - 4) == "0000") {
    bin.erase(end(bin) - 4, end(bin));
  }
  reverse(begin(bin), end(bin));

  cout << hex << uppercase;
  for(int i=0; i<size(bin); i+=4) {
    cout << stoi(bin.substr(i, 4), 0, 2);
  }
  cout << nl;

  return 0;
}
