import os
### START FAST IO ###
os_input = os.read(0, int(1e7)).split()
os_input_pos = -1
answer_list = []
def read_s():
  global os_input_pos
  os_input_pos += 1
  return os_input[os_input_pos].decode()
def read_i():
  return int(read_s())
def write_s(v):
  answer_list.append(v)
def write_i(v):
  write_s(str(v))
def print_ans():
  os.write(1, "\n".join(answer_list).encode())
  os.write(1, "\n".encode())
#### END FAST IO ####

MOD = int(1e9 + 7)
N = int(2e6 + 1)
dp = [None, (0, 0), (0, 0)]
for i in range(3, N):
  use = max(dp[i-1][0] + 2*dp[i-2][0], dp[i-1][1] + 2*dp[i-2][1] + 4)
  skip = dp[i-1][0] + 2*dp[i-2][0]
  dp.append((use % MOD, skip % MOD))

T = read_i()
while T:
  T -= 1
  n = read_i()
  write_i(dp[n][0])


print_ans()

