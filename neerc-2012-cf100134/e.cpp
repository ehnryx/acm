#include <bits/stdc++.h>

using namespace std;

#define FILENAME "exact"

#define nl '\n'
typedef long long ll;
typedef long double ld;

const int N = 20;
ll x;
int n;
ll POW10[N];

void pre() {
  POW10[0] = 1ll;
  for(int i = 1; i < N; ++i) {
    POW10[i] = POW10[i-1]*10ll;
  }
}

vector<pair<ll,int>> box[N];
ll need[N], have[N];
vector<int> opened;

void bpush(int i) {
  for (int j = 0; j < i; ++j) {
    if (have[j] >= 10) {
      have[j+1] += have[j]/10;
      have[j] %= 10;
    }
  }
}

void bopen(int i) {
  ll v; int idx;
  tie(v,idx) = box[i].back(); box[i].pop_back();
  //fprintf(stderr, "opening box %d\n", idx);
  opened.push_back(idx);
  if (v == 0) {
    cout << -1 << nl;
    exit(0);
  }
  have[i] += v;
}

int bmax(int i) {
  int ans = 0;
  for(int j=0; j <= i;++j) {
    if (box[ans].back().first*POW10[ans] < box[j].back().first*POW10[j]) {
      ans = j;
    }
  }
  return ans;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif
  pre();
  cin >> x >> n;
  for(int i=0; i < n; ++i) {
    ll k, q;
    cin >> k >> q;
    box[k].emplace_back(q, i+1);
  }
  for(int i = 0; i < N; ++i) {
    sort(box[i].rbegin(), box[i].rend());
    box[i].emplace_back(0ll, 0);
    reverse(box[i].begin(), box[i].end());
    // stack big to small, sentinel 0
  }
  for(int i=0; x > 0; ++i) {
    need[i] = x % 10;
    x /= 10;
  }
  for(int i = 0; i < N; ++i) {
    if (!need[i]) continue;
    bpush(i);
    //fprintf(stderr, "need %lld of %d\n", need[i], i);
    while (need[i] > have[i]) {
      bopen(bmax(i));
      bpush(i);
    }
    have[i] -= need[i];
  }
  cout << opened.size() << nl;
  sort(opened.begin(), opened.end());
  for(int v: opened) {
    cout << v << " ";
  }
  cout << nl;
  return 0;
}

