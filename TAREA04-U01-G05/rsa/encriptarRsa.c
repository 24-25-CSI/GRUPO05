#include "stdio.h"
#include "stdlib.h"
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

unsigned long long int modpow(int base, int power, int mod)
{
        int i;
        unsigned long long int result = 1;
        for (i = 0; i < power; i++)
        {
                result = (result * base) % mod;
        }
        return result;
}

int contar_caracteres(char *path)
{

        int fd = open(path, O_RDONLY);

        char buffer[1204];
        size_t bytes_read;
        long caracteres = 0;

        while ((bytes_read = read(fd, buffer, 1024)) > 0)
        {
                caracteres += bytes_read;
        }

        if (bytes_read == -1)
        {
                perror("Error al leer el archivo");
                close(fd);
                return 1;
        }
        close(fd);

        return caracteres;
}

char *create_large_vector(size_t size)
{
        char *vec = (char *)malloc(size * sizeof(char));
        if (!vec)
        {
                fprintf(stderr, "Error al asignar memoria\n");
                exit(EXIT_FAILURE);
        }
        return vec;
}

void free_large_vector(char *vec)
{
        if (vec)
        {
                free(vec);
        }
}

int main(int argc, char *argv[])
{       

        //Variables del algoritmo rsa
        //esquema de cifrado
        //c = m^e mod {n}
        int m, n, e;
        unsigned long long int c;
        int i;

        //Archivo con la llave publica
        FILE *inp = fopen("public.txt", "r");
        fscanf(inp, "%d %d", &n, &e);
        fclose(inp);

        //Archivo de salida donde se guarda el texto cifrado
        FILE *outp = fopen("ciphertext.txt", "w");

        //Inico de la lectura del archivp
        clock_t inicioLectura, finLectura;
        inicioLectura = clock();
        //Ruta del archivo de texto
        FILE *file_ptr;
        char filePath[] = "../../texto_plano/1000000.txt";

        //Numero de caracteres de entrada 
        long nunm_caracteres = contar_caracteres(filePath);
        printf("Numero de caracteres: %d\n", nunm_caracteres);

        //alocacion de memoria para el vector donde se guarda la informacion. 
        char *large_vec = create_large_vector(nunm_caracteres + 1);
        file_ptr = fopen(filePath, "r");
        if (file_ptr == NULL)
        {
                perror("Error opening file");
                exit(EXIT_FAILURE);
        }
        //Carga de datos en el vector de texto. 
        fread(large_vec, 1, nunm_caracteres + 1, file_ptr);
        //Fin del reloj de lectura. 
        finLectura = clock();

        //Copia de dos datos de lectura 
        char *texto = large_vec;
        double tiempoLectura = (double)(finLectura - inicioLectura);
        printf("Cadena de entrada: ");

        //Impresion de los primeros caracteres del texto de entrada
        for (int i = 0; i < 40; i++)
        {
                if (large_vec[i] == '\0')
                {
                        printf("Null character encountered\n");
                        break;
                }
                printf("%c", large_vec[i]); 
        }

        //Resultado del tiempo de carga de los archivos. 
        printf("\nT1: Tiempo de lectura del archivo: %f \n", tiempoLectura / CLOCKS_PER_SEC);

        //Inicio del proceso de encriptacion. 
        clock_t inicioEncriptar, finEncriptar;
        inicioEncriptar = clock();
        printf("Texto cifrado c = ");
        for (i = 0; texto[i] != '\0'; i++)
        {
                c = modpow(texto[i], e, n);
                if (i < 20)
                {
                        printf("%llu ", c);
                };
                fprintf(outp, "%llu\n", c);
        }

        printf("\n");
        fclose(outp);
        finEncriptar = clock();
        double tiempoEncriptar = (double)(finEncriptar - inicioEncriptar);
        printf("T3: Tiempo de Encriptar del archivo: %f\n", tiempoEncriptar / CLOCKS_PER_SEC);

        long numCaracteresSalida = contar_caracteres("ciphertext.txt");
        printf("numero de caracteres de salida: %d\n", numCaracteresSalida);
        free_large_vector(large_vec);
        return 0;
}