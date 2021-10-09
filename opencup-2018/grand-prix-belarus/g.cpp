#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define nl '\n'
#define pb push_back

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const int INF = 0x3f3f3f3f;



int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(17);

  int T;
  cin >> T;
  while (T--) {
    int k, l;
    cin >> k >> l;
    ld r = l/M_PIl;
    ld area = r*r*M_PIl/2;
    if (2*r > k) {
      ld goal = (ld)l/k;
      ld left = 0;
      ld right = M_PIl;
      for (int bs=0; bs<97; bs++) {
        ld mid = (left+right)/2;
        if (mid/sin(mid) < goal) left = mid;
        else right = mid;
      }
      ld q = 2*left;
      r = l/q;
      area = r*r*q/2 + r*r*sin(2*M_PIl-q)/2;
    }
    cout << area << nl;
  }

  return 0;
}

