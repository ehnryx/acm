#include <bits/stdc++.h>
using namespace std;

//%:include "io/fast_input.h"

//%:include "number/int_base10.h"

using ll = long long;
//using ld = long double;
using ld = double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-24L;
random_device _rd; mt19937 rng(_rd());

//using Int = int_base10;

#pragma pack(push, 1)
struct state_t {
  uint8_t y;
  uint32_t x;
  state_t() = default;
  state_t(ll v): y(v >> 32), x(v) {}
  ll big() const { return (ll)y << 32 | x; }
  bool operator < (state_t o) const { return big() < o.big(); }
  bool operator == (state_t o) const { return big() == o.big(); }
  state_t add(int i, int v) {
    ll have = big() >> (6*i + 2) & 0b111111;
    return state_t(big() ^ (have ^ (have + v)) << (6*i + 2));
  }
  bool done() const { return x & 0b11; }
  bool win() const { return x & 2; }
  bool set_lose() { x |= 1; return false; }
  bool set_win() { x |= 2; return true; }
  void clear() { x &= ~0b11; }
  bool memoize() const {
    int sum = 0;
    for(int i=0; i<6; i++) {
      sum += big() >> (6*i + 2) & 0b111111;
    }
    return sum % 2;
  }
};
#pragma pack(pop)

const int N = 74974368;

//state_t all[N];

/*
void build(int at, vector<char> state, ld v, const vector<ld>& fs, int& aid) {
  if(at == size(state)) {
    state_t bm = 0;
    for(int i=0; i<size(state); i++) {
      bm = bm.add(i, state[i]);
    }
    all[aid++] = bm;
    return;
  }
  while(v > 1) {
    build(at + 1, state, v, fs, aid);
    v *= fs[at];
    state[at]++;
  }
}
*/

const int MAGIC = 1;

//bool solve(state_t state, Int n, Int d, const vector<Int>& fs) {
//bool solve(state_t state, ld v, const vector<ld>& fs, int m) {
bool solve(state_t state, ld v, const vector<ld>& fs, set<state_t>& memo) {
  //if(n <= d) return false;
  if(v <= 1/* + EPS*/) return false;
  //auto it = lower_bound(all, all + m, state);
  //if(it->done()) return it->win();
  if(state.memoize()) {
    auto it = memo.lower_bound(state);
    if(it != memo.end() && (it->big() >> 2) == (state.big() >> 2)) return it->win();
  }
  for(int i=0; i<size(fs); i++) {
    //if(!solve(state.add(i, 1), n*fs[i], d*(int)1e6, fs)) {
    //if(!solve(state.add(i, 1), v*fs[i], fs, m)) {
    if(!solve(state.add(i, 1), v*fs[i], fs, memo)) {
      //return it->set_win();
      if(state.memoize()) {
        state_t add = state;
        add.set_win();
        memo.insert(add);
      }
      return true;
    }
  }
  //return it->set_lose();
  if(state.memoize()) {
    state.set_lose();
    memo.insert(state);
  }
  return false;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int T;
  cin >> T;
  while(T--) {
    ld n;
    int k;
    cin >> n >> k;
    //vector<Int> fs;
    vector<ld> fs(k);
    for(int i=0; i<k; i++) {
      //double x;
      //cin >> x;
      //fs.emplace_back((int)round(x * 1e6));
      cin >> fs[i];
    }
    sort(begin(fs), end(fs));
    //int m = 0;
    //build(0, vector<char>(6), n, fs, m);
    //sort(all, all + m);
    //if(solve(0, (int)round(n * 1e6), (int)1e6, fs)) {
    //if(solve(0, n, fs, m)) {
    set<state_t> memo;
    if(solve(0, n, fs, memo)) {
      cout << "Nils" << nl;
    } else {
      cout << "Mikael" << nl;
    }
    /*
    if(T) {
      for(int i=0; i<N; i++) {
        all[i].clear();
      }
    }
    */
  }

  return 0;
}
