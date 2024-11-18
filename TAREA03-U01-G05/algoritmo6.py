entrada = str( input("Texto de entrada: "))


def coordenadas(tabla, char):
    for num_fila, fila in enumerate(tabla):
        for num_columna, letra in enumerate(fila):
            if letra == char:
                return (num_fila, num_columna)
    return None

tabla = [
    ['*', 'A', 'S', 'D', 'F', 'G'],
    ['Q', 'a', 'b', 'c', 'd', 'e'],
    ['W', 'f', 'g', 'h', 'i', 'j'],
    ['E', 'k', 'l', 'm', 'n', 'o'],
    ['R', 'p', 'q', 'r', 's', 't'],
    ['T', 'u', 'v', 'x', 'y', 'z']
]

chars =list('abcdefghijlkmnopqrstuvxyz')
columnas = ['*', 'A', 'S', 'D', 'F', 'G']
filas = ['*', 'Q', 'W', 'E', 'R', 'T']




entrada = entrada.lower()
entrada_limpia = []
for char in list(entrada):
    if char in chars:
        entrada_limpia.append(char)
    else:
        entrada_limpia.append('*')

entrada_limpia = "".join(entrada_limpia)
print("Texto de entrada: ")
print(entrada)
print("---------------")
print("Texto limpio: ")
print(entrada_limpia)
print("---------------")

print("Tabla de cifrado: ")
for fila in tabla:
    print(fila)
print("---------------")

mensage_cifrado= []
for char in list(entrada_limpia):
    coord = coordenadas(tabla,char)
    columna =columnas[ coord[1] ]
    fila = filas[ coord[0]]
    mensage_cifrado.append(fila)
    mensage_cifrado.append(columna)
    
print("Texto de salida: ")    
print ("".join(mensage_cifrado))
print("--------------")

mensage_descifrado = []
for i in range(0, len(mensage_cifrado), 2):
    if i + 1 >= len(mensage_cifrado):
        break
    char1, char2 = mensage_cifrado[i], mensage_cifrado[i+1]
    #print((char1,char2))
    fila = filas.index(char1)
    columna= columnas.index(char2)
    mensage_descifrado.append(tabla[fila][columna])
mensage_descifrado = "".join(mensage_descifrado)

print("Texto de descifrado: ")    
print(mensage_descifrado)
print("--------------")
    
