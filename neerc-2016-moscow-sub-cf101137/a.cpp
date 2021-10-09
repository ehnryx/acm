#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const char nl = '\n';
const int INF = 0x3f3f3f3f;




int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n; cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  for (int i = 0; i < n; i++) {
    if (a[i] < a[(i+1)%n] && a[(i+1)%n] > a[(i+2)%n]) {
      cout << i+1 << " " << (i+1)%n+1 << " " << (i+2)%n+1 << nl;
      return 0;
    }
  }

  return 0;
}
