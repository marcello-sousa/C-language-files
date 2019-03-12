def Proxima(a, N, M):
    t = N - 1
    while t >= 0:
        a[t] = (a[t] + 1) % M
        if a[t] == 0: t -= 1
        else: return True
    return False

def Imprime_Sequencias(N, M):
    seq = [0] * N
    tem_proxima = True
    cont = 0
    while tem_proxima:
        print("\n%2d - " %cont, end = '') 
        for k in range(N): 
            print("%3d" %seq[k], end = '')
        cont += 1
        tem_proxima = Proxima(seq, N, M)

Imprime_Sequencias(2, 3)