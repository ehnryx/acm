#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG
//#define USE_MAGIC_IO

#define ll long long
#define pii pair<int,int>
#define pdd pair<double,double>
#define ldouble long double
#define nl '\n'
const ll MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

struct Segments {
  struct Dist {
    int other;
    int diff;
    Dist(int p, int d) {
      other = p;
      diff = d;
    }
  };
  ll fixed[200000];
  Dist pair[200000];
  Segments() {
    memset(fixed, -1, sizeof(fixed));
  }
  ll& operator [] (int i) {
    return fixed[i];
  }

  void add(int a, int b, int d) {
    pair[a] = Dist(b, d);
    pair[b] = Dist(a, -d);
  }
  void fix(int a, int f) {
    if (a > pair[a].other) 
      a = pair[a].other;
    fixed[a] = f;
    fixed[pair[a].other] = f + pair[a].diff;
  }

  ll attempt(int curr, ll pos) {
    int other = pair[curr].other;
    if (other == 0) 
    if (other > 0 && fixed[other-1] == -1) {
    } else {
      return fixed[other-1].
    }
  }
};

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  Segments sad;
  int first, second;
  int a, b, d;
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a >> b >> d;
    if (a > b) d = -d;
    sad.add(a, b, d);
  }
  cin >> first >> second;
  if (first > second) swap(first, second);
  sad.fix(first, 0);

  for (int i = first+1; i <= second; i++) {
    if (sad[i] == -1)
      sad.fix(i, sad[i-1] + sad.attempt(i, sad[i-1]));
  }
  cout << sad[second] << nl;

  return 0;
}
