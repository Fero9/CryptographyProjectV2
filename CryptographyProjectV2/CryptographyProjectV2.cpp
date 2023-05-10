//Ukljucujemo header fajlove
#include <iostream>
#include <string>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

//Definisemo funkciju "encrypt" koja uzima string "message" i "shift" integer kao argumente
//i vraca enkriptovanu poruku
//Ova funkcija prolazi kroz svaki karakter u poruci, konvertuje u velika slova
//i onda menja karaktere za odredjeni broz pozicija
string encrypt(string message, int shift) {
    string result = "";
    
    for (int i = 0; i < message.length(); i++)
    {
        char c = message[i];
        if (isalpha(c)) {
            c = toupper(c);
            //Ovde "c" predstavlja trenuatan karakter koji se enkriptuje
            //"shift" je broj pozicija koje ce se menjati u alfabeti
            //"A" je ASCII vrednost velikog slova A
            //%26 obezbedjuje da se pomereni karakter vraca na pocetak ako ode iznad slova Z
            c = ((c - 'A' + shift) % 26) + 'A';
        }
        result += c;
    }
    return result;
}

//Takodje imamo funkciju "decrypt" koja uzima enkriptovanu poruku i shift integer kao argumente
//i vraca dekriptovanu poruku
string decrypt(string message, int shift) {
    return encrypt(message, 26 - shift);
}

//Prvo definisemo 3 pomocne funkcije koje se koriste u RSA algoritmu

//Ova funkcija uzima dva integera: a i b i vraca najveci zajednicki delilac
// Calculate Greatest Common Divisor
int gcd(int a, int b)
{
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

//Ovde funkcija 'modMultiply' uzima 3 integera: a, b i mod i vraca '(a * b) % mod'
// Koristimo ovu funkciju da izracunamo modularne proizvode RSA algoritma
// Calculate Modulo Multiplication
int modMultiply(int a, int b, int mod)
{
    int resultRSA = 0;
    a = a % mod;
    while (b > 0)
    {
        if (b % 2 == 1)
            resultRSA = (resultRSA + a) % mod;
        a = (a * 2) % mod;
        b /= 2;
    }
    return resultRSA;
}

//Ova funkcija takodje uzima 3 integrea: base, exponent i mod i vraca 'base^exponent % mod' koristeci modularnu exponenciju
// Koristimo je za bi smo izracunali modularni exponent u RSA algoritmu
// Calculate Modular Exponentiation
int modExp(int base, int exponent, int mod)
{
    int result = 1;
    base = base % mod;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
            result = modMultiply(result, base, mod);
        base = modMultiply(base, base, mod);
        exponent /= 2;
    }
    return result;
}


//Ovde generisemo privatne i javne kljuceve za RSA koristeci dva prosta broja: p i q
// Funkcija racuna 'n = p * q' i 'phi(n) = (p - 1) * (q - 1)' gde je 'phi(n)' Ojlerova funkcija
// Javni kljuc je: (n, e)
// Privatni kljuc je: (n, d)
// Generate Public and Private Keys
void generateKeys(int p, int q, int& n, int& e, int& d)
{
    // Calculate n and phi(n)
    n = p * q;
    int phiN = (p - 1) * (q - 1);

    // Find e such that gcd(e, phi(n)) = 1
    for (e = 2; e < phiN; e++)
    {
        if (gcd(e, phiN) == 1)
            break;
    }

    // Find d such that d * e ≡ 1 (mod phi(n))
    for (d = 1; d < phiN; d++)
    {
        if ((d * e) % phiN == 1)
            break;
    }
}

// Encrypt Message
int encryptRSA(int messageRSA, int e, int n)
{
    return modExp(messageRSA, e, n);
}

// Decrypt Message
int decryptRSA(int encryptedMessageRSA, int d, int n)
{
    return modExp(encryptedMessageRSA, d, n);
}



//Sto se tice Cezarove sifre, proveravamo da li radi
//getline funkciju koristimo da procitamo poruku kao string
int main()
{
    string message;
    int shift;

    cout << "Enter the message you wish to encrypt: ";
    getline(cin, message);

    cout << "Enter the number of shifts: ";
    cin >> shift;

    string encrypted = encrypt(message, shift);
    string decrypted = decrypt(encrypted, shift);

    cout << "Encrypted message is: " << encrypted << endl;
    cout << "The decrypted message is: " << decrypted << endl;

    // Generate Public and Private Keys
    int p = 54;
    int q = 35;
    int n, e, d;
    generateKeys(p, q, n, e, d);
    cout << "Public Key (n, e): (" << n << ", " << e << ")" << endl;
    cout << "Private Key (n, d): (" << n << ", " << d << ")" << endl;

    // Encrypt and Decrypt Message
    int messageRSA = 369369;
    cout << "Original Message: " << messageRSA << endl;
    int encryptedMessageRSA = encryptRSA(messageRSA, e, n);
    cout << "Encrypted Message: " << encryptedMessageRSA << endl;
    int decryptedMessageRSA = decryptRSA(encryptedMessageRSA, d, n);
    cout << "Decrypted Message: " << decryptedMessageRSA << endl;

    return 0;
}
