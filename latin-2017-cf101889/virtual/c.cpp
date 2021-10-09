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
const int N = 1010;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());


int cnt[N];

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int k, n; cin >> k >> n;
  for (int i = 0; i < n; i++) {
    int s; cin >> s;
    cnt[s-1]++;
  }
  int sml = INF, big = -1;
  for (int i = 0; i < k; i++) {
    sml = min(sml, cnt[i]);
    big = max(big, cnt[i]);
  }
  if (big - sml > 2) {
    puts("*");
    return 0;
  }
  if (big - sml == 2) {
    int bigi = -1, smli = -1;
    for (int i = 0; i < k; i++) {
      if (cnt[i] == big) {
        if (bigi != -1) {
          puts("*");
          return 0;
        }
        bigi = i;
      }
      if (cnt[i] == sml) {
        if (smli != -1) {
          puts("*");
          return 0;
        }
        smli = i;
      }
    }
    cout << "-" << bigi+1 << " +" << smli+1 << endl;
  } else {
    int bigi = -1, smli = -1; bool isb = 0, iss = 0;
    for (int i = 0; i < k; i++) {
      if (cnt[i] == big) {
        if (bigi != -1) {
          if (iss) {
            puts("*");
            return 0;
          } else isb = 1;
        }
        bigi = i;
      }
      if (cnt[i] == sml) {
        if (smli != -1) {
          if (isb) {
            puts("*");
            return 0;
          } else iss = 1;
        }
        smli = i;
      }
    }
    if (isb) {
      cout << "+" << smli+1 << endl;
    } else {
      cout << "-" << bigi+1 << endl;
    }
  }

  return 0;
}
