#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;

struct Seg {
  int a, l, r;
  bool operator < (const Seg& o) const { 
    return a > o.a;
  }
};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int h, w, n;
  cin >> h >> w >> n;

  vector<Seg> segs;
  for (int i=0; i<n; i++) {
    int a, b;
    cin >> a >> b;
    segs.push_back({a,b,b+1});
  }
  sort(segs.begin(), segs.end());

  bool flip;
  int ans[w+2];
  for (int i=1; i<=w; i++) {
    int x = i;
    if (i%2 == 0) x = w+1 - x;
    x += h;
    flip = x/w % 2;
    x = x%w;
    if (x == 0) x++;
    if (flip) x = w+1 - x;
    if (i%2 == 0) x = w+1 - x;
    ans[i] = x;
    //cerr << i << ": " << ans[i] << nl;
  }

  for (const Seg& s : segs) {
    int r = s.r;
    r += s.a-1;
    flip = r/w % 2;
    r = r%w;
    if (r == 0) r++;
    if (flip) r = w+1 - r;
    int l = s.l;
    l = w+1 - l;
    l += s.a-1;
    flip = l/w % 2;
    l = l%w;
    if (l == 0) l++;
    if (flip) l = w+1 - l;
    l = w+1 - l;
    //cerr << "FLIP " << l << " " << r << nl;
    swap(ans[l], ans[r]);
  }

  for (int i=1; i<=w; i++) {
    cout << ans[i] << nl;
  }

  return 0;
}
