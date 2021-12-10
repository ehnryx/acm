import sys

s = {}

s[')'] = 1
s[']'] = 2
s['}'] = 3
s['>'] = 4

s['('] = s[')']
s['['] = s[']']
s['{'] = s['}']
s['<'] = s['>']

o = {}
o['('] = ')'
o['['] = ']'
o['{'] = '}'
o['<'] = '>'
o[')'] = '('
o[']'] = '['
o['}'] = '{'
o['>'] = '<'

ans = []
for line in sys.stdin:
    a = line.strip()
    print(a)
    stk = []
    for c in a:
        if c in ['(', '[', '{', '<']:
            stk.append(c)
        else:
            if stk[-1] != o[c]:
                break
            else:
                stk.pop()
    else:
        print(stk)
        cur = 0
        for c in stk[::-1]:
            cur = cur*5 + s[c]
        ans.append(cur)

ans=sorted(ans)
print(ans)
print(len(ans))
print(ans[len(ans)//2])
