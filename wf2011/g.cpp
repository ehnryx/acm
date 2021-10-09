#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,avx,abm,popcnt,mmx,tune=native")

#define nl '\n'

typedef long long ll;
typedef float ld;
typedef complex<ld> pt;
typedef pair<int,int> pii;

const ld PI = acos((ld)-1);
const int BS = 50;

const int N = 500+1;
int len[N];

ld sqr(ld x) { return x*x; }

ld get(int s, int t, ld r) {
  ld res = 0;
  for (int i=s; i<=t; i++) {
    res += asin((ld)len[i]/2/r);
  }
  return 2*res;
}

ld get_area1(int s, int t, ld r) {
  int maxv = 0;
  ld res = 0;
  for (int i=s; i<=t; i++) {
    maxv = max(maxv, len[i]);
    res += sqrt(sqr(r)-sqr((ld)len[i]/2)) * len[i];
  }
  return res/2 - sqrt(sqr(r)-sqr((ld)maxv/2)) * maxv;
}

ld get_area2(int s, int t, ld r) {
  ld res = 0;
  for (int i=s; i<=t; i++) {
    res += sqrt(sqr(r)-sqr((ld)len[i]/2)) * len[i];
  }
  return res/2;
}

ld solve2(int s, int t) {
  if (t-s+1 < 3) return 0;

  int maxv = 0;
  int sum = 0;
  for (int i=s; i<=t; i++) {
    maxv = max(maxv, len[i]);
    sum += len[i];
  }
  if (2*maxv >= sum) {
    return 0;
  }

  ld init = get(s, t, (ld)maxv/2) - PI;
  if (init < PI) {
    ld left = (ld)maxv/2;
    ld right = 1e7;
    for (int bs=0; bs<BS; bs++) {
      ld mid = (left+right)/2;
      ld ang = get(s, t, mid);
      ld big = 2*asin((ld)maxv/2/mid);
      if (ang-big < big) {
        left = mid;
      } else {
        right = mid;
      }
    }
    return get_area1(s, t, left);
  }
  else {
    ld left = (ld)maxv/2;
    ld right = 1e7;
    for (int bs=0; bs<BS; bs++) {
      ld mid = (left+right)/2;
      ld ang = get(s, t, mid);
      if (ang > 2*PI) {
        left = mid;
      } else {
        right = mid;
      }
    }
    return get_area2(s, t, left);
  }
}

ld solve(int s, int t) {
  if (t-s+1 < 3) return 0;
  int maxv = s;
  for (int i=s+1; i<=t; i++) {
    if (len[i] > len[maxv]) {
      maxv = i;
    }
  }
  ld all = solve2(s, t);
  ld left = solve(s, maxv-1);
  ld right = solve(maxv+1, t);
  return max(all, left+right);
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout << fixed << setprecision(17);

  for (int n, tt=1; cin>>n && n; tt++) {
    for (int i=1; i<=n; i++) {
      cin >> len[i];
    }
    cout << "Case " << tt << ": " << solve(1,n) << nl;
  }

  return 0;
}
