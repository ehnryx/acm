#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;

inline char get() {
  static char buf[100000], *S = buf, *T = buf;
  if (S == T) {
    T = (S = buf) + fread(buf, 1, 100000, stdin);
    if (S == T) return EOF;
  }
  return *S++;
}
inline void read(int& x) {
  static char c; x = 0;
  for (c = get(); c < '0' || c > '9'; c = get());
  for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + c - '0';
}
inline void readll(ll& x) {
  static char c; x = 0;
  for (c = get(); c < '0' || c > '9'; c = get());
  for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + c - '0';
}

const int N = 3e5+1;

int n;
int a[N], ileft[N], iright[N];
vector<pii> sorted;

void output(ll lb, ll ub) {
  //cerr << "OUTPUT " << lb << " " << ub << nl;

  vector<ll> res;
  for (const pii& it : sorted) {
    int val = it.first;
    int idx = it.second;
    ll maxv = ub/val;
    ll minv = (lb+val-1)/val;
    ll left = ileft[idx];
    ll right = iright[idx];

    if (minv <= maxv && minv <= (right-left-1)) {
      for (int i=max((ll)idx,left+minv); i<min(right,idx+maxv); i++) {
        for (int j=max(left,i-maxv); j<min((ll)idx,i-minv+1); j++) {
          res.push_back((ll)(i-j)*val);
        }
      }
    }
  }
  sort(res.begin(), res.end());

  for (ll it : res) {
    cout << it << " ";
  }
}

ll linear(ll ub) {
  ll res = 0;
  for (const pii& it : sorted) {
    int val = it.first;
    int idx = it.second;
    ll len = ub/val;
    ll left = ileft[idx];
    ll right = iright[idx];

    if (len >= right-left-1) {
      res += (ll)(idx-left) * (right-idx);
    }
    else {
      left = max(left, idx-len);
      right = min(right, idx+len);
      int offset = left+len-idx;
      int range = min(idx-left, right-(left+len));
      res += (ll)range*(range+1)/2 + (ll)offset*range + (ll)(right-idx)*(idx-left-range);
    }
  }
  return res;
}

ll find(ll goal) {
  //cerr << "FIND " << goal << endl;
  ll l = 0;
  ll r = (ll)n*INF;
  while (l<r) {
    ll mid = (l+r)/2;
    ll cnt = linear(mid);
    ////cerr << mid << " -> " << cnt << nl;
    if (cnt < goal) {
      l = mid+1;
    } else {
      r = mid;
    }
  }
  //cerr << "goal: " << linear(l) << " " << linear(l-1) << endl;
  assert(l==r);
  return l;
}

void solve(ll lid, ll lval, ll rid, ll rval) {
  //cerr << "SOLVE " << lval << " " << rval << endl;
  if (lval == rval) {
    for (ll i=lid; i<=rid; i++) {
      cout << lval << " ";
    }
    cout << nl;
  }
  else {
    ll left = linear(lval);
    ll right = linear(rval-1);
    //cerr << "left: " << left << "   right: " << right << endl;
    for (ll i=lid; i<=left; i++) {
      cout << lval << " ";
    }
    if (lval+1 <= rval-1) {
      output(lval+1, rval-1);
    }
    //cerr << "right+1 " << right+1 << " " << rid << endl;
    //cerr << linear(rval) << endl;
    for (ll i=right+1; i<=rid; i++) {
      cout << rval << " ";
    }
    cout << nl;
  }
}

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  read(n);
  for (int i=0; i<n; i++) {
    read(a[i]);
    sorted.push_back(pii(a[i], i));
  }
  sort(sorted.begin(), sorted.end());

  set<int> done;
  done.insert(-1);
  done.insert(n);
  for (const pii& it : sorted) {
    int idx = it.second;
    ileft[idx] = *prev(done.lower_bound(idx));
    iright[idx] = *done.lower_bound(idx);
    done.insert(idx);
  }

  //int q; cin >> q; while (q--) {
  ll left, right;
  readll(left); readll(right);

  ll leftv = find(left);
  ll rightv = find(right);
  solve(left, leftv, right, rightv);
  //}

  return 0;
}
