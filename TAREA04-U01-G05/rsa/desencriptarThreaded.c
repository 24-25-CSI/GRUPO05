//archivo de desencripcion rsa con multiples hilos

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define MAX_CIPHERTEXT 10000000000 
#define NUM_THREADS 12             // Numero de hilos para desencriptar

unsigned long long int *ciphertext;
int num_ciphertext = 0;
int p, q, d, n;
int dP, dQ, qInv;

// Funcion para calcular la potencia modular de un numero
//  c ≡ b^e ( mod m )
unsigned long long int modpow(unsigned long long int base, int power, int mod)
{
    int i;
    unsigned long long int result = 1;
    for (i = 0; i < power; i++)
    {
        result = (result * base) % mod;
    }
    return result;
}
// Funcion para encontrar el inverso modular de un numero
//  n^-1 ≡ m(mod p)
int inverse(int a, int mod)
{
    int aprev, iprev, i = 1, atemp, itemp;

    aprev = mod, iprev = mod;
    while (a != 1)
    {
        atemp = a;
        itemp = i;
        a = aprev - aprev / atemp * a;
        i = iprev - aprev / atemp * i;
        aprev = atemp;
        iprev = itemp;
        while (i < 0)
            i += mod;
    }
    return i;
}

// Metodo para desencriptar el texto por partes (multihilo)
void *decrypt_chunk(void *arg)
{
    int thread_id = *(int *)arg;
    int chunk_size = num_ciphertext / NUM_THREADS;
    int start = thread_id * chunk_size;
    int end = (thread_id == NUM_THREADS - 1) ? num_ciphertext : start + chunk_size;

    FILE *output;
    char filename[20];
    sprintf(filename, "decrypted_%d.txt", thread_id); // Create a file for each thread
    output = fopen(filename, "w");
    if (!output)
    {
        fprintf(stderr, "Error: error de hilo %d.\n", thread_id);
        pthread_exit(NULL);
    }

    for (int i = start; i < end; i++)
    {
        unsigned long long int c = ciphertext[i];
        unsigned long long int m1 = modpow(c, dP, p);
        unsigned long long int m2 = modpow(c, dQ, q);
        int m1m2 = m1 - m2;
        if (m1m2 < 0)
            m1m2 += p;
        int h = (qInv * m1m2) % p;
        unsigned long long int m = m2 + h * q;

        fprintf(output, "%c", (char)m); // Escribir al archivo
    }

    fclose(output);
    return NULL;
}

int main()
{
    clock_t start_time, end_time;
    start_time = clock(); // Inicio del metodo

    FILE *inp;

    // Cargar llave privada
    inp = fopen("private.txt", "r");
    fscanf(inp, "%d %d", &n, &d);
    fclose(inp);

    // cargar p y q
    inp = fopen("pq.txt", "r");
    fscanf(inp, "%d %d", &p, &q);
    fclose(inp);

    // Leer el archivo cifrado
    printf("Leyendo texto cifrado...\n");
    inp = fopen("ciphertext.txt", "r");
    int capacity = 100; // Capacidad inicial para el vector
    // asignacion inicial de memoria.
    ciphertext = malloc(capacity * sizeof(unsigned long long int));

    // Manejo de error de lectura
    if (!ciphertext)
    {
        fprintf(stderr, "Error: maloc fallo.\n");
        exit(EXIT_FAILURE);
    }

    // Manejo dimamico de memoria
    while (fscanf(inp, "%llu", &ciphertext[num_ciphertext]) != EOF)
    {
        num_ciphertext++;
        // Si el numero de caracteres es mayor al tamaño del array
        // duplicamos y volvemos a asignar memoria.
        if (num_ciphertext >= capacity)
        {
            capacity *= 2;
            ciphertext = realloc(ciphertext, capacity * sizeof(unsigned long long int));
            if (!ciphertext)
            {
                fprintf(stderr, "Error: maloc fallo.\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    fclose(inp);

    // Variables RSA
    dP = d % (p - 1);
    dQ = d % (q - 1);
    qInv = inverse(q, p);

    // Desesncriptado por hilos (POSIX threads no sive en windows :v usa el wsl)
    printf("Desencriptando...\n");
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++)
    {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, decrypt_chunk, &thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("Desencriptado completo.\n");

    end_time = clock();
    // Medicion de tiempo del metodo, se divide el clock time por el
    // numero de clocks por segundo del procesador y por el numero
    // de hilos porque cada hilo tiene su propio clock time
    double elapsed_time = (((double)(end_time - start_time)) / CLOCKS_PER_SEC) / NUM_THREADS;
    printf("Tiempo de desencripcion: %f seconds\n", elapsed_time);

    printf("Combinando archivos...\n");
    FILE *final_output = fopen("decrypted_combined.txt", "w");
    if (!final_output)
    {
        fprintf(stderr, "Error: no se pudo crear el archivo combinado.\n");
        return 1;
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        char filename[20];
        sprintf(filename, "decrypted_%d.txt", i);

        FILE *thread_output = fopen(filename, "r");
        if (!thread_output)
        {
            fprintf(stderr, "Error: no se pudo abrir el archivo %s.\n", filename);
            fclose(final_output);
            return 1;
        }

        int ch;
        while ((ch = fgetc(thread_output)) != EOF)
        {
            fputc(ch, final_output);
        }
        fclose(thread_output);

        remove(filename);
    }

    free(ciphertext);
    return 0;
}
