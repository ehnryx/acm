#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;
const ld EPS = 1e-13;
const ld PI = acos((ld)-1);

const int N = 1e5+1;
ll a[N], b[N], c[N];

int bit[N];
void insert(int x, int v) {
  for ( ; x<N; x+=x&-x) {
    bit[x] += v;
  }
}
int query(int x) {
  int res = 0;
  for ( ; x>0; x-=x&-x) {
    res += bit[x];
  }
  return res;
}
int query(int l, int r) {
  return query(r)-query(l-1);
}

int n;

ll count(ld x) {
  x = tan(PI/2-x);
  memset(bit, 0, sizeof bit);
  vector<pair<ld,int>> segs;
  for (int i=0; i<n; i++) {
    segs.push_back({x*b[i]-a[i],i});
  }
  sort(segs.begin(), segs.end(), greater<pair<ld,int>>());

  //cerr << nl << "COUNT " << x << endl;
  ll ans = 0;
  for (const auto& it : segs) {
    int i = it.second;
    ////cerr << i << ": " << it.first << ", " << a[i] << " " << b[i] << " " << c[i] << endl;
    ans += query(1, c[i]);
    insert(c[i], 1);
  }
  ////cerr << " -> " << ans << endl;
  return ans;
}

ld search(ll goal) {
  //cerr << "SEARCH FOR " << goal << endl;
  ld left = PI;
  ld right = 0;
  for (int bs=0; bs<50; bs++) {
    ld mid = (left+right)/2;
    if (count(mid) >= goal) {
      left = mid;
    } else {
      right = mid;
    }
  }
  return left;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout << fixed << setprecision(13);

  cin >> n;

  map<int,int> remap;
  for (int i=0; i<n; i++) {
    cin >> a[i] >> b[i];
    remap[b[i]];
  }

  int rmpid = 1;
  for (auto& it : remap) {
    it.second = rmpid++;
  }
  for (int i=0; i<n; i++) {
    c[i] = remap[b[i]];
  }

  ll tot = (ll)n*(n-1)/2;
  if (tot%2 == 0) {
    cout << (search(tot/2) + search(tot/2+1)) / 2 << nl;
  } else {
    cout << search(tot/2+1) << nl;
  }

  return 0;
}
