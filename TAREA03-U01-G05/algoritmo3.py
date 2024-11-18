'''
3. Algoritmo que realice el cifrado de un mensaje por permutación de columnas, teniendo como clave n columnas. Tanto n como el texto del mensaje se ingresan al iniciar el algoritmo. El algoritmo debe controlar que el número de caracteres del mensaje (sin espacios), sea menor o igual que n x n. Imprima la matriz de cifrado, el mensaje original y el mensaje cifrado. Si en la matriz de cifrado sobran espacios para almacenar los caracteres del mensaje original, estos deben llenarse con "*".
'''

#Función para obtener los datos ingresados por el usuario
def obtener_datos_por_teclado():
    while True:
        try:
            n = int(input("Ingrese el número de columnas (n): "))
            if n <= 0:
                raise ValueError("El número de columnas debe ser un entero positivo.")
            mensaje = input("Ingrese el mensaje a cifrar: ").replace(" ", "") #Elimina los espacios en blanco
            if len(mensaje) > n * n:
                raise ValueError(f"El mensaje debe tener como máximo {n * n} caracteres.")
            return n, mensaje  #Retorna los valores ingresados por el usuario en una tupla
        except ValueError as e:
            print(f"Entrada inválida: {e}. Por favor, intente de nuevo.")
     
#Función de cifrado por permutación de columnas
def cifrado_permutacion_columnas(n, mensaje):
    # Inicializar la matriz de n x n con '*'
    matriz = []
    for _ in range(n):
        fila = []
        for _ in range(n):
            fila.append('*')
        matriz.append(fila)

    # Llenar la matriz con los caracteres del mensaje
    index = 0
    for i in range(n):
        for j in range(n):
            if index < len(mensaje):
                matriz[i][j] = mensaje[index]
                index += 1
    
    # Imprimir la matriz de cifrado
    print("Matriz de cifrado:")
    for fila in matriz:
        print(" ".join(fila))
    
    # Leer la matriz por columnas para obtener el mensaje cifrado
    mensaje_cifrado = ""
    for j in range(n):
        for i in range(n):
            mensaje_cifrado += matriz[i][j]
    
    # Imprimir el mensaje original y el mensaje cifrado
    print("Mensaje original:", mensaje)
    print("Mensaje cifrado:", mensaje_cifrado)
    
# Solicitar la información
n, mensaje = obtener_datos_por_teclado()

# Ejecutar el algoritmo
cifrado_permutacion_columnas(n, mensaje)    