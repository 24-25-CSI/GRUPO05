'''
4. Algoritmo que realice el cifrado de una cadena de caracteres mediante un método de sustitución Monoalfabético de desplazamiento n caracteres a la derecha. Tanto la palabra como el valor de n se ingresan al iniciar el algoritmo. El algoritmo debe mostrar el alfabeto original, el alfabeto
cifrado, la cadena decaracteres ingresada y su resultado.
'''

#Función para obtener los datos ingresados por el usuario
def obtener_datos_por_teclado():
    while True:
        try:
            n = int(input("Ingrese el valor de desplazamiento (n): "))
            mensaje = input("Ingrese el mensaje a cifrar: ")
            return n, mensaje  # Retorna los valores ingresados por el usuario en una tupla
        except ValueError as e:
            print(f"Entrada inválida: {e}. Por favor, intente de nuevo.")
            
# Función para seleccionar o ingresar un alfabeto
def seleccionar_alfabeto():
    print("Seleccione un alfabeto:")
    print("1. Alfabeto en español")
    print("2. Alfabeto en inglés")
    print("3. Alfabeto en francés")
    print("4. Alfabeto en alemán")
    print("5. Ingresar un alfabeto personalizado")
    
    while True:
        try:
            opcion = int(input("Ingrese el número de la opción deseada: "))
            if opcion == 1:
                return 'ABCDEFGHIJKLMNÑOPQRSTUVWXYZ'
            elif opcion == 2:
                return 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
            elif opcion == 3:
                return 'ABCDEFGHIJKLMNOPQRSTUVWXYZÀÂÆÇÉÈÊËÎÏÔŒÙÛÜŸ'
            elif opcion == 4:
                return 'ABCDEFGHIJKLMNOPQRSTUVWXYZÄÖÜß'
            elif opcion == 5:
                alfabeto_personalizado = input("Ingrese el alfabeto personalizado: ").upper()
                if len(set(alfabeto_personalizado)) == len(alfabeto_personalizado):
                    return alfabeto_personalizado
                else:
                    print("El alfabeto personalizado no debe contener caracteres repetidos.")
            else:
                print("Opción no válida. Por favor, intente de nuevo.")
        except ValueError as e:
            print(f"Entrada inválida: {e}. Por favor, intente de nuevo.")        

# Función de cifrado monoalfabético
def cifrado_monoalfabetico(n, cadena, alfabeto='ABCDEFGHIJKLMNÑOPQRSTUVWXYZ'): # Dejamos por defecto el alfabeto en español
    n = n % len(alfabeto)  # Asegurar que el desplazamiento esté dentro del rango del alfabeto
    alfabeto_cifrado = alfabeto[n:] + alfabeto[:n]
    
    cadena_cifrada = ''
    for char in cadena.upper():
        if char in alfabeto:
            index = alfabeto.index(char)
            cadena_cifrada += alfabeto_cifrado[index]
        else:
            cadena_cifrada += char
    
    # Imprimir resultados
    print("RESULTADOS")
    print("Alfabeto original: ", alfabeto)
    print("Alfabeto cifrado:  ", alfabeto_cifrado)
    print("Cadena original:   ", cadena)
    print("Cadena cifrada:    ", cadena_cifrada)

# Seleccionar el alfabeto
alfabeto = seleccionar_alfabeto()

# Solicitar la información
n, cadena = obtener_datos_por_teclado()

# Ejecutar el algoritmo
cifrado_monoalfabetico(n, cadena, alfabeto)