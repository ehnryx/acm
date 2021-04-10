a = [list('.'*8 + input() + '.'*8) for i in range(8)]

r = 0
def g(n):
  global a, r
  if n < 8:
    for i in range(8, 16):
      if a[n][i] == '.':
        for j in range(n):
          if 'x' in [a[j][i], a[j][i-n+j], a[j][i+n-j]]:
            break
        else:
          a[n][i] = 'x'
          g(n+1)
          a[n][i] = '.'
  else: r += 1
g(0)

print(r)
