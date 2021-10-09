#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const char nl = '\n';

struct bit {
  vector<int> t;
  int n;
  bit (int sz) {
    n = sz+1;
    t = vector<int>(n);
  }
  void add(int x, int v) {
    for (; x<n; x+=(x&-x)) {
      t[x] += v;
    }
  }
  int query(int x) {
    int amt = 0;
    if (x == 0) return 0;
    for (; x; x-=(x&-x)) {
      amt += t[x];
    }
    return amt;
  }
};

const int N = 100100;

int pos[N*2];

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);

  int TT;
  cin >> TT;
  while (TT--) {
    int n, m;
    cin >> n >> m;
    bit b(n+m+10);
    int first = m+1;
    for (int i=1; i<=n; ++i) {
      pos[i] = m+1+i;
      b.add(m+1+i, 1);
    }

    for (int q=1; q<=m; ++q) {
      int j;
      cin >> j;
      cout << b.query(pos[j]-1) << " ";
      b.add(pos[j], -1);
      pos[j] = first--;
      b.add(pos[j], 1);
    }
    cout << "\n";
  }

  return 0;
}
