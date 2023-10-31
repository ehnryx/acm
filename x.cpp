#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr char nl = '\n';
random_device _rd; mt19937 rng(_rd());


//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int T = 1;
#if defined(MULTI_TEST) or defined(PRINT_CASE)
  cin >> T;
#endif
  for(int testnum=1; testnum<=T; testnum++) {
#define MAKE_STRING_IMPL(STRING) #STRING
#define MAKE_STRING(STRING) MAKE_STRING_IMPL(STRING)
#ifdef PRINT_CASE
    cout << "Case " << MAKE_STRING(PRINT_CASE) << testnum << ": ";
#endif
    solve_main(testnum, cin);
  }

  return 0;
}
