#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
#define nl '\n'

const ld EPS = 1e-7;
const ld PI = acos((ld)-1);

const int N = 1e4+1;
int a[N];

int count(int n, ld v) {
  int res = 0;
  for(int i=0; i<n; i++) {
    ld ang = 2*v/((ld)a[i]*a[i]);
    res += floor(2*PI/ang);
  }
  return res;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(11);

  int T;
  cin >> T;
  while(T--) {
    int n, m;
    cin >> n >> m;
    for(int i=0; i<n; i++) {
      cin >> a[i];
    }
    ld l = 0;
    ld r = 1e9;
    while(r-l>EPS) {
      ld v = (l+r)/2;
      if(count(n, v) >= m+1) {
        l = v;
      } else {
        r = v;
      }
    }
    cout << r << nl;
  }

  return 0;
}
