#include <iostream>
#include <fstream>
#include <string>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include <cryptopp/base64.h>

std::string aes_ecb_decrypt(const std::string& ciphertext, const std::string& key) {
    CryptoPP::AES::Decryption aesDecryption;
    aesDecryption.SetKey(reinterpret_cast<const CryptoPP::byte*>(key.data()), key.size());

    CryptoPP::ECB_Mode_ExternalCipher::Decryption ecbDecryption(aesDecryption);

    std::string decryptedText;

    // Use CryptoPP::Base64Decoder for Base64 decoding
    CryptoPP::StringSource(ciphertext, true, new CryptoPP::Base64Decoder(new CryptoPP::StreamTransformationFilter(ecbDecryption, new CryptoPP::StringSink(decryptedText))));

    return decryptedText;
}

void Decrypt_func() {
    std::string key="2222222222222222";
    std::string encryptedText;
  

    if (key.size() != 16) {
        std::cerr << "Invalid key size. Key must be 16 characters long." << std::endl;
        return;
    }

    // Read content from Send.txt
    std::ifstream sendFile("Send.txt");
    if (!sendFile.is_open()) {
        std::cerr << "Error opening Send.txt." << std::endl;
        return;
    }

    // Read entire content of the file as a single string
    encryptedText.assign(std::istreambuf_iterator<char>(sendFile), std::istreambuf_iterator<char>());

    sendFile.close();

    // Decryption
    std::string decryptedText = aes_ecb_decrypt(encryptedText, key);

    // Write decrypted text to Decrypted.txt
    std::ofstream decryptedFile("Decrypted.txt");
    if (!decryptedFile.is_open()) {
        std::cerr << "Error creating Decrypted.txt." << std::endl;
        return;
    }

    decryptedFile << decryptedText;

    decryptedFile.close();

    std::cout << "Decryption and file handling complete." << std::endl;
}

int main() {
    Decrypt_func();  // Call the Decrypt_func function

    return 0;
}
