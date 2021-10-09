#!/usr/bin/ruby
include Math

n = readline().to_i
a = readline().split().map(&:to_i)
cnt = []
for i in 0..1000
  cnt.push(0)
end

zero = 0
ans = []
for i in 0..n-1
  if a[i] >= 0
    cnt[a[i]] += 1
    if a[i] == 0
      zero += 1
    end
  else 
    if cnt[-a[i]] > 0
      cnt[-a[i]] -= 1
    elsif cnt[0] > 0
      cnt[0] -= 1
      ans.push(-a[i])
    else
      bad = true
      break
    end
  end
end

if bad
  puts "No"
else
  puts "Yes"
  while ans.size() < zero
    ans.push(1)
  end
  puts ans.join(" ")
end

