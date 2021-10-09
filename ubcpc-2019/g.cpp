#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// DON'T USE THESE MACROS DURING ICPC PRACTICE
#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
  os<<"[ ";
  for(const T& it: v) os<<it<<", ";
  return os<<"]";
}

vector<int> convert(const string& s) {
  vector<int> res(101);
  int open = 0;
  stack<int> memo;
  int cur = 0;
  int depth = 0;
  for(char c:s) {
    if(c=='[') {
      open++;
      memo.push(cur);
      cur = 0;
    } else if(c==']') {
      if(cur>0) {
        depth = max(depth,open);
      }
      open--;
      cur = memo.top();
      memo.pop();
    } else {
      cur++;
    }
    if(open==0 && (cur>0 || depth>0)) {
      for(int i=0;i<depth;i++) {
        res[100-i] = 0;
      }
      res[100-depth]++;
      cur = 0;
      depth = 0;
    }
  }
  return res;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin>>n;
  string s[n];
  pair<vector<int>,int> v[n];
  for(int i=0;i<n;i++) {
    cin>>s[i];
    v[i] = make_pair(convert(s[i]),i);
  }
  sort(v,v+n);
  for(int i=0;i<n;i++) {
    cout<<s[v[i].second]<<nl;
  }

  return 0;
}
