def cifrado_permutacion_filas(mensaje):
    N = 5  # Fijar el número de filas en 5
    # Reemplazar los espacios del mensaje con "-"
    mensaje = mensaje.replace(" ", "-")

    # Calcular el número de columnas necesarias (al menos 3)
    columnas = max(3, (len(mensaje) + N - 1) // N)

    # Llenar el mensaje con asteriscos si es necesario
    mensaje_ajustado = mensaje.ljust(N * columnas, '*')

    # Crear la matriz de cifrado de tamaño N x columnas
    matriz_cifrado = [list(mensaje_ajustado[i * columnas:(i + 1) * columnas]) for i in range(N)]

    # Mostrar la matriz de cifrado
    print("Matriz de cifrado:")
    for fila in matriz_cifrado:
        print(" ".join(fila))

    # Leer el mensaje cifrado por columnas
    mensaje_cifrado = ""
    for columna in range(columnas):
        for fila in range(N):
            mensaje_cifrado += matriz_cifrado[fila][columna]

    # Mostrar el mensaje original y el mensaje cifrado
    print("\nMensaje original (sin espacios):", mensaje)
    print("Mensaje cifrado:", mensaje_cifrado)

mensaje = input("Ingrese el mensaje a cifrar: ")

cifrado_permutacion_filas(mensaje)