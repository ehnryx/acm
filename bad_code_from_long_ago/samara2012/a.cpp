#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG
//#define USE_MAGIC_IO

#define ll long long
#define pii pair<int,int>
#define pdd pair<double,double>
#define ldouble long double
#define nl '\n'
const ll MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

struct BIT {
  const int size = 2500;
  int freq[2501];
  BIT() {
    memset(freq, 0, sizeof(freq));
  }
  void insert(int x) {
    for ( ; x <= size; x += x & -x)
      freq[x]++;
  }
  int query(int x) {
    int sum = 0;
    for ( ; x > 0; x -= x & -x) 
      sum += freq[x];
    return sum;
  }
  int query(int lx, int rx) {
    return query(rx) - query(lx-1);
  }
};

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  int n, m;
  cin >> n >> m;
  string grid[n];
  BIT row[n];
  BIT col[m];
  for (int i = 0; i < n; i++) {
    cin >> grid[i];
    for (int j = 0; j < m; j++)
      if (grid[i][j] == '#')
        row[i].insert(j+1);
  }
  for (int j = 0; j < m; j++) {
    for (int i = 0; i < n; i++)
      if (grid[i][j] == '#')
        col[j].insert(i+1);
  }
  int a, b, x, y;
  int q;
  cin >> q;
  while (q--) {
    cin >> a >> b >> x >> y;
    if (!row[a-1].query(min(y,b),max(y,b)) && !col[y-1].query(min(a,x),max(a,x))) {
      cout << "YES" << nl;
    }
    else if (!row[x-1].query(min(y,b),max(y,b)) && !col[b-1].query(min(a,x),max(a,x))) {
      cout << "YES" << nl;
    }
    else {
      cout << "NO" << nl;
    }
  }

  return 0;
}
