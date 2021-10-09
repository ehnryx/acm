#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const char nl = '\n';
const int INF = 0x3f3f3f3f;


const int MAXN = 2e5+10;

string op[MAXN];
int t[MAXN];

ld ans[MAXN];
int n;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n;
  n = 2*n;
  for(int i=0;i<n;i++) {
    cin >> op[i] >> t[i];
  }

  ld A = 0;
  ld S = 0;
  int cum = 0;
  for(int i=n-1;i>=0;i--) {
    if (op[i]=="-") {
      cum++;
      S=1.0L/cum*t[i] + (1-1.0L/cum)*S;
    }
    else {
      ans[i] = S - t[i];
      cum--;
      if (cum ==0) S=A=0;
    }
    //cerr << i << " " << S << " " << A << " " << cum <<endl;
  }

  cout << setprecision(10) << fixed;
  for(int i=0;i<n;i++) {
    if (op[i]=="+") cout << ans[i] << nl;
  }

  return 0;
}
