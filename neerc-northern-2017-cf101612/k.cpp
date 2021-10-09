#include <bits/stdc++.h>
using namespace std;

#define FILENAME "kotlin"

typedef long long ll;
typedef long double ld;
const char nl = '\n';


int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  if(fopen(FILENAME ".in", "r")) {
    freopen(FILENAME ".in", "r", stdin);
    freopen(FILENAME ".out", "w", stdout);
  }

  int n, m, k;
  cin >> n >> m >> k;
  char ans[n][m];
  fill(&ans[0][0], &ans[0][0]+n*m, '.');
  int a = (n+1)/2;
  int b = (m+1)/2;
  for(int i=1; i<=a; i++) {
    for(int j=1; j<=b; j++) {
      if(i*j == k) {
        for(int ii=1,c=1; c<i; ii+=2,c++) {
          for(int jj=0; jj<m; jj++) {
            ans[ii][jj] = '#';
          }
        }
        for(int jj=1,c=1; c<j; jj+=2,c++) {
          for(int ii=0; ii<n; ii++) {
            ans[ii][jj] = '#';
          }
        }
        for(int ii=0; ii<n; ii++) {
          for(int jj=0; jj<m; jj++) {
            cout << ans[ii][jj];
          }
          cout << nl;
        }
        return 0;
      }
    }
  }
  cout << "Impossible" << nl;

  return 0;
}
