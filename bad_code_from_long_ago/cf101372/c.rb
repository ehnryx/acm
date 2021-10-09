tests = gets().to_i
for i in 1..tests
  left, right = gets().split()
  llen = left.length
  rlen = right.length

  ans = 0

  if rlen == llen
    if llen == 1
      ans += right.to_i - left.to_i + 1
    else
      lmid = left[1..llen-2].to_i
      rmid = right[1..rlen-2].to_i
      lmid += 1 if left[llen-1].ord > left[0].ord
      rmid += 1 if right[rlen-1].ord >= right[0].ord
      if left[0] == right[0]
        ans += rmid - lmid
      else
        ans += 10**(llen-2) - lmid
        ans += rmid
        ans += 10**(llen-2) * (right[0].ord - left[0].ord - 1)
      end
    end
  else
    # first part
    if llen == 1
      ans += 10-left.to_i
    else
      mid = left[1..llen-2].to_i
      mid += 1 if left[llen-1].ord > left[0].ord
      ans += 10**(llen-2) - mid
      ans += 10**(llen-2) * (9 - left[0].to_i)
    end

    # second part
    mid = right[1..rlen-2].to_i
    mid += 1 if right[rlen-1].ord >= right[0].ord
    ans += mid
    ans += 10**(rlen-2) * (right[0].to_i - 1)

    # middle part
    for i in llen+1..rlen-1
      ans += 9 * 10**(i-2)
    end
  end

  puts ans
end
