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
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int n, m;
  cin >> n >> m;

  int a[n], b[n];
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  for (int i = 0; i < n; i++) {
    cin >> b[i];
  }

  auto count = [&] (int lb) {
    if (lb == 1) return (ll)INF;
    ll cnt = 0;
    for (int i = 0; i < n; i++) {
      if (a[i] >= lb) {
        cnt += 1 + (a[i]-lb)/b[i];
      }
    }
    return cnt;
  };

  auto answer = [&] (int lb) {
    ll res = 0;
    for (int i = 0; i < n; i++) {
      if (a[i] >= lb) {
        ll cnt = 1 + (a[i]-lb)/b[i];
        res += cnt * a[i] - cnt*(cnt-1)/2 * b[i];
      }
    }
    return res;
  };

  int left, right, mid;
  left = 1;
  right = 1e9;
  while (left <= right) {
    mid = (left+right)/2;
    if (count(mid) >= m) left = mid+1;
    else right = mid-1;
  }
  if (count(mid) >= m) mid++;

  int num = count(mid);
  cout << answer(mid) + (ll)(mid-1)*(m-num) << nl;

  return 0;
}
