#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const ld PI = acos((ld)-1);
const int N = 1e4+1;
ld shift[N], dist[N];

bool valid(ld h, int n) {
  vector<pair<ld,int>> p;
  int done = 0;
  for(int i=0; i<n; i++) {
    if(dist[i] > h) {
      ld t = acos(h/dist[i]);
      ld s = -t;
      s += shift[i];
      t += shift[i];
      if(t-s < PI/2) {
        for(int j=0; j<2; j++) {
          p.push_back(make_pair(s+j*PI/2,1));
          p.push_back(make_pair(t+j*PI/2,-1));
        }
      } else {
        done++;
      }
    } else {
      return false;
    }
  }
  sort(p.begin(), p.end());
  if(done == n) return true;

  int cnt = 0;
  for(const auto& it: p) {
    cnt += it.second;
    if(cnt+done == n) {
      return true;
    }
  }
  return false;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(4);

  int n;
  cin >> n;

  int x[n], y[n];
  for(int i=0; i<n; i++) {
    cin >> x[i] >> y[i];
    shift[i] = atan2((ld)y[i], (ld)x[i]);
    while(shift[i]<0) shift[i] += PI/2;
    while(shift[i]>PI/2) shift[i] -= PI/2;
    dist[i] = hypot((ld)x[i], (ld)y[i]);
  }

  ld l = 0;
  ld r = INF*2;
  while (r-l > EPS) {
    ld m = (l+r) / 2;
    if(valid(m, n)) {
      l = m;
    } else {
      r = m;
    }
  }

  ld ans = (l+r) / 2;
  cout << 8 * ans << nl;

  return 0;
}
