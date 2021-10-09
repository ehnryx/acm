#include <iostream>
#include <iomanip>
#include <cassert>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <random>
#include <chrono>
#include <utility>
using namespace std;

#define _USE_MATH_DEFINES

typedef long long ll;
typedef double ld;

const char nl = '\n';
const ll MOD = 1e9+7;
const ld EPS = 1e-11;
const ld BS = 3e-8;

mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
  for(T it:v) { os<<it+1<<" "; }
  return os;
}

struct Answer {
  ld d,x,y;
  vector<int> id;
  bool operator < (const Answer& o) const {
    return d<o.d;
  }
  friend ostream& operator << (ostream& os, const Answer& v) {
    os<<v.d<<nl;
    os<<v.x<<" "<<v.y<<nl;
    return os<<v.id;
  }
};

const int N = 2e3+1;
int a[N],b[N];

ld lp_dist(ld x, ld y, int i) {
  if(abs(y)<EPS) {
    return abs(b[i]);
  } else {
    return abs(y*a[i]-x*b[i])/sqrt(x*x+y*y);
  }
}

ld calc(int n, int k, ld q, ld& x, ld& y, vector<int>& id) {
  id.clear();
  x = cos(q);
  y = sin(q);
  vector<pair<ld,int>> p;
  for(int i=0;i<n;i++) {
    p.push_back(make_pair(lp_dist(x,y,i),i));
  }
  nth_element(p.begin(),p.begin()+k-1,p.end());
  ld sum = 0;
  for(int i=0;i<k;i++) {
    sum += p[i].first;
    id.push_back(p[i].second);
  }
  return sum;
}

Answer search(int n, int k, ld left, ld right) {
  vector<int> id;
  ld x, y;
  while(right-left>BS) {
    ld ml=(9*left+8*right)/17;
    ld mr=(8*left+9*right)/17;
    if(calc(n,k,ml,x,y,id) > calc(n,k,mr,x,y,id)) {
      right = mr;
    } else {
      left = ml;
    }
  }
  ld d = calc(n,k,(left+right)/2,x,y,id);
  return Answer{d,x,y,id};
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout<<fixed<<setprecision(13);

  int n,k;
  cin>>n>>k;
  vector<ld> p;
  vector<int> r;
  r.push_back(n);
  for(int i=0;i<n;i++) {
    cin>>a[i]>>b[i];
    ld cur = (a[i]||b[i] ? atan2(b[i],a[i]) : 0);
    if(cur<0) cur += M_PI;
    p.push_back(cur);
    r.push_back(i);
  }
  p.push_back(0);
  p.push_back(M_PI);
  sort(p.begin(),p.end());
  shuffle(r.begin()+2,r.end(),rng);

  Answer ans = Answer{-1};
  for(int i=0;i<n+1&&clock()<3.9*CLOCKS_PER_SEC;i++) {
    ans = max(ans, search(n,k,p[r[i]],p[r[i]+1]));
  }
  cout<<ans<<nl;

  return 0;
}
