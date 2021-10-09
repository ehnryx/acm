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

const int N = 1e5+7;
const int S = sqrt(N);
vector<int> primes;

void init() {
  bitset<N> np;
  np[0] = np[1] = true;
  for (int i=2; i<S; i++)
    if (!np[i])
      for (int j=i*i; j<N; j+=i)
        np[j] = true;
  for (int i=0; i<N; i++) {
    if (!np[i]) primes.push_back(i);
  }
}

#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  init();

  ll n;
  cin >> n;

  if (n == 1) {
    cout << 1 << nl;
    cout << 1 << nl;
    return 0;
  }

  vector<ll> groups;
  ll sum = 0;
  for (int p : primes) {
    if (n % p == 0) {
      ll cur = 1;
      while (n % p == 0) {
        cur *= p;
        n /= p;
        if (cur > N) break;
      }
      groups.push_back(cur);
      sum += cur;
      if (sum > N) {
        cout << "No solution" << nl;
        return 0;
      }
    }
  }

  if (n > 1) {
    groups.push_back(n);
    sum += n;
  }
  if (sum > 1e5) {
    cout << "No solution" << nl;
    return 0;
  }

  cout << sum << nl;
  int offset = 1;
  for (int it : groups) {
    for (int i=1; i<it; i++) {
      cout << offset + i << " ";
    }
    cout << offset << " ";
    offset += it;
  }
  cout << nl;

  return 0;
}
