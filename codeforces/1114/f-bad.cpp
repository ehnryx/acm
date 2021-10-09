//#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
const int MOD = 1e9+7;
const int TOT = MOD-1;

// MAGIC IO
inline char get(void) {
  static char buf[1000000], *S = buf, *T = buf;
  if (S == T) {
    T = (S = buf) + fread(buf, 1, 100000, stdin);
    if (S == T) return EOF;
  }
  return *S++;
}
inline void read(int &x) {
  static char c; x = 0; int sgn = 0;
  for (c = get(); c < '0' || c > '9'; c = get()) if (c == '-') sgn = 1;
  for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + c - '0';
  if (sgn) x = -x;
}
void readchar(char& c) {
  while (isspace(c = get()));
}
// END MAGIC IO

inline ll power(ll n, int e) {
  ll res = 1;
  for ( ; e>0; e/=2) {
    if (e&1) res = res*n % MOD;
    n = n*n % MOD;
  }
  return res;
}

vector<int> primes;

const int N = 4e5+1;
const int ST = 62;
int slope[ST][N+1], inter[ST][N+1];

inline void insert_point(int st[], int x, int v) {
  for ( ; x <= N; x += x&-x) {
    st[x] += v;
    if (st[x] > MOD) st[x] %= TOT;
  }
}

inline void insert_range(int st[], int l, int r, int v) {
  insert_point(st, l, v);
  insert_point(st, r+1, -v);
}

inline int query_point(int st[], int x) {
  int res = 0;
  for ( ; x > 0; x -= x&-x) {
    res += st[x];
    if (res > MOD) res %= TOT;
  }
  return res;
}

inline void update(int st, int l, int r, int v) {
  insert_range(slope[st], l, r, v);
  insert_range(inter[st], l, r, -(l-1)*v % TOT);
  insert_range(inter[st], r+1, N, (r-l+1)*v % TOT);
}

inline int query(int st, int l, int r) {
  ll left = (ll)query_point(slope[st], l-1)*(l-1) + query_point(inter[st], l-1);
  ll right = (ll)query_point(slope[st], r)*r + query_point(inter[st], r);
  return ((right - left) % TOT + TOT) % TOT;
}

//#define FILEIO
int main() {
  // generate primes
  for (int i=2; i<=300; i++) {
    bool p = true;
    for (int j=2; j<i; j++) {
      if (i%j == 0) {
        p = false;
        break;
      }
    }
    if (p) primes.push_back(i);
  }
  int sz = primes.size();

  int n, q, a, b, c;
  read(n); read(q);

  for (int i=1; i<=n; i++) {
    read(a);
    for (int j=0; j<sz; j++) {
      int cnt = 0;
      while (a%primes[j] == 0) {
        cnt++;
        a /= primes[j];
      }
      update(j, i, i, cnt);
    }
  }

  for (char s; q>0; q--) {
    readchar(s);
    if (s == 'M') { // MULTIPLY
      readchar(s);
      readchar(s);
      readchar(s);
      readchar(s);
      readchar(s);
      readchar(s);
      readchar(s);
      read(a); read(b); read(c);
      for (int i=0; i<sz; i++) {
        int cnt = 0;
        while (c%primes[i] == 0) {
          cnt++;
          c /= primes[i];
        }
        if (cnt>0) {
          update(i, a, b, cnt);
        }
      }
    } else { // TOTIENT
      readchar(s);
      readchar(s);
      readchar(s);
      readchar(s);
      readchar(s);
      readchar(s);
      read(a); read(b);
      ll ans = 1;
      for (int i=0; i<sz; i++) {
        int cur = query(i, a, b);
        if (cur>0) {
          int mlt = power(primes[i], cur-1) * (primes[i]-1) % MOD;
          ans = ans * mlt % MOD;
        }
      }
      printf("%d\n", (int)ans);
    }
  }

  return 0;
}
