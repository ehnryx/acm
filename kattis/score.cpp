#include <bits/stdc++.h>
using namespace std;

//%:include "io/fast_input.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int n;
  scanf("%d\n", &n);

  int home = 0;
  int away = 0;
  int htime = 0;
  int atime = 0;

  int last = 0;
  for(int i=0; i<n; i++) {
    char t;
    int s, h, m;
    scanf("%c %d %d:%d\n", &t, &s, &h, &m);

    int cur = h*60 + m;
    if(home > away) {
      htime += cur - last;
    } else if(home < away) {
      atime += cur - last;
    }
    last = cur;

    if(t == 'H') {
      home += s;
    } else {
      away += s;
    }
  }

  if(int cur = 32*60; home > away) {
    htime += cur - last;
  } else if(home < away) {
    atime += cur - last;
  }

  printf("%c %d:%02d %d:%02d\n", home > away ? 'H' : 'A', htime / 60, htime % 60, atime / 60, atime % 60);

  return 0;
}
