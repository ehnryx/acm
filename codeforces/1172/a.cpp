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

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int n;
  cin >> n;

  int a[n], b[n];
  For(i,n) {
    cin >> a[i];
  }
  For(i,n) {
    cin >> b[i];
  }

  int ans = -1;
  function<bool(int)> valid = [&] (int s) {
    unordered_multiset<int> cur;
    deque<int> ch;
    For(i,n) {
      cur.insert(a[i]);
      ch.push_back(b[i]);
    }
    For(i,s) {
      cur.erase(cur.find(0));
      ch.push_back(0);
      cur.insert(ch.front());
      ch.pop_front();
    }

    ans = s;
    while (ch.back() != n) {
      ans++;
      int g = ch.back()+1;
      if (cur.count(g)) {
        cur.erase(g);
        ch.push_back(g);
        cur.insert(ch.front());
        ch.pop_front();
      } else {
        break;
      }
    }

    bool ok = true;
    int p = 0;
    For(i,n) {
      if (ch.front() != p+1) {
        ok = false;
        break;
      }
      p = ch.front();
      ch.pop_front();
    }
    return ok;
  };

  if (valid(0)) {
    cout << ans << nl;
    return 0;
  }

  int l = 0;
  int r = n;
  while (l<r) {
    int m = (l+r)/2;
    if (valid(m)) {
      r = m;
    } else {
      l = m+1;
    }
  }
  assert(valid(l));
  assert(ans != -1);
  cout << ans << nl;

  return 0;
}
