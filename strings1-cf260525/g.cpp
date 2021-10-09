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
typedef vector<int> vi;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

// get_sarray()[i] = idx of suffix s[i..L-1] in list of sorted suffixes
struct suff_array {
  const int L; int skip, lvl;
  vector<vi> P; vector<pair<pii,int>> M;
  suff_array(const string &s) : L(s.size()), P(1, vi(L, 0)), M(L) {
    for (int i = 0; i < L-(L==1); i++) P[0][i] = int(s[i]);
    for (skip = 1, lvl = 1; skip < L; skip *= 2, lvl++) {
      P.push_back(vi(L, 0));
      for (int i = 0; i < L; i++)
        M[i] = {{P[lvl-1][i], i+skip<L ? P[lvl-1][i + skip] : -1000}, i};
      sort(M.begin(), M.end());
      for (int i = 0; i < L; i++)
        P[lvl][M[i].second] = (i > 0 && M[i].first == M[i-1].first) ?
            P[lvl][M[i-1].second] : i; } }
  const vi& get_sarray() { return P.back(); }
  //returns len of longest common prefix of s[i...L-1] and s[j...L-1], O(lg L)
  int lcp(int i, int j) const {
    int len = 0; if (i == j) return L - i;
    for (int k = P.size() - 1; k >= 0 && i < L && j < L; k--)
      if (P[k][i] == P[k][j]) { i += 1 << k; j += 1 << k; len += 1 << k; }
    return len; }
};

const int N = 1e6+1;
int idx[N], inv[N];

ll bit[N];

void insert(int x, ll v) {
  for(;x<N;x+=x&-x) {
    bit[x] += v;
  }
}
void insert_range(int l, int r, ll v) {
  insert(l, v);
  insert(r+1, -v);
}
ll query(int x) {
  ll res = 0;
  for(;x;x-=x&-x) {
    res += bit[x];
  }
  return res;
}

struct Count {
  int a, b, c;
  Count(): a(0), b(0), c(0) {}
  Count(int x, int y, int z): a(x), b(y), c(z) {}
  ll operator * (const Count& o) const {
    return (ll)a*b*o.c + (ll)a*o.b*c + (ll)o.a*b*c
      + (ll)o.a*o.b*c + (ll)o.a*b*o.c + (ll)a*o.b*o.c;
  }
  Count operator + (const Count& o) const {
    return Count(a+o.a, b+o.b, c+o.c);
  }
};

ostream& operator << (ostream& os, const Count& v) {
  return os << "( " << v.a << " " << v.b << " " << v.c << " )";
}

int alen, blen, clen;
Count solve(const suff_array& sa, int l, int r) {
  //cerr<<"solving "<<l<<" "<<r<<nl;
  if(l == r) {
    //cerr<<"got to leaf @ "<<l<<" "<<r<<nl;
    Count res;
    if(inv[r] < alen) res.a = 1;
    else if(alen < inv[r] && inv[r] < alen+blen+1) res.b = 1;
    else if(alen+blen+1 < inv[r]) res.c = 1;
    return res;
  }

  int minv = sa.lcp(inv[l], inv[r]);
  int left = l+1;
  int right = r;
  while(left < right) {
    int mid = (left+right)/2;
    if(sa.lcp(inv[l], inv[mid]) == minv) {
      right = mid;
    } else {
      left = mid+1;
    }
  }

  Count lres = solve(sa, l, left-1);
  Count rres = solve(sa, left, r);
  //cerr<<"got "<<lres<<" and "<<rres<<" from "<<l<<" "<<left-1<<" and "<<left<<" "<<r<<nl;
  ll add = lres * rres;
  insert_range(1, minv, add);
  return lres + rres;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  string a,b,c;
  cin >> a >> b >> c;
  alen = a.size();
  blen = b.size();
  clen = c.size();

  suff_array sa(a+" "+b+"."+c);
  int n = alen+blen+clen+2;
  for(int i=0; i<n; i++) {
    idx[i] = sa.get_sarray()[i];
    inv[idx[i]] = i;
  }

  Count result = solve(sa, 0, n-1);
  //cerr<<"result: "<<result<<nl;
  int len = min(alen, min(blen, clen));
  for(int i=1; i<=len; i++) {
    cout << query(i) % MOD << " ";
  }
  cout << nl;

  return 0;
}
