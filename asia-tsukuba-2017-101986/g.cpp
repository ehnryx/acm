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
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const ld PI = acos((ld)-1);
const ld half = (ld)1/2;
const ld sqrt3 = sqrt((ld)3)/2;
const ld d60 = PI/3;

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
inline pt line_inter(const pt &a, const pt &b, const pt &c, const pt &d) {
  return a + cp(c - a, d - c) / cp(b - a, d - c) * (b - a);
}

string solve(char a, char b, char c, char d, ld x, ld ang, ld len) {
  //cerr<<"solving "<<a<<','<<b<<','<<c<<','<<d<<": "<<x<<" "<<ang<<" "<<len<<nl;
  pt S(x,0), A(0,0), B(1,0), C(half,sqrt3);
  pt D = S + exp(pt(0,ang));
  if(ang < arg(C-S)) {
    pt T = line_inter(B,C,S,D);
    ld dist = abs(T-S);
    if(len < dist) {
      string s = {a,b,c};
      sort(s.begin(),s.end());
      return s;
    } else {
      return solve(c, b, d, a, abs(C-T), ang+d60, len-dist);
    }
  } else {
    pt T = line_inter(A,C,S,D);
    ld dist = abs(T-S);
    if(len < dist) {
      string s = {a,b,c};
      sort(s.begin(),s.end());
      return s;
    } else {
      return solve(a, c, d, b, abs(A-T), ang-d60, len-dist);
    }
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  char x[2],y[2];
  int d[2],l[2];
  string res[2];
  for(int i=0;i<2;i++) {
    //cerr<<"SOLVE "<<i<<nl;
    cin>>x[i]>>y[i]>>d[i]>>l[i];
    char c = y[i]+1;
    if(c>'D') c = 'B';
    res[i] = solve('A',x[i],y[i],c,0,d[i]*PI/180,l[i]);
    //cerr<<res[i]<<nl;
    //cerr<<nl;
  }
  cout<<(res[0]==res[1] ? "YES" : "NO")<<nl;

  return 0;
}
