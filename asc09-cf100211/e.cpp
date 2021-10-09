//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "quadratic"

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

const int N = 200;
int deg[3], coeff[3][N];

int mat[N][N], goal[N];

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
///*
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif
//*/

  for(int t=0; t<3; t++) {
    cin >> deg[t];
    for(int j=deg[t]; j>=0; j--) {
      cin >> coeff[t][j];
    }
  }

  for(int i=0; i<N; i++) {
    goal[i] ^= coeff[2][i];
    for(int j=0; j<=i; j++) {
      mat[i][j] ^= coeff[1][i-j];
    }
    for(int j=0; 2*j<=i; j++) {
      mat[i][j] ^= coeff[0][i-2*j];
    }
  }

  for(int t=0; t<N; t++) {
    for(int i=t; i<N; i++) {
      if(mat[i][t]) {
        swap(mat[i], mat[t]);
        swap(goal[i], goal[t]);
        break;
      }
    }
    if(!mat[t][t]) continue;
    for(int i=t+1; i<N; i++) {
      if(!mat[i][t]) continue;
      for(int j=t; j<N; j++) {
        mat[i][j] ^= mat[t][j];
      }
      goal[i] ^= goal[t];
    }
  }

  for(int i=N-1; i>=0; i--) {
    for(int j=i+1; j<N; j++) {
      goal[i] ^= mat[i][j] & goal[j];
    }
    if(!mat[i][i] && goal[i]) {
      cout << "no solution" << nl;
      return 0;
    }
  }

  for(int i=0; i<2*N; i++) {
    int val = 0;
    if(i<N) {
      val ^= coeff[2][i];
    }
    for(int j=0; j<=i; j++) {
      if(j<N && i-j<N) {
        val ^= coeff[1][j] & goal[i-j];
      }
    }
    for(int j=0; j<=i; j++) {
      for(int k=0; k+j<=i; k++) {
        if(j<N && k<N && i-j-k<N) {
          val ^= coeff[0][j] & goal[k] & goal[i-j-k];
        }
      }
    }
    if(val) {
      cout << "no solution" << nl;
      return 0;
    }
  }

  int last = -1;
  for(int i=0; i<N; i++) {
    if(goal[i]) {
      last = i;
    }
  }
  cout << last << "  ";
  for(int i=last; i>=0; i--) {
    cout << goal[i] << " ";
  }
  cout << nl;

  return 0;
}
