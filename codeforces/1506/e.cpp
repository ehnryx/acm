#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';
using ll = long long;
int T = -1;

int main() {
  if(T < 0) { cin.tie(0)->sync_with_stdio(0); cin >> T; }
  if(--T) main();

  int n;
  cin >> n;
  vector<int> a(n);
  for(int i=0; i<n; i++) {
    cin >> a[i];
  }

  vector<int> small(n), big(n);
  set<int> hs, hb;
  for(int i=0, j=1; i<n; i++) {
    while(j <= a[i]) {
      hs.insert(j);
      hb.insert(j);
      j++;
    }

    if(i == 0 || a[i] != a[i-1]) {
      small[i] = big[i] = a[i];
      hs.erase(a[i]);
      hb.erase(a[i]);
    } else {
      small[i] = *begin(hs);
      hs.erase(begin(hs));
      big[i] = *rbegin(hb);
      hb.erase(prev(end(hb)));
    }
  }

  for(int it : small) {
    cout << it << " ";
  }
  cout << nl;
  for(int it : big) {
    cout << it << " ";
  }
  cout << nl;

  return 0;
}
