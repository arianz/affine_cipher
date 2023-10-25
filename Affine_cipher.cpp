#include <iostream>
#include <cstring>
#include <cctype>
#include <cmath>
using namespace std;

// Kelas Affine yang digunakan untuk enkripsi dan dekripsi
class Affine {
    char *ciphertext, *dekripsi;

public:
    // Konstruktor Affine untuk menginisialisasi variabel
    Affine() {
        ciphertext = nullptr;
        dekripsi = nullptr;
    }

    // Metode Enkripsi untuk mengenkripsi teksBiasa menggunakan rumus Affine Cipher
    char *Enkripsi(const char *teksBiasa, int a, int b) {
        int panjang = strlen(teksBiasa);
        ciphertext = new char[panjang + 1];
        for (int i = 0; i < panjang; i++) {
            if (isupper(teksBiasa[i])) {
                int asli = teksBiasa[i] - 'A';
                int terenkripsi = (((asli * a) + b) % 26);
                ciphertext[i] = terenkripsi + 'A';
                cout << "Langkah " << i + 1 << " - Enkripsi: " << teksBiasa[i] << " -> " << static_cast<char>(asli + 'A') << " * " << a << " + " << b << " % 26 = " << static_cast<char>(terenkripsi + 'A') << endl;
            } else if (islower(teksBiasa[i])) {
                int asli = teksBiasa[i] - 'a';
                int terenkripsi = (((asli * a) + b) % 26);
                ciphertext[i] = terenkripsi + 'a';
                cout << "Langkah " << i + 1 << " - Enkripsi: " << teksBiasa[i] << " -> " << static_cast<char>(asli + 'a') << " * " << a << " + " << b << " % 26 = " << static_cast<char>(terenkripsi + 'a') << endl;
            } else {
                ciphertext[i] = teksBiasa[i];
            }
        }
        ciphertext[panjang] = '\0';
        return ciphertext;
    }

    // Metode Dekripsi untuk mendekripsi teksCipher menggunakan rumus Affine Cipher
    char *Dekripsi(const char *teksCipher, int a, int b) {
        int panjang = strlen(teksCipher);
        dekripsi = new char[panjang + 1];
        int inv = Invers(a);
        for (int i = 0; i < panjang; i++) {
            if (isupper(teksCipher[i])) {
                int terenkripsi = teksCipher[i] - 'A';
                int terdekripsi = ((inv * (terenkripsi - b + 26)) % 26);
                dekripsi[i] = terdekripsi + 'A';
                cout << "Langkah " << i + 1 << " - Dekripsi: " << teksCipher[i] << " -> " << inv << " * (" << terenkripsi - b + 26 << ") % 26 = " << static_cast<char>(terdekripsi + 'A') << endl;
            } else if (islower(teksCipher[i])) {
                int terenkripsi = teksCipher[i] - 'a';
                int terdekripsi = ((inv * (terenkripsi - b + 26)) % 26);
                dekripsi[i] = terdekripsi + 'a';
                cout << "Langkah " << i + 1 << " - Dekripsi: " << teksCipher[i] << " -> " << inv << " * (" << terenkripsi - b + 26 << ") % 26 = " << static_cast<char>(terdekripsi + 'a') << endl;
            } else {
                dekripsi[i] = teksCipher[i];
            }
        }
        dekripsi[panjang] = '\0';
        return dekripsi;
    }

private:
    // Metode untuk mencari invers a (untuk invers modulo 26)
    int Invers(int angka) {
        for (int i = 1; i < 26; i++) {
            if ((i * angka) % 26 == 1)
                return i;
        }
        return 1;
    }
};

int main() {
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    char *teksBiasa, *teksCipher, *teksDekripsi;
    int a = 1, b = 0;

    teksBiasa = nullptr;

    // Meminta pengguna untuk memasukkan teks
    cout << "Masukkan Teks: ";
    char input[1000];
    cin.getline(input, sizeof(input));
    teksBiasa = new char[strlen(input) + 1];
    strcpy(teksBiasa, input);

    // Meminta pengguna untuk memasukkan nilai a dan b
    cout << "Masukkan a (prima): ";
    cin >> a;
    cout << "Masukkan b: ";
    cin >> b;

    // Membuat objek Affine dan melakukan enkripsi dan dekripsi
    Affine affine;
    teksCipher = affine.Enkripsi(teksBiasa, a, b);
    cout << "Teks Terenkripsi: " << teksCipher << endl;
    teksDekripsi = affine.Dekripsi(teksCipher, a, b);
    cout << "Teks Terdekripsi: " << teksDekripsi << endl;

    // Membersihkan alokasi memori
    delete[] teksBiasa;
    delete[] teksCipher;
    delete[] teksDekripsi;

    return 0;
}