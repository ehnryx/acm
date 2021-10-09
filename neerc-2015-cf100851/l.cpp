#include <bits/stdc++.h>
using namespace std;
#define FILENAME "landscape"

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

const int N = 1<<17;
int h[N];

struct SegTree {
  ll sum[2*N]; int maxv[2*N];
  void set(int i, ll v) {
    sum[i+N] = v+i;
    maxv[i+N] = max((ll)-INF,v+i);
  }
  void build() {
    for (int i=N-1; i>0; i--) {
      sum[i] = sum[2*i] + sum[2*i+1];
      maxv[i] = max(maxv[2*i], maxv[2*i+1]);
    }
  }

  pair<ll, int> query(int l, int r, ll v, int i=1, int s=0, int e=N-1) {
    if (s>r || e<l) return { 0, -INF };
    if (l<=s && e<=r && maxv[i] < v) {
      return { v*(e-s+1) - sum[i], maxv[i] };
    }
    if (i>=N) {
      //cerr << "WTF" << endl;
      return { 0, INF }; // WTF???
    }
    int m = (s+e)/2;
    ll res, res2 = 0;
    int val, val2 = -INF;
    tie(res, val) = query(l, r, v, 2*i, s, m);
    if (val < v) tie(res2, val2) = query(l, r, v, 2*i+1, m+1, e);
    return { res + res2, max(val,val2) };
  }
};

SegTree lsegt, rsegt;


int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int w; ll n;
  cin >> w >> n;

  int maxv = 0;
  for (int i=1; i<=w; i++) {
    cin >> h[i];
    lsegt.set(w-i, h[i]);
    rsegt.set(i, h[i]);
    maxv = max(maxv, h[i]);
  }
  lsegt.set(w, -INFLL);
  rsegt.set(w+1, -INFLL);
  lsegt.build();
  rsegt.build();

  auto find = [&] (int target) {
    for (int i=1; i<=w; i++) {
      ll lval = lsegt.query(w-i, w, target + w-i).first;
      ll rval = rsegt.query(i+1, w+1, target + i).first;
      if (lval + rval <= n) {
        return true;
      }
    }
    return false;
  };

  ll left = maxv;
  ll right = maxv+w/2+7;
  while (left < right) {
    ll mid = (left+right+1)/2;
    if (find(mid)) {
      left = mid;
    } else {
      right = mid-1;
    }
  }

  cout << left << nl;

  return 0;
}
