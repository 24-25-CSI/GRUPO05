
// <https://www.ietf.org/rfc/rfc1321.txt> definicion base

// verificaciones de null
#include <assert.h>

// enteros en bits
#include <stdint.h>

// malloc/free
#include <stdlib.h>

// printf
#include <stdio.h>

// operaciones de numeros flotantes
#include <float.h>

// gestion de archivos
#include <fcntl.h>
#include <unistd.h>

// manejo de char[]
#include <string.h>

// Medicion del tiempo
#include <time.h>

// archivo de cabecera donde se define la struc md5_context
// struct es un tipo de dato definido por el usuario
// similar a un objeto pero no es un objeto
// c no maneja programacion por objetos.
#include "md5.h"

// Operaciones de bit a bit usadas en el Hash MD5
/*
3.4 Step 4. Process Message in 16-Word Blocks

   We first define four auxiliary functions that each take as input
   three 32-bit words and produce as output one 32-bit word.

		  F(X,Y,Z) = XY v not(X) Z
		  G(X,Y,Z) = XZ v Y not(Z)
		  H(X,Y,Z) = X xor Y xor Z
		  I(X,Y,Z) = Y xor (X v not(Z))
*/

#define F(X, Y, Z) (((X) & (Y)) | ((~(X)) & (Z)))
#define G(X, Y, Z) (((X) & (Z)) | (Y & (~(Z))))
#define H(X, Y, Z) ((X) ^ (Y) ^ (Z))
#define I(X, Y, Z) ((Y) ^ ((X) | (~(Z))))

// Rotacion de la cadena de bits hacia la izquierda
// imagina la forma en el que el cifrado cesar rota los caracteres
static uint32_t rotl(uint32_t x, int s) { return (x << s) | (x >> (32 - s)); }

// Un paso de transformacion del algoritmo MD5
#define STEP(OP, a, b, c, d, k, s, i)                \
	do                                               \
	{                                                \
		a = b + rotl(a + OP(b, c, d) + X[k] + i, s); \
	} while (0)

// Combina 4 bytes y los convierte en un int(los char tienen tamaño de 1 byte)
#define TO_I32(x, i) ((x[i]) | (x[i + 1] << 8) | (x[i + 2] << 16) | (x[i + 3] << 24))

// Procesa bloques de 64 bytes como define el algoritmo md5
/*
   This step uses a 64-element table T[1 ... 64] constructed from the
   sine function. Let T[i] denote the i-th element of the table, which
   is equal to the integer part of 4294967296 times abs(sin(i)), where i
   is in radians. The elements of the table are given in the appendix.*/

static void md5_block(md5_context *ctx, const uint8_t m[64])
{
	assert(ctx != NULL);

	uint32_t X[16] = {
		TO_I32(m, 0), TO_I32(m, 4), TO_I32(m, 8), TO_I32(m, 12),
		TO_I32(m, 16), TO_I32(m, 20), TO_I32(m, 24), TO_I32(m, 28),
		TO_I32(m, 32), TO_I32(m, 36), TO_I32(m, 40), TO_I32(m, 44),
		TO_I32(m, 48), TO_I32(m, 52), TO_I32(m, 56), TO_I32(m, 60)};

	// Tomamos los valores acumulados en el contexto
	uint32_t a = ctx->a;
	uint32_t b = ctx->b;
	uint32_t c = ctx->c;
	uint32_t d = ctx->d;

	// Valores "magicos" definidos por 4294967296 times abs(sin(i))
	// tomados de la definicon de md5 "The elements of the table are given in the appendix"
	// Ronda uno usa la operacion F
	STEP(F, a, b, c, d, 0, 7, 0xd76aa478);
	STEP(F, d, a, b, c, 1, 12, 0xe8c7b756);
	STEP(F, c, d, a, b, 2, 17, 0x242070db);
	STEP(F, b, c, d, a, 3, 22, 0xc1bdceee);
	STEP(F, a, b, c, d, 4, 7, 0xf57c0faf);
	STEP(F, d, a, b, c, 5, 12, 0x4787c62a);
	STEP(F, c, d, a, b, 6, 17, 0xa8304613);
	STEP(F, b, c, d, a, 7, 22, 0xfd469501);
	STEP(F, a, b, c, d, 8, 7, 0x698098d8);
	STEP(F, d, a, b, c, 9, 12, 0x8b44f7af);
	STEP(F, c, d, a, b, 10, 17, 0xffff5bb1);
	STEP(F, b, c, d, a, 11, 22, 0x895cd7be);
	STEP(F, a, b, c, d, 12, 7, 0x6b901122);
	STEP(F, d, a, b, c, 13, 12, 0xfd987193);
	STEP(F, c, d, a, b, 14, 17, 0xa679438e);
	STEP(F, b, c, d, a, 15, 22, 0x49b40821);

	// Ronda dos usa la operacion G
	STEP(G, a, b, c, d, 1, 5, 0xf61e2562);
	STEP(G, d, a, b, c, 6, 9, 0xc040b340);
	STEP(G, c, d, a, b, 11, 14, 0x265e5a51);
	STEP(G, b, c, d, a, 0, 20, 0xe9b6c7aa);
	STEP(G, a, b, c, d, 5, 5, 0xd62f105d);
	STEP(G, d, a, b, c, 10, 9, 0x02441453);
	STEP(G, c, d, a, b, 15, 14, 0xd8a1e681);
	STEP(G, b, c, d, a, 4, 20, 0xe7d3fbc8);
	STEP(G, a, b, c, d, 9, 5, 0x21e1cde6);
	STEP(G, d, a, b, c, 14, 9, 0xc33707d6);
	STEP(G, c, d, a, b, 3, 14, 0xf4d50d87);
	STEP(G, b, c, d, a, 8, 20, 0x455a14ed);
	STEP(G, a, b, c, d, 13, 5, 0xa9e3e905);
	STEP(G, d, a, b, c, 2, 9, 0xfcefa3f8);
	STEP(G, c, d, a, b, 7, 14, 0x676f02d9);
	STEP(G, b, c, d, a, 12, 20, 0x8d2a4c8a);

	// Ronda 3 usa la operacion H
	STEP(H, a, b, c, d, 5, 4, 0xfffa3942);
	STEP(H, d, a, b, c, 8, 11, 0x8771f681);
	STEP(H, c, d, a, b, 11, 16, 0x6d9d6122);
	STEP(H, b, c, d, a, 14, 23, 0xfde5380c);
	STEP(H, a, b, c, d, 1, 4, 0xa4beea44);
	STEP(H, d, a, b, c, 4, 11, 0x4bdecfa9);
	STEP(H, c, d, a, b, 7, 16, 0xf6bb4b60);
	STEP(H, b, c, d, a, 10, 23, 0xbebfbc70);
	STEP(H, a, b, c, d, 13, 4, 0x289b7ec6);
	STEP(H, d, a, b, c, 0, 11, 0xeaa127fa);
	STEP(H, c, d, a, b, 3, 16, 0xd4ef3085);
	STEP(H, b, c, d, a, 6, 23, 0x04881d05);
	STEP(H, a, b, c, d, 9, 4, 0xd9d4d039);
	STEP(H, d, a, b, c, 12, 11, 0xe6db99e5);
	STEP(H, c, d, a, b, 15, 16, 0x1fa27cf8);
	STEP(H, b, c, d, a, 2, 23, 0xc4ac5665);

	// Ronda 4 Usa la operacion I
	STEP(I, a, b, c, d, 0, 6, 0xf4292244);
	STEP(I, d, a, b, c, 7, 10, 0x432aff97);
	STEP(I, c, d, a, b, 14, 15, 0xab9423a7);
	STEP(I, b, c, d, a, 5, 21, 0xfc93a039);
	STEP(I, a, b, c, d, 12, 6, 0x655b59c3);
	STEP(I, d, a, b, c, 3, 10, 0x8f0ccc92);
	STEP(I, c, d, a, b, 10, 15, 0xffeff47d);
	STEP(I, b, c, d, a, 1, 21, 0x85845dd1);
	STEP(I, a, b, c, d, 8, 6, 0x6fa87e4f);
	STEP(I, d, a, b, c, 15, 10, 0xfe2ce6e0);
	STEP(I, c, d, a, b, 6, 15, 0xa3014314);
	STEP(I, b, c, d, a, 13, 21, 0x4e0811a1);
	STEP(I, a, b, c, d, 4, 6, 0xf7537e82);
	STEP(I, d, a, b, c, 11, 10, 0xbd3af235);
	STEP(I, c, d, a, b, 2, 15, 0x2ad7d2bb);
	STEP(I, b, c, d, a, 9, 21, 0xeb86d391);

	// sumamos los nuevos valores a los acumuladores
	ctx->a += a;
	ctx->b += b;
	ctx->c += c;
	ctx->d += d;

	// limpieza de memoria
	memset(X, 0, sizeof(X));
}

// Funcion para inicializar el struct md5 context
// Similar a un constructor (o un bloque de inicializacion)
// pero no es un contructor
// c no maneja objetos
void md5_init(md5_context *ctx)
{
	assert(ctx != NULL);
	memset(ctx, 0, sizeof(md5_context));
	// Iniciamos los acumuladores con los valores de RFC 1321, Section 3.3:
	/*    word A: 01 23 45 67
		  word B: 89 ab cd ef
		  word C: fe dc ba 98
		  word D: 76 54 32 10*/
	//formato hex  
	ctx->a = 0x67452301;
	ctx->b = 0xEFCDAB89;
	ctx->c = 0x98BADCFE;
	ctx->d = 0x10325476;
}

//Separa enteros de 32 bits en 4 bytes
#define TO_U8(x, o, i)                 \
	do                                 \
	{                                  \
		o[i] = (x) & 0xFF;             \
		o[i + 1] = ((x) >> 8) & 0xFF;  \
		o[i + 2] = ((x) >> 16) & 0xFF; \
		o[i + 3] = ((x) >> 24) & 0xFF; \
	} while (0)

//Procesa la entrada loques de 64 bytes
void md5_digest(md5_context *ctx, void *buffer, size_t size)
{	
	//numero de bytes ya procesados dados por un buffer(array)
	uint8_t *bytes = (uint8_t *)buffer;
	//tamaño total de bits
	uint64_t message_bits = size * 8;
	//tamaño restante de procesar
	size_t rem_size = size;
	//Rompe el texto en bytes 
	while (rem_size > 64)
	{	
		//procesa un bloque de bytes 
		md5_block(ctx, bytes);
		//aumenta el conteo de bytes procesados
		bytes += 64;
		//reduce el conteo de bytes restantes
		rem_size -= 64;
	}
	uint8_t scratch[64];
	memset(scratch, 0, 64);
	memcpy(scratch, bytes, rem_size);
	//Maneja el resto de bytes 
	if (rem_size == 64)
	{
		md5_block(ctx, scratch);
		memset(scratch, 0, 64);
		scratch[0] = 0x80;
	}
	else
	{	
		//si el resto es menor que 64 bytes hace padding con 0 (0x80 en hex)
		scratch[rem_size] = 0x80;
		if (64 - (rem_size + 1) < 8)
		{
			md5_block(ctx, scratch);
			memset(scratch, 0, 64);
		}
	}


	TO_U8(message_bits, scratch, 56);
	TO_U8(message_bits >> 32, scratch, 60);
	md5_block(ctx, scratch);
	memset(scratch, 0x00, 64);
}

//salida de el hash
void md5_output(md5_context *ctx, uint8_t out[16])
{
	TO_U8(ctx->a, out, 0);
	TO_U8(ctx->b, out, 4);
	TO_U8(ctx->c, out, 8);
	TO_U8(ctx->d, out, 12);
}

//hexadecimal a texto 
int hex_digit_to_int(char c)
{
	switch (c)
	{
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		return c - '0';
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
		return c + 10 - 'A';
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
		return c + 10 - 'a';
	default:
		assert(0 && "invalid hex character");
	}
	return -1;
}

//convierte de hezadecimales a bytes 
void hex_string_to_bytes(char *hex, uint8_t bytes[16])
{
	assert(strlen(hex) == 32);
	int j = 0;
	for (int i = 0; i < 32; i += 2)
	{
		bytes[j] = 16 * hex_digit_to_int(hex[i]) + hex_digit_to_int(hex[i + 1]);
		j++;
	}
}

//imprimir los bytes 
void print_bytes(uint8_t bytes[16])
{
	for (int i = 0; i < 16; i++)
	{
		printf("%02X", bytes[i]);
	}
	printf("\n");
}

//Metodo para crear un array grande
//si haces char vect[1000000000] da error de memoria
//hay que usar malloc para conseguir memoria 
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

//c no tiene garbage collector como java
//si no liberas la memoria da una fuga de ram
//cuando lo probe me ocupo 11 gb despues de correrlo algunas veces
void free_large_vector(char *vec)
{
	if (vec)
	{
		free(vec);
	}
}

//Metodo para contar los caracteres de un achivo de texto
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

//Ejecucion del hash. 
int main()
{	
	//lectura del archivo
	clock_t inicioLectura, finLectura;
	FILE *file_ptr;
	inicioLectura = clock();
	char filePath[] = "../../texto_plano/10000000.txt";
	//contar los char en el archivo
	long nunm_caracteres = contar_caracteres(filePath);
	printf("Numero de caracteres: %d\n", nunm_caracteres);
	char *large_vec = create_large_vector(nunm_caracteres + 1);
	file_ptr = fopen(filePath, "r");
	if (file_ptr == NULL)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	fread(large_vec, 1, nunm_caracteres + 1, file_ptr);

	finLectura = clock();
	double tiempoLectura = (double)(finLectura - inicioLectura);

	//instrucciones por segundo del procesador para calcular el tiempo. 
	// printf("clocks per sec: %d\n", CLOCKS_PER_SEC);

	//impresion de los primeros 40 caracteres del archivo
	printf("Cadena de entrada: ");
	for (int i = 0; i < 40; i++)
	{
		if (large_vec[i] == '\0')
		{
			printf("Null character encountered\n");
			break;
		}
		printf("%c", large_vec[i]);
	}

	printf("\nT1: Tiempo de lectura del archivo: %f", tiempoLectura / CLOCKS_PER_SEC);

	printf("\n");
	char *input = large_vec;

	// printf(large_vec);
	clock_t inicioEncriptar, finEncriptar;
	inicioEncriptar = clock();
	//declara el acumulador
	md5_context ctx;
	//inicia el acumulador
	md5_init(&ctx);
	//calcula el hash
	md5_digest(&ctx, input, strlen(input));
	//declarando el array de salida
	uint8_t md5_actual[16] = {0};
	//guarda el hash en el array de salida
	md5_output(&ctx, md5_actual);
	finEncriptar = clock();
	double tiempoEncriptar = (double)(finEncriptar - inicioEncriptar);
	printf("T3: Tiempo de Encriptar del archivo: %f\n", tiempoEncriptar / CLOCKS_PER_SEC);
	printf("Hash de salida: ");
	//Imprime los bytes del vector de salida
	print_bytes(md5_actual);

	//libera la memoria del array de lectura. 
	free_large_vector(large_vec);
}