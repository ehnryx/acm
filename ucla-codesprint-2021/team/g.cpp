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

pair<bool,bool> query(int l, int r) {
  assert(l <= r);
  cout << "ASK " << l << " " << r << endl;
  string a, b;
  cin >> a >> b;
  return pair(a == "yes", b == "yes");
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

  int l = 1;
  int r = 500;
  int al, bl, ar, br;
  al = bl = ar = br = -1;
  bool s = false;

  int bs = 0;
  while(bs < 10) {
    bs++; // query
    int m = (l + r) / 2;
    auto [lin, rin] = query(l, m);
    if(lin && rin) {
      r = m;
    } else if(!lin && !rin) {
      l = m + 1;
    } else {
      al = l;
      ar = m;
      bl = m + 1;
      br = r;
      if(rin) s = true; // ???
      break;
    }
  }
  if (al == -1) {
    cout << "GUESS " << r << " " << r << endl;
    return 0;
  }
  assert(al > 0 && bl > 0 && ar > 0 && br > 0);

  while(bs < 10) {
    bs++; // query
    int am = (al + ar) / 2;
    int bm = (bl + br) / 2;
    auto [lin, rin] = query(am + 1, bm);
    if(s) swap(lin, rin);
    if(lin) {
      al = am + 1;
    } else {
      ar = am;
    }
    if(rin) {
      br = bm;
    } else {
      bl = bm + 1;
    }
  }

  assert(al == ar);
  assert(bl == br);
  if(s) swap(ar, br);
  cout << "GUESS " << ar << " " << br << endl;

  return 0;
}
