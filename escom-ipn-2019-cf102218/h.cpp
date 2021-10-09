#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const ld PI = acos((ld)-1);

ld phase(ld x) {
  while (x > 2*PI) x -= 2*PI;
  while (x < 0) x += 2*PI;
  return x;
}

pdd combine(ld a1, ld h1, ld a2, ld h2) {
  ld m = (h1+h2)/2;
  ld d = (h1-h2)/2;
  ld acosq = (a1+a2)*cos(d);
  ld asinq = (a1-a2)*sin(d);
  ld A = sqrt(acosq*acosq+asinq*asinq);
  ld q = atan2(asinq,acosq);
  ld H = phase(m+q);
  return pdd(A,H);
}

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int n; ld w;
  cin >> n >> w;

  ld a[n], h[n];
  For(i,n) {
    cin >> a[i] >> h[i];
  }

  ld A = a[n-1];
  ld H = h[n-1];
  For(i,n-1) {
    tie(A,H) = combine(A,H,a[i],h[i]);
  }

  cout << A << " " << H << nl;

  return 0;
}
