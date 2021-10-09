#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const char nl = '\n';
const int INF = 0x3f3f3f3f;



int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  int T; cin >> T;
  while (T--) {
    int n, m; cin >> n >> m;
    int k;
    for (int i = 0; i < n+m; i++) {
      cin >> k;
    }
    puts(n <= m ? "Yes" : "No");
  }

  return 0;
}
