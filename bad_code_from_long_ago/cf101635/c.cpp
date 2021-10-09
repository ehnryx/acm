#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

inline void srand() { srand(clock() + time(nullptr)); }

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
  os << "(" << v.first << "," << v.second << ")"; return os;
}

template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
  for (const T& it : v) os << it << " "; return os;
}

template <class T>
ostream& operator << (ostream& os, const set<T>& v) {
  os << "{ ";
  for (const T& it : v) os << it << " ";
  os << "}"; return os;
}

template <class T, class U>
ostream& operator << (ostream& os, const map<T,U>& v) {
  os << "{ ";
  for (const pair<T,U>& it : v) os << "{" << it.first << "," << it.second << "} "; 
  os << "}"; return os;
}

template <class T>
inline T sqr(T x) { return x*x; }

const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
//const ld PI = M_PIl;
////////////////////////////////////////////////////////////////////////

const ll MOD = 1e9;
const ld EPS = 1e-9;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  vector<ll> fibb = { 1, 1, 2, 3, 5, 8, 13, 21, 34, 55 };

  int n; 
  ll m;
  cin >> n >> m;

  int len = 1<<n;
  ll mat[len][len];
  memset(mat, 0, sizeof mat);

  for (int bm = 1; bm < len; bm++) {
    for (int next = 1; next < len; next++) {
      if ((bm & next) == next) {
        int cur = ~(next ^ bm);
        int cnt = 0;
        int opp = 0;
        ll add = 1;
        for (int i = 0; i < n; i++) {
          if (bm & cur & (1<<i)) cnt++;
          else {
            add = add * fibb[cnt] % MOD;
            cnt = 0;
          }
          if ((~bm) & cur & (1<<i)) opp++;
          else {
            add = add * fibb[opp] % MOD;
            opp = 0;
          }
        }
        mat[next][bm] = add * fibb[cnt] % MOD * fibb[opp] % MOD;
      }
      else if (~bm == next) {
        int cur = next & bm;
        int cnt = 0;
        ll add = 1;
        for (int i = 0; i < n; i++) {
          if (cur & (1<<i)) cnt++;
          else {
            add = add * fibb[cnt] % MOD;
            cnt = 0;
          }
        }
        mat[next][bm] = add * fibb[cnt] % MOD;
      }
    }
  }

  for (int bm = 0; bm < len; bm++) {
    int cur = bm;
    int cnt = 0;
    ll add = 1;
    for (int i = 0; i < n; i++) {
      if (cur & (1<<i)) cnt++;
      else {
        add = add * fibb[cnt] % MOD;
        cnt = 0;
      }
    }
    mat[len-1][bm] = add * fibb[cnt] % MOD;
  }
  mat[0][len-1] = 1;

  ll ans[len][len];
  memset(ans, 0, sizeof ans);
  for (int i = 0; i < len; i++) {
    ans[i][i] = 1;
  }

  ll temp[len][len];
  while (m > 0) {
    if (m & 1) {
      for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
          temp[i][j] = 0;
          for (int k = 0; k < len; k++)
            temp[i][j] = (temp[i][j] + ans[i][k] * mat[k][j] % MOD) % MOD;
        }
      }
      for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
          ans[i][j] = temp[i][j];
        }
      }
    }

    for (int i = 0; i < len; i++) {
      for (int j = 0; j < len; j++) {
        temp[i][j] = 0;
        for (int k = 0; k < len; k++)
          temp[i][j] = (temp[i][j] + mat[i][k] * mat[k][j] % MOD) % MOD;
      }
    }
    for (int i = 0; i < len; i++) {
      for (int j = 0; j < len; j++) {
        mat[i][j] = temp[i][j];
      }
    }
    m >>= 1;
  }

  cout << ans[len-1][len-1] << nl;

  return 0;
}
