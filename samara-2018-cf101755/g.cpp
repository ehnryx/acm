#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 1<<18;
struct BIT {
  ll freq[N];
  BIT() { memset(freq, 0, sizeof freq); }
  void insert(int x, int c) {
    for (x += 1 ; x < N; x += x & -x) freq[x] += c;
  }
  ll query(int x) {
    ll res = 0;
    for (x += 1; x > 0; x -= x & -x) res += freq[x];
    return res;
  }
  ll query(int lx, int rx) {
    return query(rx) - query(lx-1);
  }
};

struct SegTree {
  ll sum[2*N];
  SegTree() { memset(sum, 0, sizeof sum); }
  void build(int n, int a[], int p) {
    for (int i = p; i < n; i+=2) sum[i+N] = a[i];
    for (int i = N-1; i > 0; i--) sum[i] = sum[2*i] + sum[2*i+1];
  }

  void update(int id, int x) {
    id += N;
    sum[id] = x;
    for (id/=2; id > 0; id/=2) sum[id] = sum[2*id] + sum[2*id+1];
  }

  ll query(int l, int r) {
    ll res = 0;
    for (l+=N, r+=N+1; l < r; l /= 2, r /= 2) {
      if (l&1) res += sum[l++];
      if (r&1) res += sum[--r];
    }
    return res;
  }

  void print(int n) {
    //cerr << "SEGT: ";
    for (int i = 0; i < n; i++) {
      //cerr << query(i, i) << " ";
    }
    //cerr << nl;
  }
};

BIT fbig[2], fsmall[2];
SegTree big[2], small[2];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n, k;
  cin >> n >> k;
  int p = (k%2)^1;

  vector<pii> idx;
  int a[n];
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    idx.push_back(pii(a[i], i));
    fbig[i%2].insert(i, 1);
  }
  sort(idx.begin(), idx.end());
  for (int i = 0; i < 2; i++) {
    big[i].build(n, a, i);
  }

  ll ans = 0;
  for (const pii& it : idx) {
    // query
    int id = it.second%2;
    int first = max(it.second, k-1-it.second);
    int last = min(it.second+k-1, it.second+k-1 - 2*(it.second+k-n));
    //cerr << it.second << ": " << "QUERY: " << first << " " << last << nl;
    // inclusive
    if (first <= last) {
      ll big_sum = big[id^p].query(first, last);
      ll small_sum = small[id^p].query(first, last);
      ll big_cnt = fbig[id^p].query(first, last);
      ll small_cnt = fsmall[id^p].query(first, last);
      ans += big_sum - big_cnt*it.first;
      ans += small_cnt*it.first - small_sum;
      //cerr << big_sum << " " << big_cnt << "  ///  " << small_sum << " " << small_cnt << nl;
      //cerr << "diff: " << big_sum-big_cnt*it.first + small_cnt*it.first-small_sum << nl;
    }

    //cerr << "b0:"; big[0].print(n);
    //cerr << "b1:"; big[1].print(n);
    //cerr << "s0:"; small[0].print(n);
    //cerr << "s1:"; small[1].print(n);
    //cerr << "ans: " << ans << nl;
    //cerr << nl;

    // update
    fbig[id].insert(it.second, -1);
    fsmall[id].insert(it.second, 1);
    big[id].update(it.second, 0);
    small[id].update(it.second, it.first);
  }
  cout << ans << nl;

  return 0;
}
