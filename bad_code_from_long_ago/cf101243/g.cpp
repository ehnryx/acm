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
inline T sqr(T x) { return x*x; }

const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
//const ld PI = M_PIl;
////////////////////////////////////////////////////////////////////////

const ll MOD = 1e9+7;
const ld EPS = 1e-9;
const int N = 1e5;

vector<bool> prime(N, 1);
vector<int> primes;

void pre() {
  prime[0] = prime[1] = 0;
  for (int i = 2; i < N; i++)
    if (prime[i])
      for (ll j = (ll) i*i; j < N; j += i)
        prime[j] = 0;
  for (int i = 2; i < N; i++)
    if (prime[i])
      primes.push_back(i);
}


int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
#ifdef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif

  pre();
  int n; cin >> n;
  int num = 0;
  for (int i : primes) {
    if ((ll) i*i > n) {
      num++;
      break;
    }
    if (n % i == 0) {
      num++;
      n /= i;
      if (n % i == 0) {
        num = -1;
        break;
      }
    }
  }
  (num == 3 ? puts("YES") : puts("NO"));

  return 0;
}
