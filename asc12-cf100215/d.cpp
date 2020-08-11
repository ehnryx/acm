//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "eq"

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

#ifdef ONLINE_JUDGE
const int D = 100;
#else
const int D = 5;
#endif

const int N = 4*D + 7;
const int M = 2*D + 2;
int mat[N][M], goal[N], res[M];
bool done[M];

vector<int> readpoly() {
  int n;
  cin >> n;
  vector<int> out(M);
  for(int i=n; i>=0; i--) {
    cin >> out[i];
  }
  return out;
}

void output(vector<int> v) {
  while(!v.empty() && !v.back()) {
    v.pop_back();
  }
  reverse(v.begin(), v.end());
  cout << (int)v.size() - 1 << " ";
  for(int it : v) {
    cout << it << " ";
  }
  cout << nl;
}

bool check(const vector<int>& a, const vector<int>& b, const vector<int>& c, const vector<int>& x, const vector<int>& y) {
  for(int i=0; i<=2*D; i++) {
    int val = c[i];
    for(int j=0; j<=i; j++) {
      if(j<=D && i-j<=D) {
        val ^= x[j] & a[i-j];
        val ^= y[j] & b[i-j];
      }
    }
    if(val) return false;
  }
  return true;
}

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

  vector<int> a1 = readpoly();
  vector<int> b1 = readpoly();
  vector<int> c1 = readpoly();
  vector<int> a2 = readpoly();
  vector<int> b2 = readpoly();
  vector<int> c2 = readpoly();

  for(int i=0; i<=2*D; i++) {
    for(int j=0; j<=i; j++) {
      if(j<=D && i-j<=D) {
        mat[2*i][j] ^= a1[i-j];
        mat[2*i][j+D+1] ^= b1[i-j];
        mat[2*i+1][j] ^= a2[i-j];
        mat[2*i+1][j+D+1] ^= b2[i-j];
      }
    }
    goal[2*i] = c1[i];
    goal[2*i+1] = c2[i];
  }

#ifndef ONLINE_JUDGE
  for(int i=0; i<N; i++) {
    for(int j=0; j<M; j++) {
      cout << mat[i][j] << " ";
    }
    cout << "| " << goal[i] << nl;
  }
#endif

  for(int i=0, s=0; i<M; i++) {
    for(int j=s; j<N; j++) {
      if(mat[j][i]) {
        swap(mat[s], mat[j]);
        swap(goal[s], goal[j]);
        break;
      }
    }
    if(!mat[s][i]) continue;
    for(int j=s+1; j<N; j++) {
      if(!mat[j][i]) continue;
      for(int k=i; k<M; k++) {
        mat[j][k] ^= mat[s][k];
      }
      goal[j] ^= goal[s];
    }
    s++;
  }

  for(int i=N-1; i>=0; i--) {
    int last = -1;
    int val = goal[i];
    for(int j=M-1; j>=0; j--) {
      if(done[j]) {
        val ^= res[j] & mat[i][j];
      } else if(mat[i][j]) {
        last = j;
      }
    }
    if(last != -1) {
      res[last] = val;
      done[last] = true;
    } else if(val) {
      cout << "No solution" << nl;
      return 0;
    }
  }

  vector<int> x(M), y(M);
  for(int i=0; i<=D; i++) {
    x[i] = res[i];
    y[i] = res[i+D+1];
  }
  if(check(a1, b1, c1, x, y) && check(a2, b2, c2, x, y)) {
    output(x);
    output(y);
  } else {
    cout << "No solution" << nl;
  }

  return 0;
}
