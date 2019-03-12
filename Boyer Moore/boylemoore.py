def BoyleMoore1( a, b):
    m, n = len(a), len(b)
    ult = [-1] * 256
    for k in range(m): ult[ord(a[k])] = k
    k = m - 1
    while k < n:
        j, i = k, m - 1
        while i >= 0:
            if a[i] != b[j]: break
            i, j = i - 1, j - 1
            if i < 0: conta += 1
            if k + 1 > n: break
            k += m - ult[ord(b[k+1])]
    return conta
    
a = ["abba"]
b = ["abbcbbabbabbbabbbabba"]
print(BoyleMoore1(a, b))
