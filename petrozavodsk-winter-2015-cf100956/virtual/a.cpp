//#define DEBUG

#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;

mt19937 paul(chrono::high_resolution_clock::now().time_since_epoch().count());

#ifdef DEBUG
const ll L = 120;
#else
const ll L = 1<<30;
#endif 

const int N = 1e6+1;
int a[N];

inline int dist(int x, int y) {
  if (x<=y) return y-x;
  else return y-x+L;
}

int n, k;

inline int d2(int x, int y) {
  return min(abs(x-y), (int)(L-abs(x-y)));
}

ll get(vector<int> v) {
  int m = v.size();
  sort(v.begin(), v.end());
  auto antiptr = upper_bound(v.begin(), v.end(), (v[0]+L/2)%L);
  if (antiptr == v.end()) antiptr = v.begin();
  int anti = antiptr - v.begin();
  ll sum = 0;
  for (int it : v) {
    sum += d2(v[0], it);
  }
  ll best = sum;
  for (int i=1; i<m; i++) {
    int left = (anti-i+m) % m;
    int right = m-left;
    sum += (ll)(right-left)*(v[i]-v[i-1]);
    if (anti == i) {
      sum -= L;
      anti++; if (anti == m) anti = 0;
    }
    while (dist(v[anti],v[i]) >= L/2) {
      sum += (ll)dist(v[i],v[anti]) - dist(v[anti],v[i]);
      anti++; if (anti == m) anti = 0;
    }
    best = min(best,sum);
  }
  //cerr << "GET "; for (int it : v) cerr << it << " "; cerr << " -> " << best << endl;
  return best;
}

bool small(ll maxv) {
  for (int i = 0; i < n; i++) {
    int used = 0;
    vector<int> cur;
    bool bad = 0;
    for (int j = 0; j < n; j++) {
      cur.push_back(a[(i+j)%n]);
      if (get(cur) > maxv) {
        used++;
        if (used >= k) {
          bad = 1;
          break;
        }
        cur = {a[(i+j)%n]};
      }
    }
    if (!bad) return 1;
  }
  return 0;
}

#define BAD 29
bool valid(ll maxv) {
  // go around once
  int limit2 = 3;
  int limit1 = 3.2e7/limit2/n;
  for (int bs1=0; bs1<limit1; bs1++) {
    int start = paul()%n;
    for (int bs2=0; bs2<limit2; bs2++) {
      ll cur = 0;
      int m = start;
      int j = start;
      int cnt = 0;
      int par = 1;
      int nxtstart = -1;
      for (int i=1; i<n; i++) {
        j++; if (j==n) j=0;
        if (cur + dist(a[m], a[j]) > maxv) {
          if (++cnt == k) {
            nxtstart = j;
            break;
          } else {
            cur = 0;
            m = j;
            par = 1;
          }
        } else { // add median
          cur += dist(a[m], a[j]);
          if (par) { m++; if (m==n) m=0; }
          par ^= 1;
        }
      }
      if (nxtstart == -1) {
        return true;
      }
      start = nxtstart;
    }
  }
  return false;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  //int n, k;
  cin >> n >> k;

  int seed, add;
  cin >> seed >> add;
#ifdef DEBUG
  for (int i=0; i<n; i++) {
    a[i] = ((seed*i+add) % L + L) % L;
  }
#else
  for (int i=0; i<n; i++) {
    seed = ((ll)seed*239017 + add) % L;
    a[i] = seed;
  }
#endif
  sort(a, a+n);

  //cerr << "POINTS: "; for (int i=0; i<n; i++) cerr << a[i] << " ";
  //cerr << nl;

  ll left = 0;
  ll right = (n<100 ? L*n : L*sqrt(n));
  cerr << "LB: " << left << nl;
  cerr << "UB: " << right << nl;
  while (left < right) {
    ll mid = (left+right)/2;
    if (n < 100) {
      if (small(mid)) {
        right = mid;
      } else {
        left = mid+1;
      }
    } else {
      if (valid(mid)) {
        right = mid;
      } else {
        left = mid+1;
      }
    }
  }
  assert(left == right);
  cout << left << nl;

  return 0;
}
