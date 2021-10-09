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



//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int n;
  cin >> n;

  char a[n][n];
  memset(a,0,sizeof a);
  for(int i=0;i<n;i++){
    int x,y;
    cin >> x >> y;
    a[x][y] = '*';
  }
  for(int i=0;i<n;i++)for(int j=0;j<n;j++)if(a[i][j]=='*'){
    for(int k=0;k<n;k++){
      if(k!=j&&a[i][k]=='*')goto bad;
      if(k!=i&&a[k][j]=='*')goto bad;
      if(k!=i&&j+k-i>=0&&j+k-i<n&&a[k][j+k-i]=='*')goto bad;
      if(k!=i&&j-k+i>=0&&j-k+i<n&&a[k][j-k+i]=='*')goto bad;
    }
  }
  cout << "CORRECT" << nl;
  return 0;

bad:
  cout << "INCORRECT" << nl;

  return 0;
}
