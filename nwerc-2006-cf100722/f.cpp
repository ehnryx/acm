#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
#define nl '\n'

void solve() {
  int cur[10];
  pii a[1100];
  int n, m;
  cin >> n >> m;
  for (int i=0; i<10; ++i) {
    cur[i] = 0;
  }
  for (int i=0; i<n; ++i) {
    cin >> a[i].second;
    a[i].first = i;
    cur[a[i].second]++;
  }
  int bak = n;
  int i = 0;
  int goal = 9;
  int amt = 0;
  while(true) {
    while(cur[goal] == 0) {
      -- goal;
      //cerr << " GOAL " << goal << endl;
    }
    //cerr << " a["<< i << "] " << a[i].first << "," << a[i].second << endl;
    if (a[i].second != goal) {
      //cerr << " BAK " << bak << endl;
      a[bak++] = a[i];
    } else {
      ++amt;
      --cur[goal];
      if (a[i].first == m) {
        cout << amt << "\n";
        return;
      }
    }
    ++i;
  }
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int TT;
  cin >> TT;
  while (TT--) {
    solve();
  }

  return 0;
}
