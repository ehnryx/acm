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

const int MAXM = 15;
const int MAXN = 13;

void pivot(int m,int n,ld a[MAXM][MAXN],
           int B[MAXM],int N[MAXN],int r,int c) {
  int i,j; swap(N[c], B[r]); a[r][c]=1/a[r][c];
  for(j=0;j<=n;j++) if(j!=c) a[r][j]*=a[r][c];
  for(i=0;i<=m;i++) if(i!=r) {
    for(j=0;j<=n;j++) if(j!=c) a[i][j]-=a[i][c]*a[r][j];
    a[i][c] = -a[i][c]*a[r][c]; } }
int feasible(int m,int n,ld a[MAXM][MAXN],int B[MAXM],int N[MAXN]) {
  int r,c,i; ld p,v;
  while(1) {
    for(p=INF,i=0; i<m; i++) if(a[i][n]<p) p=a[r=i][n];
    if(p>-EPS) return 1;
    for(p=0,i=0; i<n; i++) if(a[r][i]<p) p=a[r][c=i];
    if(p>-EPS) return 0;
    p = a[r][n]/a[r][c];
    for(i=r+1; i<m; i++) if(a[i][c]>EPS) {
      v = a[i][n]/a[i][c];
      if(v<p) r=i,p=v; }
    pivot(m,n,a,B,N,r,c); } }
int simplex(int m,int n,ld a[MAXM][MAXN],ld b[MAXN],ld& ret) {
  int B[MAXM],N[MAXN],r,c,i; ld p,v;
  for(i=0; i<n; i++) N[i]=i;
  for(i=0; i<m; i++) B[i]=n+i;
  if(!feasible(m,n,a,B,N)) return 0;
  while(1) {
    for(p=0,i=0; i<n; i++) if(a[m][i]>p) p=a[m][c=i];
    if(p<EPS) {
      for(i=0; i<n; i++) if(N[i]<n) b[N[i]]=0;
      for(i=0; i<m; i++) if(B[i]<n) b[B[i]]=a[i][n];
      ret = -a[m][n];
      return 1; }
    for(p=INF,i=0; i<m; i++) if(a[i][c]>EPS) {
      v = a[i][n]/a[i][c];
      if(v<p) p=v,r=i; }
    if(p==INF) return -1;
    pivot(m,n,a,B,N,r,c); }
}

ld a[MAXM][MAXN];
ld b[MAXN];
ld ret;

// O Paul, heed my prayers
void solve() {
  fill(&a[0][0], &a[0][0]+MAXM*MAXN, 0);

  int A, B;
  cin >> A >> B;

  // set PA
  a[0][5] = 1;
  a[0][MAXN-1] = A;
  a[1][5] = -1;
  a[1][MAXN-1] = -A;

  // set PB
  a[2][11] = 1;
  a[2][MAXN-1] = B;
  a[3][11] = -1;
  a[3][MAXN-1] = -B;

  // read costs
  cin >> a[MAXM-1][1] >> a[MAXM-1][2]; // open A
  cin >> a[MAXM-1][7] >> a[MAXM-1][8]; // open B
  cin >> a[MAXM-1][3] >> a[MAXM-1][9]; // close AB
  cin >> a[MAXM-1][4]; // convert AB
  a[MAXM-1][10] = a[MAXM-1][4]; // convert AB
  for(int i=0; i<MAXM-1; i++) {
    a[MAXM-1][i] *= -1;
  }

  int start;
  cin >> start;

  // set init A
  a[4][0] = 1;
  a[4][MAXN-1] = (start == 1);
  a[5][0] = -1;
  a[5][MAXN-1] = -(start == 1);

  // set init B
  a[6][6] = 1;
  a[6][MAXN-1] = (start == 2);
  a[7][6] = -1;
  a[7][MAXN-1] = -(start == 2);

  // set type A eq
  a[8][1] = a[8][0] = a[8][10] = 1;
  a[8][4] = a[8][3] = a[8][5] = -1;
  a[8][2] = 2;
  a[9][1] = a[9][0] = a[9][10] = -1;
  a[9][4] = a[9][3] = a[9][5] = 1;
  a[9][2] = -2;

  // set type B eq
  a[10][7] = a[10][6] = a[10][4] = 1;
  a[10][10] = a[10][9] = a[10][11] = -1;
  a[10][8] = 2;
  a[11][7] = a[11][6] = a[11][4] = -1;
  a[11][10] = a[11][9] = a[11][11] = 1;
  a[11][8] = -2;

  if(start == 1 && B > 0) {
    a[12][4] = -1;
    a[12][MAXN-1] = -1;
  }

  if(start == 2 && A > 0) {
    a[13][10] = -1;
    a[12][MAXN-1] = -1;
  }

  cerr << "feasible? " << simplex(MAXM-1, MAXN-1, a, b, ret) << nl;
  for(int i=0; i<MAXN-1; i++) {
    cerr << fixed << setprecision(2) << b[i] << "   ";
  }
  cerr << nl;

  // This doesn't work, but I prayed to Paul ¯\_(ツ)_/¯
  cout << ret << nl;
}

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
  while(n--) {
    solve();
  }

  return 0;
}
