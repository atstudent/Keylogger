#include <iostream>
#include <string>
#include<cstring>
#include<fstream>
// Crypto++ libraries for encryption
#include <cryptopp/aes.h> // AES encryption algorithm
#include <cryptopp/modes.h>// Cipher modes (e.g., ECB mode)
#include <cryptopp/filters.h> //Filters for processing data
#include <cryptopp/base64.h> // Base64 encoding for data
#include<curl/curl.h>// libcurl library for handling URLs

using namespace std;

class EmailSender {
public:
    // function prototypes

     // Function to log messages to a specified log file
    void log(const string& logFilename);
    // Helper function for AES ECB encryption
    string aes_ecb_encrypt(const std::string& plaintext, const std::string& key);
    // Function to encrypt log data and write it to a file
    void Encrypt_func(const string& logFilename, ofstream& w);
    // Function to send an email with an attachment
    int SendMailWithAttachment(const string& logFilename, ofstream &w);

};


