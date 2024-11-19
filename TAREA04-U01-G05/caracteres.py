def contar_caracteres_archivo(nombre_archivo):
    try:
        # Abrir el archivo en modo lectura
        with open(nombre_archivo, 'r') as archivo:
            # Leer todo el contenido del archivo
            contenido = archivo.read()
            # Retornar el número de caracteres
            return len(contenido)
    except FileNotFoundError:
        print(f"Error: El archivo '{nombre_archivo}' no existe.")
        return None
    except PermissionError:
        print(f"Error: No tienes permiso para leer el archivo '{nombre_archivo}'.")
        return None
    except Exception as e:
        print(f"Ocurrió un error al leer el archivo: {str(e)}")
        return None

# Ejemplo de uso
archivo = "./src/rsa/ciphertext.txt"
caracteres = contar_caracteres_archivo(archivo)

if caracteres is not None:
    print(f"El archivo '{archivo}' contiene {caracteres} caracteres.")
