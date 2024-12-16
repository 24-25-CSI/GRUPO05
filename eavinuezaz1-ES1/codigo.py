
""" 
Indicaciones:
Realice el cifrado de un mensaje por permutacion de filas,
teniendo como clave 5 filas y la cantidad de columnas que sean necesarias (garantice al menos 3).
Los espacios del mensaje original se sustituyen con el caracter"-". Si en la matriz de cifrado sobran espacios, estos deben llenarse con el caracter"*" 
"""
import random

#Funcion para el cifrado por permutacion de filas
def cifrar_por_permutacion(mensaje, filas=5):

    # 1) Reemplazar los espacios con '-'
    mensaje = mensaje.replace(' ', '-')
    
    # 2) Calculo de cuántas columnas se necesitan
    # Al menos 3 columnas, y el número total de celdas debe ser múltiplo de 5
    columnas = max(3, (len(mensaje) + filas - 1) // filas)  # Número de columnas necesarias
    
    # Rellenar con '*' si el mensaje no llena la matriz
    total_caracteres = filas * columnas
    mensaje = mensaje.ljust(total_caracteres, '*')
    
    # 3) Construir la matriz de cifrado
    matriz = [list(mensaje[i:i+columnas]) for i in range(0, len(mensaje), columnas)]
    
    # Mostrar la matriz antes de la permutación (opcional)
    print("Matriz antes de permutar:")
    for fila in matriz:
        print("".join(fila))
    
    # 4): Permutar las filas de manera aleatoria
    filas_permutadas = list(range(filas))
    random.shuffle(filas_permutadas)
    
    # Crear la matriz permutada
    matriz_permutada = [matriz[i] for i in filas_permutadas]
    
    # Mostrar la matriz permutada (opcional)
    print("\nMatriz después de permutar:")
    for fila in matriz_permutada:
        print("".join(fila))
    
    # 5): Leer la matriz por columnas
    mensaje_cifrado = ''.join(matriz_permutada[fila][col] for col in range(columnas) for fila in range(filas))
    
    return mensaje_cifrado


print("RESULTADOS")

mensaje_original = "eavinuezaz1"
print("Mensaje original: " +mensaje_original)
mensaje_cifrado = cifrar_por_permutacion(mensaje_original)
print("\nMensaje cifrado:", mensaje_cifrado)

