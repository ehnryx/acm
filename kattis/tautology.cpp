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
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



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

  for(string s; cin >> s && s != "0"; ) {
    reverse(s.begin(), s.end());
    vector<bool> have(2);
    for(int bm=0; bm<1<<5; bm++) {
      stack<bool> stk;
      for(char c : s) {
        if(islower(c)) {
          stk.push(bm >> (c - 'p') & 1);
        } else if(c == 'N') {
          stk.top() = !stk.top();
        } else {
          bool tmp = stk.top();
          stk.pop();
          if(c == 'K') {
            stk.top() &= tmp;
          } else if(c == 'A') {
            stk.top() |= tmp;
          } else if(c == 'E') {
            stk.top() = (stk.top() == tmp);
          } else {
            stk.top() |= !tmp;
          }
        }
      }
      have[stk.top()] = true;
    }
    if(have[0]) {
      cout << "not" << nl;
    } else {
      cout << "tautology" << nl;
    }
  }

  return 0;
}
