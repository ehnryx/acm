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

void sad() {
  cout << 0 << nl;
  exit(0);
}

bool isnumber(const string& s) {
  if(size(s) >= 11) return false;
  for(char c : s) {
    if(!isdigit(c)) return false;
  }
  if(stoll(s) > (int)1e9) return false;
  return true;
}

bool isprime(const string& s) {
  int n = stoi(s);
  if(n < 2) return false;
  for(int i=2; i*i<=n; i++) {
    if(n % i == 0) return false;
  }
  return true;
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

  string a, b, c;
  if(!(cin >> a >> b >> c)) {
    sad();
  }

  if(!isnumber(a)) sad();
  if(!isnumber(b)) sad();
  if(!isnumber(c)) sad();
  if(stoi(a) % 2) sad();
  if(!isprime(b)) sad();
  if(!isprime(c)) sad();
  if(stoi(a) != stoi(b) + stoi(c)) sad();

  if(cin >> a) sad();
  cout << 1 << nl;

  return 0;
}
