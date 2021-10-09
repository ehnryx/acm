#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <vector>
#include <map>
#include <queue>
using namespace std;

typedef long long ll;
typedef long double ld;

const char nl = '\n';

template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
  os<<"[ "; for(T it:v) { os<<it<<", "; }
  return os<<"]";
}

const int N = 1<<18;
ld segt[2*N];
bool lazy[2*N];

void push(int i) {
  if(lazy[i]) {
    segt[2*i] = segt[2*i+1] = segt[i]/2;
    lazy[2*i] = lazy[2*i+1] = true;
    lazy[i] = false;
  }
}

void pull(int i) {
  segt[i] = segt[2*i] + segt[2*i+1];
}

void insert(int l, int r, ld v, int i=1, int s=0, int e=N-1) {
  if(r<s||e<l) return;
  if(l<=s&&e<=r) {
    segt[i] = v*(e-s+1);
    lazy[i] = true;
    return;
  }
  push(i);
  int m = (s+e)/2;
  insert(l,r,v,2*i,s,m);
  insert(l,r,v,2*i+1,m+1,e);
  pull(i);
}

ld query(int l, int r, int i=1, int s=0, int e=N-1) {
  if(r<s||e<l) return 0;
  if(l<=s&&e<=r) {
    return segt[i];
  }
  push(i);
  int m = (s+e)/2;
  return query(l,r,2*i,s,m) + query(l,r,2*i+1,m+1,e);
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout<<fixed<<setprecision(13);

  int n,m;
  cin>>n>>m;
  for(int i=1;i<=n;i++) {
    int a;
    cin>>a;
    insert(i,i,a);
  }

  for(int i=0;i<m;i++) {
    string s;
    cin>>s;
    if(s=="get") {
      int a;
      cin>>a;
      cout<<query(a,a)<<nl;
    } else {
      int a,b;
      cin>>a>>b;
      ld sum = query(a,b);
      insert(a,b,sum/(b-a+1));
    }
  }

  return 0;
}
