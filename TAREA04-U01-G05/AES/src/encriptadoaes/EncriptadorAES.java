package encriptadoaes;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.io.UnsupportedEncodingException;
import java.security.InvalidKeyException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.text.DecimalFormat;
import java.util.Arrays;
import java.util.Base64;
import javax.crypto.BadPaddingException;
import javax.crypto.Cipher;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.NoSuchPaddingException;
import javax.crypto.spec.SecretKeySpec;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.time.LocalTime;
import java.time.temporal.ChronoUnit;

public class EncriptadorAES {

    // Método para crear una clave secreta a partir de una cadena de texto
    private SecretKeySpec crearClave(String clave) throws UnsupportedEncodingException, NoSuchAlgorithmException {
        // Convierte la cadena de texto 'clave' a un arreglo de bytes usando la
        // codificación UTF-8
        byte[] claveEncriptacion = clave.getBytes("UTF-8");

        // Crea una instancia de MessageDigest que utiliza el algoritmo SHA-1
        MessageDigest sha = MessageDigest.getInstance("SHA-1");

        // Calcula el hash SHA-1 del arreglo de bytes de la clave
        claveEncriptacion = sha.digest(claveEncriptacion);

        // Trunca o expande el arreglo de bytes resultante del hash SHA-1 a 16 bytes
        // (128 bits)
        claveEncriptacion = Arrays.copyOf(claveEncriptacion, 16);

        // Crea una instancia de SecretKeySpec usando el arreglo de bytes de 16 bytes
        // como la clave y especifica que se utilizará el algoritmo AES
        return new SecretKeySpec(claveEncriptacion, "AES");
    }

    // Método para encriptar una cadena de texto
    public String encriptar(String datos, String claveSecreta)
            throws UnsupportedEncodingException, NoSuchAlgorithmException, InvalidKeyException, NoSuchPaddingException,
            IllegalBlockSizeException, BadPaddingException {
        // Genera una clave secreta a partir de la cadena de texto 'claveSecreta'
        SecretKeySpec secretKey = this.crearClave(claveSecreta);

        // Crea una instancia de Cipher que utiliza el algoritmo AES en modo ECB con
        // relleno PKCS5Padding
        Cipher cipher = Cipher.getInstance("AES/ECB/PKCS5Padding");

        // Inicializa el Cipher en modo de encriptación con la clave secreta generada
        cipher.init(Cipher.ENCRYPT_MODE, secretKey);

        // Convierte la cadena de texto 'datos' a un arreglo de bytes usando la
        // codificación UTF-8
        byte[] datosEncriptar = datos.getBytes("UTF-8");

        // Encripta los datos y obtiene el arreglo de bytes encriptados
        byte[] bytesEncriptados = cipher.doFinal(datosEncriptar);

        // Convierte el arreglo de bytes encriptados a una cadena en Base64 y la retorna
        return Base64.getEncoder().encodeToString(bytesEncriptados);
    }

    // Método para desencriptar una cadena de texto encriptada
    public String desencriptar(String datosEncriptados, String claveSecreta)
            throws UnsupportedEncodingException, NoSuchAlgorithmException, InvalidKeyException, NoSuchPaddingException,
            IllegalBlockSizeException, BadPaddingException {
        // Genera una clave secreta a partir de la cadena de texto 'claveSecreta'
        SecretKeySpec secretKey = this.crearClave(claveSecreta);

        // Crea una instancia de Cipher que utiliza el algoritmo AES en modo ECB con
        // relleno PKCS5Padding
        Cipher cipher = Cipher.getInstance("AES/ECB/PKCS5Padding");

        // Inicializa el Cipher en modo de desencriptación con la clave secreta generada
        cipher.init(Cipher.DECRYPT_MODE, secretKey);

        // Decodifica la cadena de texto 'datosEncriptados' desde Base64 a un arreglo de
        // bytes
        byte[] bytesEncriptados = Base64.getDecoder().decode(datosEncriptados);

        // Desencripta los datos y obtiene el arreglo de bytes desencriptados
        byte[] datosDesencriptados = cipher.doFinal(bytesEncriptados);

        // Convierte el arreglo de bytes desencriptados a una cadena de texto y la
        // retorna
        return new String(datosDesencriptados);
    }

    public static void main(String[] args) {
        LocalTime startTime, endTime;
        double tE1, tE2, tE3, tE4, tTotal;

        try {
            // Crear un objeto DecimalFormat para formatear el tiempo con 2 decimales
            DecimalFormat df = new DecimalFormat("#.##");

            // T-E1: Tiempo de ejecución para la etapa de lectura del archivo
            startTime = LocalTime.now(); // Captura el tiempo inicial
            String filePath = "texto_plano/10.txt"; // Ruta del archivo a encriptar

            // Encuentra la posición de "/"
            int startIndex = filePath.lastIndexOf("/") + 1; // Posición después de "/"

            // Encuentra la posición de ".txt"
            int endIndex = filePath.indexOf(".txt");

            // Extrae el número entre las posiciones encontradas
            String numeroPalabras = filePath.substring(startIndex, endIndex);

            String datosOriginales = new String(Files.readAllBytes(Paths.get(filePath)), "UTF-8");
            endTime = LocalTime.now(); // Captura el tiempo final
            tE1 = ChronoUnit.NANOS.between(startTime, endTime) / 1_000_000_000.0; // Convertir de ns a segundos (con
                                                                                  // decimales)

            // T-E2: Tiempo de ejecución para la generación de claves
            startTime = LocalTime.now();
            final String claveOriginal = "secreto!"; // Clave proporcionada
            EncriptadorAES encriptador = new EncriptadorAES();
            endTime = LocalTime.now();
            tE2 = ChronoUnit.NANOS.between(startTime, endTime) / 1_000_000_000.0;

            // T-E3: Tiempo de ejecución para cifrar el texto
            startTime = LocalTime.now();
            String encriptado = encriptador.encriptar(datosOriginales, claveOriginal);
            endTime = LocalTime.now();
            tE3 = ChronoUnit.NANOS.between(startTime, endTime) / 1_000_000_000.0;

            // T-E4: Tiempo de ejecución para descifrar el texto
            startTime = LocalTime.now();
            String desencriptado = encriptador.desencriptar(encriptado, claveOriginal);
            endTime = LocalTime.now();
            tE4 = ChronoUnit.NANOS.between(startTime, endTime) / 1_000_000_000.0;

            // T-Total: Tiempo total de ejecución
            tTotal = tE1 + tE2 + tE3 + tE4;

            System.out.println("Cadena Original: " + datosOriginales);
            System.out.println("Escriptado     : " + encriptado);
            System.out.println("Desencriptado  : " + desencriptado);

            // Imprimir los tiempos en segundos con dos decimales
            System.out.println("T-E1 (Lectura del archivo)  : " + df.format(tE1) + " s");
            System.out.println("T-E2 (Generación de claves) : " + df.format(tE2) + " s");
            System.out.println("T-E3 (Cifrado del texto)    : " + df.format(tE3) + " s");
            System.out.println("T-E4 (Descifrado del texto) : " + df.format(tE4) + " s");
            System.out.println("T-Total (Tiempo total)      : " + df.format(tTotal) + " s");

            // Crear la carpeta texto_cifrado si no existe
            Path carpetaDestino = Paths.get("texto_cifrado");
            if (!Files.exists(carpetaDestino)) {
                Files.createDirectory(carpetaDestino);
            }

            // Escribir el texto cifrado en un archivo dentro de la carpeta texto_cifrado
            String archivoDestino = "texto_cifrado/texto_cifrado_de_"+numeroPalabras+"_palabras.txt"; // Nombre del archivo destino
            Files.write(Paths.get(archivoDestino), encriptado.getBytes("UTF-8"));
            System.out.println("Texto cifrado guardado en: " + archivoDestino);

        } catch (IOException | NoSuchAlgorithmException | InvalidKeyException | NoSuchPaddingException
                | IllegalBlockSizeException | BadPaddingException ex) {
            Logger.getLogger(EncriptadorAES.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}