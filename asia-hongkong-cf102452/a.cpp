#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
#define nl '\n'

const int INF = 0x3f3f3f3f;

struct Segment {
  int x, l, r;
};

const int N = 1<<19;
int st[2*N], sum[2*N];

void clear(int n) {
  for(int i=0; i<=n; i++) {
    for(int j=N+i; j>0; j/=2) {
      st[j] = st[j^1] = 0;
      sum[j] = sum[j^1] = 0;
    }
  }
}

void push(int i, int len) {
  if(st[i]) {
    st[2*i] ^= 1;
    st[2*i+1] ^= 1;
    sum[2*i] = len/2 - sum[2*i];
    sum[2*i+1] = len/2 - sum[2*i+1];
    st[i] = 0;
  }
}

void insert(int l, int r, int i=1, int s=0, int e=N-1) {
  if(r<s || e<l) return;
  if(l<=s && e<=r) {
    st[i] ^= 1;
    sum[i] = (e-s+1) - sum[i];
    return;
  }
  push(i, e-s+1);
  int m = (s+e)/2;
  insert(l, r, 2*i, s, m);
  insert(l, r, 2*i+1, m+1, e);
  sum[i] = sum[2*i] + sum[2*i+1];
}

bool solve(const vector<Segment>& segs) {
  map<int,vector<pair<int,int>>> lines;
  map<int,int> rmp;
  for(auto [x, l, r] : segs) {
    lines[x].push_back(make_pair(l, r));
    rmp[l]; rmp[r];
  }

  int rid = 0;
  for(auto& it : rmp) {
    it.second = ++rid;
  }

  clear(rid);
  for(const auto& it : lines) {
    for(auto [l, r] : it.second) {
      insert(rmp[l], rmp[r]-1);
    }
    if(sum[1] > 0) {
      return false;
    }
  }
  return true;
}

int A[N], B[N], X[N], Y[N];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    int minx, miny, maxx, maxy, minu, maxu, mind, maxd;
    minx = miny = minu = mind = INF;
    maxx = maxy = maxu = maxd = -INF;
    for(int i=0; i<n; i++) {
      cin >> A[i] >> B[i] >> X[i] >> Y[i];
      A[i] *= 2; B[i] *= 2;
      X[i] *= 2; Y[i] *= 2;
      minx = min(minx, A[i]);
      minx = min(minx, X[i]);
      maxx = max(maxx, A[i]);
      maxx = max(maxx, X[i]);
      miny = min(miny, B[i]);
      miny = min(miny, Y[i]);
      maxy = max(maxy, B[i]);
      maxy = max(maxy, Y[i]);
      minu = min(minu, A[i]+B[i]);
      minu = min(minu, X[i]+Y[i]);
      maxu = max(maxu, A[i]+B[i]);
      maxu = max(maxu, X[i]+Y[i]);
      mind = min(mind, A[i]-Y[i]);
      mind = min(mind, X[i]-B[i]);
      maxd = max(maxd, A[i]-Y[i]);
      maxd = max(maxd, X[i]-B[i]);
    }

    vector<tuple<int,int,int>> ans;
    vector<Segment> segs(4*n);

    for(int i=0; i<n; i++) {
      int mid = (minx + maxx) / 2;
      segs[4*i + 0] = {A[i], B[i], Y[i]};
      segs[4*i + 1] = {X[i], B[i], Y[i]};
      segs[4*i + 2] = {2*mid - A[i], B[i], Y[i]};
      segs[4*i + 3] = {2*mid - X[i], B[i], Y[i]};
    }
    if(solve(segs)) {
      int a = 2;
      int b = 0;
      int c = (minx + maxx) / 2;
      int g = abs(__gcd(__gcd(a, b), c));
      ans.push_back(make_tuple(a/g, b/g, c/g));
    }

    for(int i=0; i<n; i++) {
      int mid = (miny + maxy) / 2;
      segs[4*i + 0] = {B[i], A[i], X[i]};
      segs[4*i + 1] = {Y[i], A[i], X[i]};
      segs[4*i + 2] = {2*mid - B[i], A[i], X[i]};
      segs[4*i + 3] = {2*mid - Y[i], A[i], X[i]};
    }
    if(solve(segs)) {
      int a = 0;
      int b = 2;
      int c = (miny + maxy) / 2;
      int g = abs(__gcd(__gcd(a, b), c));
      ans.push_back(make_tuple(a/g, b/g, c/g));
    }

    for(int i=0; i<n; i++) {
      int mid = (minu + maxu) / 2;
      int ga = 2*mid - (A[i] + B[i]);
      int na = (ga + (A[i]-B[i])) / 2;
      int nb = (ga - (A[i]-B[i])) / 2;
      int gx = 2*mid - (X[i] + Y[i]);
      int nx = (gx + (X[i]-Y[i])) / 2;
      int ny = (gx - (X[i]-Y[i])) / 2;
      segs[4*i + 0] = {A[i], B[i], Y[i]};
      segs[4*i + 1] = {X[i], B[i], Y[i]};
      segs[4*i + 2] = {na, min(nb, ny), max(nb, ny)};
      segs[4*i + 3] = {nx, min(nb, ny), max(nb, ny)};
    }
    if(solve(segs)) {
      int a = 2;
      int b = 2;
      int c = (minu + maxu) / 2;
      int g = abs(__gcd(__gcd(a, b), c));
      ans.push_back(make_tuple(a/g, b/g, c/g));
    }

    for(int i=0; i<n; i++) {
      int mid = (mind + maxd) / 2;
      int ga = 2*mid - (A[i] - B[i]);
      int na = (ga + (A[i]+B[i])) / 2;
      int nb = (-ga + (A[i]+B[i])) / 2;
      int gx = 2*mid - (X[i] - Y[i]);
      int nx = (gx + (X[i]+Y[i])) / 2;
      int ny = (-gx + (X[i]+Y[i])) / 2;
      segs[4*i + 0] = {A[i], B[i], Y[i]};
      segs[4*i + 1] = {X[i], B[i], Y[i]};
      segs[4*i + 2] = {na, min(nb, ny), max(nb, ny)};
      segs[4*i + 3] = {nx, min(nb, ny), max(nb, ny)};
    }
    if(solve(segs)) {
      int a = 2;
      int b = -2;
      int c = (mind + maxd) / 2;
      int g = abs(__gcd(__gcd(a, b), c));
      ans.push_back(make_tuple(a/g, b/g, c/g));
    }

    sort(ans.begin(), ans.end(), greater<tuple<int,int,int>>());
    cout << ans.size() << nl;
    for(auto [a, b, c] : ans) {
      cout << a << " " << b << " " << c << " ";
    }
    cout << nl;
  }

  return 0;
}
