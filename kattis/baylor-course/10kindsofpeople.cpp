#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 1e3;
const int M = 1e6+1;
char grid[N][N+1];
int root[M];
int sz[M];
int find(int i) {
  return (root[i]==-1?i:root[i]=find(root[i]));
}
void link(int i, int j) {
  i = find(i); j = find(j);
  if (i!=j) {
    if (sz[i]<sz[j]) {
      root[i] = j;
      sz[j] += sz[i]+1;
    } else {
      root[j] = i;
      sz[i] += sz[j]+1;
    }
  }
}

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  memset(root, -1, sizeof root);

  int n, m;
  scanf("%d%d",&n,&m);

  for (int i=0; i<n; i++) {
    scanf("%s",grid[i]);
    for (int j=0; j<m; j++) {
      if (i>0 && grid[i-1][j]==grid[i][j]) link((i-1)*m+j,i*m+j);
      if (j>0 && grid[i][j-1]==grid[i][j]) link(i*m+(j-1),i*m+j);
    }
  }

  int q;
  scanf("%d",&q);
  while (q--) {
    int a, b, x, y;
    scanf("%d%d%d%d",&a,&b,&x,&y);
    --a; --b; --x; --y;
    if (find(a*m+b)!=find(x*m+y)) {
      printf("neither\n");
    } else {
      a = find(x*m+y)/m;
      b = find(x*m+y)%m;
      if (grid[a][b] == '0') printf("binary\n");
      else printf("decimal\n");
    }
  }

  return 0;
}
