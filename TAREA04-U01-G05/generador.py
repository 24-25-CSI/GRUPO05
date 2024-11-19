#Script para generar palabras de forma aleatoria dado un numero. 
#variables
numero_palabras = 1000000
ruta = './texto_plano/'+str(numero_palabras)+'.txt'

#LibreriasS
import nltk
import random
from pathlib import Path

#Creacion de la carpeta
Path("./texto_plano").mkdir(parents=True, exist_ok=True)

#Descargar diccionario
nltk.download('words')
nltk.download('cess_esp')

#Cargar palabras
palabras= set(palabra.lower() for palabra in nltk.corpus.words.words())
#palabras= set(palabra.lower() for palabra in nltk.corpus.cess_esp.words())
palabras = [palabra for palabra in palabras if palabra.isalpha()]
palabras_aleatorias = random.choices(list(palabras),k = numero_palabras)
with open(ruta,'w' ) as archivo:
    for palabra in palabras_aleatorias:
        archivo.write(palabra +' ')
        
       