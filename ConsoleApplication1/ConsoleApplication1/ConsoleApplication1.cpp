// ConsoleApplication1.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <iomanip>
#include "sodium.h"
#include <fstream>
#include <string>
using namespace std;




int main()
{
    if (sodium_init() < 0) {
        /* panic! the library couldn't be initialized, it is not safe to use */
        return -1;
    }
    std::cout << "Hello World!\n";
    std::ifstream inFile;
    inFile.open("C:\\pruebacifrar.txt");
    string sum;
    string x;
    if (!inFile) {
        std::cout << "Unable to open file";
        exit(1); 
    }

    while (inFile >> x) {
        sum = sum + x;
    }

    inFile.close();
    std::cout << "Sum = " << sum << std::endl;
    unsigned char cat[50];
    strcpy((char*)cat, sum.c_str());
    std::cout << "Suma = " << cat << std::endl;

    unsigned char buf[32];
    randombytes_buf(buf, sizeof buf);
    for(int i=0;i<sizeof buf;i++)
        std::cout << std::setfill('0') << std::setw(2) << std::hex << int(buf[i]);
    std::cout << std::endl;

    unsigned char plaintext[]=" Holacomoestas";
    unsigned char plaintext1[] = "Holacomoestas";
    int plaintext_len = strlen((char*)cat);
    int plaintext_len1 = strlen((char*)plaintext1);
    unsigned char* ciphertext = new unsigned char[plaintext_len];
    unsigned char* deciphertext = new unsigned char[plaintext_len];
    unsigned char key[crypto_stream_chacha20_KEYBYTES];
    unsigned char nonc[crypto_stream_chacha20_NONCEBYTES];

    crypto_secretbox_keygen(key);
    randombytes_buf(nonc, sizeof nonc);

    int errorcode = crypto_stream_chacha20_xor(ciphertext, cat, plaintext_len, nonc, key);
    for (int i = 0; i < plaintext_len; i++) {
        std::cout << std::setfill('0') << std::setw(2) << std::hex << int(ciphertext[i]);
    }
    std::cout << std::endl;

    errorcode = crypto_stream_chacha20_xor(deciphertext, plaintext1, plaintext_len1, nonc, key);
    for (int i = 0; i < plaintext_len1; i++) {
        std::cout << std::setfill('0') << std::setw(2) << std::hex << int(deciphertext[i]);
    }
    std::cout << std::endl;


    return 0;
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
