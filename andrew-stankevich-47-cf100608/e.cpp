#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
//mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
mt19937 rng(7);

ostream& operator << (ostream& os, const vector<int> v) {
  for (int it : v) os << it << " ";
  return os;
}

vector<int> primes;

ll get_val(const vector<int>& v) {
  ll res = 1;
  for (int it : v) res *= primes[it];
  return res;
}

const int N = 10000;
void init() {
  bitset<N+1> notp;
  int lim = sqrt(N);
  for (int i = 2; i <= lim; i++)
    if (!notp[i])
      for (int j = i*i; j <= N; j += i)
        notp[j] = true;
  for (int i = 2; i <= N; i++)
    if (!notp[i]) primes.push_back(i);
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
  freopen("elegant.in", "r", stdin);
  freopen("elegant.out", "w", stdout);
  init();

  int n;
  cin >> n;

  vector<int> x;
  for (int i = 0; i < n; i++) {
    x.push_back(i);
  }

  vector<int> grid[n][n];

  int pnum = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      grid[j][(i+j)%n].push_back(pnum);
      grid[j][(i+n-j)%n].push_back(pnum+1);
    }
    pnum += 2;
  }

  if (n % 2 == 0) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n/2; j++) {
        grid[j][(i+2*j)%n].push_back(pnum);
        grid[n-1-j][n-1-(i+2*j)%n].push_back(pnum);
        grid[(i+2*j)%n][j].push_back(pnum+1);
        grid[n-1-(i+2*j)%n][n-1-j].push_back(pnum+1);
      }
      pnum += 2;
    }

    for (int j = 0; j < 2 + 2*(n==6); j++) {
      shuffle(x.begin(), x.end(), rng);
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          grid[j][(i+x[j])%n].push_back(pnum);
        }
        pnum++;
      }
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << get_val(grid[i][j]) << " "; 
    }
    cout << nl;
  }

  return 0;
}
