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

const int M = 1e7+17;
vector<int> primes;
void init() {
  bitset<M> np;
  np[0] = np[1] = true;
  int lim = sqrt(M);
  for (int i=2; i<lim; i++) {
    if (!np[i]) for (int j=i*i; j<M; j+=i) {
      np[j] = true;
    }
  }
  for (int i=0; i<M; i++) {
    if (!np[i]) primes.push_back(i);
  }
}

const int N = 1e6+2;
vector<int> pf[N];
int lp[N], rp[N];
int ans[N];

bool solve(int left, int right, int parent) {
  if (left > right) return true;
  int diff = right-left;
  int root = -1;
  for (int i=0; i<=diff/2; i++) {
    if (lp[left+i] < left && rp[left+i] > right) {
      root = left+i; break;
    }
    if (lp[right-i] < left && rp[right-i] > right) {
      root = right-i; break;
    }
  }
  if (root == -1) {
    return false;
  } else {
    ans[root] = parent;
    if (!solve(left, root-1, root)) return false;
    if (!solve(root+1, right, root)) return false;
    return true;
  }
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

  init();

  int n, v;
  cin >> n;

  map<int,vector<int>> idx;
  for (int i=1; i<=n; i++) {
    cin >> v;
    int lim = sqrt(v);
    for (int it : primes) {
      if (it>lim) break;
      if (v%it == 0) {
        pf[i].push_back(it);
        idx[it].push_back(i);
        while (v%it == 0) {
          v /= it;
        }
      }
    }
    if (v > 1) {
      pf[i].push_back(v);
      idx[v].push_back(i);
    }
  }

  for (int i=1; i<=n; i++) {
    int left = 0;
    int right = n+1;
    for (int it : pf[i]) {
      auto lb = lower_bound(idx[it].begin(), idx[it].end(), i);
      auto rb = next(lb);
      if (lb != idx[it].begin()) left = max(left, *prev(lb));
      if (rb != idx[it].end()) right = min(right, *rb);
    }
    tie(lp[i],rp[i]) = pii(left,right);
  }

  if (solve(1, n, 0)) {
    for (int i=1; i<=n; i++) {
      cout << ans[i] << " ";
    }
    cout << nl;
  } else {
    cout << "impossible" << nl;
  }

  return 0;
}
