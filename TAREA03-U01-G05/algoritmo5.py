#Cifrado de vigenere
entrada ="universidad central del ecuador"
llave = "abc"


def generar_llave(mensage_plano, llave):
    llave = list(llave)
    if(len(mensage_plano) == len(llave)):
        return llave
    else:
        for i in range(len(mensage_plano) - len(llave)):
            llave.append(llave[i%len(llave)])
    return "".join(llave)

def cifrar(mensage,llave):
    mensage_cifrado = []
    llave = generar_llave(mensage,llave)
    for i in range(len(mensage)):
        letra = mensage[i]
        letra_encriptada = chr(( (ord(letra) + ord(llave[i]))  - 2*ord('a') ) % 26 + ord('a'))
        mensage_cifrado.append(letra_encriptada)
    return "".join(mensage_cifrado)

def descifrar(mensage,llave):
    mensage_decifrado = []
    llave = generar_llave(mensage,llave)
    for i in range(len(mensage)):
        letra=mensage[i]
        letra_descifrada = chr((ord(letra) - ord(llave[i]) + 26) % 26 + ord('a'))
        mensage_decifrado.append(letra_descifrada)
    return "".join(mensage_decifrado)


def preparar_mensage(mensage_plano):
    mensage_preparado = ''.join( c for c in mensage_plano if c.isalpha())
    return mensage_preparado.lower()



print("Texto de entrada")
entrada = str(input())
print("---------------")

print("Llave de cifrado")
llave = str(input())
print("----------------")

print("Entrada preparada")
entrada_preparada = preparar_mensage(entrada)
print(entrada_preparada)
print("---------------")

print("Texto cifrado")
texto_cifrado = cifrar(entrada_preparada,llave)
print(texto_cifrado)
print("---------------")

print("Texto descifrado")
texto_descifrado = descifrar(texto_cifrado,llave)
print(texto_descifrado)
print("---------------")