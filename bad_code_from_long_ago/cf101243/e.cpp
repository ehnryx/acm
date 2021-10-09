#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

inline void srand() { srand(clock() + time(nullptr)); }

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
  os << "(" << v.first << "," << v.second << ")"; return os;
}

template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
  for (const T& it : v) os << it << " "; return os;
}

template <class T>
inline T sqr(T x) { return x*x; }

const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
//const ld PI = M_PIl;
////////////////////////////////////////////////////////////////////////

const ll MOD = 1e9+7;
const ld EPS = 1e-9;



int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  ll N, K;
  cin >> N >> K;
  vector<ll> a(N);
  ll x = 0;
  for(ll i=0;i<N;++i) {
    cin >> a[i];
    if(a[i] > a[x])
      x=i;
  }
  ++x;
  ll e1 = 0, e2= 0;
  for(ll i=0;i<x-1;++i) {
    e1 += a[i]-1;
  }
  for(ll i=x;i<N;++i) {
    e2 += a[i]-1;
  }
  ll et = e1+e2;
  ll ex = e1;
  ////cerr << "e1 " << e1 << " et " << et<< endl;

  ll sum = x-1;
  if(sum > K) {
    cout << "KEK" << endl;
    return 0;
  }

  ll gp = a[x-1]+N-1;
  ll ct = (K-sum)/gp;
  ex += et*ct;
  sum += ct*gp;
  ////cerr << "ct " << ct << " x " << x <<" gp " << gp <<endl;
  
  ll remain = K-sum;
  ////cerr << "REMAIN "<< remain << ", EX " << ex << endl;
  if(ex >= remain)
    cout << "YES" << endl;
  else
    cout << "KEK" << endl;
  

  return 0;
}
