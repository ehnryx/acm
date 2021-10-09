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

const int N = 1e4+1;
int x[N], y[N];
int cnt[2][2];

ll ncr(int n, int r) {
  ll res = 1;
  For(i,r) res *= n-i;
  For(i,r) res /= i+1;
  return res;
}

int solve() {
  memset(cnt, 0, sizeof cnt);

  int n;
  cin >> n;
  For(i,n) {
    cin >> x[i] >> y[i];
    cnt[abs(x[i])%2][abs(y[i])%2]++;
  }

  set<map<pii,int>> todo;
  For(ax,2) {
    For(ay,2) {
      For(bx,2) {
        For(by,2) {
          For(cx,2) {
            For(cy,2) {
              if ((ax*by+bx*cy+cx*ay+ay*bx+by*cx+cy*ax)%2 == 0) {
                map<pii,int> cur;
                cur[pii(ax,ay)]++;
                cur[pii(bx,by)]++;
                cur[pii(cx,cy)]++;
                todo.insert(cur);
              }
            }
          }
        }
      }
    }
  }

  ll ans = 0;
  for (const auto& cur : todo) {
    ll res = 1;
    for (const auto& it : cur) {
      res *= ncr(cnt[it.first.first][it.first.second], it.second);
    }
    ans += res;
  }

  cout << ans << nl;

  return 0;
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

  int T;
  cin >> T;
  while (T--) {
    assert(solve() == 0);
  }

  return 0;
}
