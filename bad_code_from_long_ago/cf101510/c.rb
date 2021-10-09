def valid(arr, len, k)
  good = -1
  n = arr.length
  arr.push(0x3f3f3f3f3f3f3f3f3f)
  idarr = 0..n
  for i in 0..n-1
    # cur = arr.bsearch_index{|x| x > arr[i]+len} - i
    cur = idarr.bsearch{|x| arr[x] > arr[i]+len} - i
    if cur < k and good < i
      return false
    elif cur >= k
      good = i+cur-1
    end
  end
  return true
end

n, k = readline().split().map(&:to_i)
arr = readline().split().map(&:to_i).sort()

left = 0
right = 2*10**9+1
ans = 0
while left <= right
  ans = (left+right)/2
  if valid(arr, ans, k)
    right = ans-1
  else
    left = ans+1
  end
end

if not valid(arr, ans, k)
  ans += 1
end

puts ans
