m = [ 0 for _ in range(3000) ]
op = []

def cut_log(p, n):
    global m
    global op
    if (p != op):
        m = [ 0 for _ in range(3000) ]
        op = p
    if (n == 0):
        return 0
    if (m[n] != 0):
        return m[n]
    q = -1
    for i in range(1, n + 1):
        q = max(q, p[i] + cut_log(p, n - i))
    m[n] = q
    return q
#

