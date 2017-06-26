def one_two_three():
    a = one_two()
    b = one_two()
    if a == 1 and b == 1: return 1
    if a == 1 and b == 2: return 2
    if a == 2 and b == 1: return 3
    if a == 2 and b == 2: return one_two_three()
#

