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

const int N = 2e5+1;
map<int,int> cnt[11];
int vals[N], len[N];
int modshift[11];

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int n, k;
  cin >> n >> k;

  ll ms = 1;
  for (int i = 0; i <= 10; i++) {
    modshift[i] = ms;
    ms = ms*10 % k;
  }

  string s;
  ll ans = 0;
  for (int i = 0; i < n; i++) {
    cin >> s;
    len[i] = s.size();
    vals[i] = stoi(s) % k;
    cnt[len[i]][vals[i]] += 1;
    if ((vals[i] * modshift[len[i]] + vals[i]) % k == 0) {
      ans--;
    }
  }

  for (int i = 0; i < n; i++) {
    for (int shift = 1; shift <= 10; shift++) {
      ans += cnt[shift][(k - (vals[i] * modshift[shift] % k)) % k];
    }
  }

  cout << ans << nl;

  return 0;
}
