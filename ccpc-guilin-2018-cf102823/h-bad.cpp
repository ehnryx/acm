#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

char mex(char a, char b) {
  char c = 'a';
  while(c == a || c == b) c++;
  return c;
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int T;
  cin >> T;
  for(int testnum=1; testnum<=T; testnum++) {
    cout << "Case " << testnum << ": ";

    string s, t;
    cin >> s >> t;
    int n = s.size();

    vector<int> match(n+1);
    for(int i=n-1; i>=0; i--) {
      match[i] = match[i+1] + (s[i] != t[i]);
    }

    string a(n, 'a');
    int scnt = 0;
    int tcnt = 0;
    for(int i=0; i<n; i++) {
      if(s[i] == t[i]) continue;
      if(match[i] <= abs(scnt - tcnt)) {
        if(scnt < tcnt) {
          a[i] = s[i];
        } else {
          a[i] = t[i];
        }
      }
      scnt += (s[i] == a[i]);
      tcnt += (t[i] == a[i]);
    }
    assert(abs(scnt - tcnt) <= 1);

    if(scnt != tcnt) {
      if(scnt > tcnt) {
        swap(scnt, tcnt);
        swap(s, t);
      }
      //cerr << s << nl << t << nl << a << nl;
      //cerr << scnt << " , " << tcnt << nl << nl;
      for(int i=n-1; i>=0; i--) {
        if(t[i] == a[i] && s[i] != a[i]) {
          a[i] = 'a';
          a[i] += (a[i] == t[i]);
          tcnt--;
          scnt += (a[i] == s[i]);
          break;
        }
      }
    }

    if(scnt != tcnt) {
      if(scnt > tcnt) {
        swap(scnt, tcnt);
        swap(s, t);
      }
      //cerr << "mex1" << nl;
      //cerr << s << nl << t << nl << a << nl;
      //cerr << scnt << " , " << tcnt << nl << nl;
      for(int i=0; i<n; i++) {
        if(t[i] == a[i] && s[i] != a[i]) {
          char to = mex(s[i], t[i]);
          if(to < a[i]) {
            a[i] = to;
            tcnt--;
            break;
          }
        }
      }
    }

    if(scnt != tcnt) {
      if(scnt > tcnt) {
        swap(scnt, tcnt);
        swap(s, t);
      }
      //cerr << "mex2" << nl;
      //cerr << s << nl << t << nl << a << nl;
      //cerr << scnt << " , " << tcnt << nl << nl;
      for(int i=n-1; i>=0; i--) {
        if(t[i] == a[i] && s[i] != a[i]) {
          char to = mex(s[i], t[i]);
          a[i] = to;
          tcnt--;
          break;
        }
      }
    }

    assert(scnt == tcnt);
    cout << a << nl;
  }

  return 0;
}
