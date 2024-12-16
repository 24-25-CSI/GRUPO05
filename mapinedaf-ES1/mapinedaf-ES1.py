#Ejercicio 1
mensaje = "texto de prueba del cifrado"
print("Texto de entrada: " + mensaje)
#remplazar los espacios por guiones 
mensaje = mensaje.replace(" ","-")

#Revisar si el mensaje encaja en las 5 filas
#Sino rellenar hasta que sea multiplo de 5  
if (len(mensaje) %5 !=0):
    #print("Rellenar palabra")
    
    while(len(mensaje) %5 !=0 ):
        mensaje = mensaje + "*"
    
    #print(mensaje)
    
#Asegurar al menos 3 columnas (5x3 =15)    
if(len(mensaje) <15):
    while(len(mensaje) <15 ):
        mensaje = mensaje + "*"
    #print(mensaje)    
    
    
matriz = []

#Cargar la matriz con los caracteres del mensaje en texto plano 
index_caracter =0
for i in range(0,5):
    matriz.append([])
    for j in range(0,int(len(mensaje)/5)):
        matriz[i].append([])
        #matriz[i][j] = list(mensaje)[index_caracter]
        #index_caracter = index_caracter +1 
for i in range(0,int(len(mensaje)/5)):
    for j in range (0,5):
        matriz[j][i] = list(mensaje)[index_caracter]
        index_caracter = index_caracter +1 

#Juntar el texto cifrado
mensaje_cifrado = ""   
for fila in matriz:
    print(fila)
    for caracter in fila:
        mensaje_cifrado = mensaje_cifrado + caracter
    
print("Testo de salida: "+mensaje_cifrado)
        