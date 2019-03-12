def paraMaiuscula(c):
    if c >= 'a' and c <= 'z':
        return chr(ord('A') + ord(c) - ord('a'))
    else:
        return c
    
def paraMinuscula(c):
    if c >= 'A' and c <= 'Z':
        return chr(ord('a') + ord(c) - ord('A'))
    else:
        return c

# PROGRAMA PRINCIPAL
texto = input("digite um texto: ")  # Suponha que o usuário digitou "PeQuEno TesTE"

textoMaiusculo = ''
textoMinusculo = ''
for l in texto:
    textoMaiusculo += paraMaiuscula(l)
    textoMinusculo += paraMinuscula(l)

print("Em maiusculas: ")
print (textoMaiusculo)

print("Em minusculas: ")