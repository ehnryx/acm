//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

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



// TODO
// double-check correctness
// read limits carefully
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(11);

  const int M = 20;
  ld ncr[M][M];
  for(int i=0; i<M; i++) {
    ncr[i][0] = ncr[i][i] = 1;
    for(int j=1; j<i; j++) {
      ncr[i][j] = ncr[i-1][j] + ncr[i-1][j-1];
    }
  }

  for(ld p; cin >> p && p > -0.1; ) {
    ld game = 0;
    for(int i=0; i<=2; i++) {
      game += powl(p, 4) * powl(1-p, i) * ncr[4+i-1][i];
    }
    game += powl(p, 3+2) * powl(1-p, 3) * ncr[6][3] / (1 - p*(1-p)*2);

    ld tiebreak = 0;
    for(int i=0; i<=5; i++) {
      tiebreak += powl(p, 7) * powl(1-p, i) * ncr[7+i-1][i];
    }
    tiebreak += powl(p, 6+2) * powl(1-p, 6) * ncr[12][6] / (1 - p*(1-p)*2);

    ld set = 0;
    for(int i=0; i<=4; i++) {
      set += powl(game, 6) * powl(1-game, i) * ncr[6+i-1][i];
    }
    set += powl(game, 7) * powl(1-game, 5) * ncr[10][5];
    set += powl(game, 6) * powl(1-game, 6) * ncr[10][5] * 2 * tiebreak;

    ld match = 0;
    match += powl(set, 2);
    match += powl(set, 2) * powl(1-set, 1) * 2;

    cout << game << " " << set << " " << match << nl;
    //cerr<<"tiebreak: "<<tiebreak<<nl;
    //cerr<<endl;
  }

  return 0;
}
