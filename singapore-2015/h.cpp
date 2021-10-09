#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
const int P = sqrt(4e7)+1;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Frac {
  ll n, d;
  Frac(ll a=0, ll b=1) {
    assert(abs(__gcd(a,b))==1 && b>0);
    tie(n,d) = tie(a,b);
  }
  bool operator < (const Frac& o) const {
    return n*o.d < d*o.n;
  }
};

vector<int> ps;
int tot[P];
void init() {
  iota(tot, tot + P, 0);
  vector<bool> isp(P, 1);
  for (int i = 2; i < P; i++) {
    if (isp[i]) {
      for (int j = i; j < P; j += i) {
        isp[j] = 0;
        tot[j] -= tot[j] / i;
      }
    }
  }
  for (int i = 2; i < P; i++) {
    if (isp[i]) ps.push_back(i);
  }
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
  init();

  int C = 4200;
  int cur = 0;
  vector<Frac> slopes;
  for (int i=2; ; i++) {
    int lim = min(i-1, (int)(C/sqrt(i)));
    int sum = 0;
    int cnt = 0;
    for (int j=1; j<=lim; j++) {
      sum += (__gcd(i,j)==1) * j;
      cnt += (__gcd(i,j)==1);
    }
    if (cur + i*cnt + sum > 2e7) break;
    cur += i*cnt + sum;
    for (int j=1; j<lim; j++) {
      if (__gcd(i,j)==1) {
        assert(0<j && j<i);
        slopes.push_back(Frac(j,i));
        slopes.push_back(Frac(i,j));
        slopes.push_back(Frac(-j,i));
        slopes.push_back(Frac(-i,j));
      }
    }
  }
  sort(slopes.begin(), slopes.end());
  int half = slopes.size();
  for (int i=0; i<half; i++) {
    slopes.push_back(slopes[i]);
  }
  //cerr << slopes.size() << " SLOPES!" << nl;

  int n;
  cin >> n;
  int x = 0;
  int y = 2e7;
  for (int i=0; i<n; i++) {
    cout << x << " " << y << nl;
    if (i<half) {
      x += slopes[i].d;
      y += slopes[i].n;
    } else {
      x -= slopes[i].d;
      y -= slopes[i].n;
    }
  }

  return 0;
}
