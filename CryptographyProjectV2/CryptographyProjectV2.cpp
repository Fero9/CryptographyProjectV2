// CryptographyProjectV2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

using namespace std;

string encrypt(string message, int shift) {
    string result = "";
    
    for (int i = 0; i < message.length(); i++)
    {
        char c = message[i];
        if (isalpha(c)) {
            c = toupper(c);
            c = ((c - 'A' + shift) % 26) + 'A';
        }
        result += c;
    }
    return result;
}

string decrypt(string message, int shift) {
    return encrypt(message, 26 - shift);
}

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

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
