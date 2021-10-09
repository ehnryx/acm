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

const int N = 1e4+1;
int cnt[N];

bool valid(int k) {
  unordered_set<int> seen;
  for (int i=1; i<=k; i++) {
    seen.insert(cnt[i]);
  }
  return seen.size() == 1;
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

  int k, n, a;
  cin >> k >> n;

  for (int i=0; i<n; i++) {
    cin >> a;
    cnt[a]++;
  }

  pii minv(INF,0);
  pii maxv(-INF,0);
  for (int i=1; i<=k; i++) {
    minv = min(minv, pii(cnt[i],i));
    maxv = max(maxv, pii(cnt[i],i));
  }

  cnt[minv.second]++;
  if (valid(k)) {
    cout << '+' << minv.second << nl;
    return 0;
  }

  cnt[maxv.second]--;
  if (valid(k)) {
    cout << '-' << maxv.second << " " << '+' << minv.second << nl;
    return 0;
  }

  cnt[minv.second]--;
  if (valid(k)) {
    cout << '-' << maxv.second << nl;
    return 0;
  }

  cout << '*' << nl;

  return 0;
}
