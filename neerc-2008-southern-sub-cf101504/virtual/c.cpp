#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const char nl = '\n';
const int INF = 0x3f3f3f3f;

struct Segment {
  int id;
  ll x, yl, yr;
  int t;
  bool operator < (const Segment& o) const {
    if (x != o.x) return x < o.x;
    return t > o.t;
  }
};

ll convertx(ll x, ll y) {
  return x-y;
}
ll converty(ll x, ll y) {
  return x+y;
}

const int N = 3e5+7;
int freq[N];
int query(int x) {
  int res = 0;
  for ( ; x > 0; x -= x&-x) 
    res += freq[x];
  return res;
}
void insert(int x, int cnt) {
  for ( ; x < N; x += x&-x)
    freq[x] += cnt;
}
void insert_range(int xl, int xr, int cnt) {
  insert(xl, cnt);
  insert(xr+1, -cnt);
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n, k;
  cin >> n >> k;

  map<ll,int> remap;
  vector<Segment> segs;
  for (int i = 1; i <= n; i++) {
    int x, y, w;
    cin >> x >> y >> w;
    remap[converty(x,y)];
    remap[converty(x,y+w)];
    remap[converty(x,y-w)];
    segs.push_back({i, convertx(x,y), converty(x,y), converty(x,y), 0});
    segs.push_back({i, convertx(x-w,y), converty(x-w,y), converty(x,y+w), 1});
    segs.push_back({i, convertx(x+w,y), converty(x,y-w), converty(x+w,y), -1});
  }
  sort(segs.begin(), segs.end());

  int cnum = 1;
  for (auto& it : remap) {
    it.second = cnum++;
  }

  vector<int> ans;
  for (const Segment& seg : segs) {
    if (seg.t == 0) {
      if (query(remap[seg.yl]) > k) {
        ans.push_back(seg.id);
      }
    } else {
      insert_range(remap[seg.yl], remap[seg.yr], seg.t);
    }
  }
  sort(ans.begin(), ans.end());

  cout << ans.size() << nl;
  for (int it : ans) {
    cout << it << ' ';
  }
  cout << nl;

  return 0;
}
