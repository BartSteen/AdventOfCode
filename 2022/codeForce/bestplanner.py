import numpy as np

def maxv(vals):
    m = -1
    for v in vals:
        m = max (v, m)

    return m

print(maxv(np.array([1,2,5,4,7,12341,4])))