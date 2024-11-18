"""# Ejercicio 2
Algoritmo que realice el cifrado de un mensaje por permutación de filas teniendo como clave N filas. Tanto N como el texto del mensaje se ingresan al iniciar el algoritmo. El algoritmo debe controlar que el numero de caracteres del mensaje (sin espacios) sea menor o igual a NxN. Imprima la matriz de cifrado, el mensaje original y el mensaje cifrado. Si en la matriz de cifrado sobran espacios para almancenar los caracteres del mensaje original estos deben llenarse con un asterisco "*"
"""

def cifrado_permutacion_filas(mensaje, N):
    # Eliminar los espacios del mensaje
    mensaje = mensaje.replace(" ", "")

    # Verificar que el mensaje no exceda el tamaño permitido
    if len(mensaje) > N * N:
        print("El mensaje es demasiado largo para una matriz de tamaño", N, "x", N)
        return

    # Llenar el mensaje con asteriscos si es necesario
    mensaje_ajustado = mensaje.ljust(N * N, '*')

    # Crear la matriz de cifrado de tamaño N x N
    matriz_cifrado = [list(mensaje_ajustado[i * N:(i + 1) * N]) for i in range(N)]

    # Mostrar la matriz de cifrado
    print("Matriz de cifrado:")
    for fila in matriz_cifrado:
        print(" ".join(fila))

    # Leer el mensaje cifrado por columnas
    mensaje_cifrado = ""
    for columna in range(N):
        for fila in range(N):
            mensaje_cifrado += matriz_cifrado[fila][columna]

    # Mostrar el mensaje original y el mensaje cifrado
    print("\nMensaje original (sin espacios):", mensaje)
    print("Mensaje cifrado:", mensaje_cifrado)

mensaje = input("Ingrese el mensaje a cifrar: ")
N = int(input("Ingrese el número de filas (N): "))

cifrado_permutacion_filas(mensaje, N)