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

bool valid(vector<int> a, vector<int> p, int k) {
  vector<int> v;
  for (int i=0; i<p.size(); i++) {
    v.push_back(i);
  }

  while (k--) {
    vector<int> nxt(p.size());
    for (int i=0; i<p.size(); i++) {
      nxt[i] = v[p[i]];
    }
    v = nxt;
  }

  return v == a;
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

  int n, k;
  cin >> n >> k;

  vector<int> a;
  vector<int> p;
  for (int i=0; i<n; i++) {
    int v;
    cin >> v;
    a.push_back(v-1);
    p.push_back(i);
  }

  int ans = 0;
  do {
    if (valid(a,p,k)) {
      ans++;
    }
  } while (next_permutation(p.begin(), p.end()));
  cout << ans << nl;

  return 0;
}
