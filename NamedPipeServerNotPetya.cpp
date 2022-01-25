// Emulation of the NotPetya named pipe server 
// By Alice Climent-Pommeret 

// To compile on linux
// sudo apt install g++-mingw-w64
// i686-w64-mingw32-g++ -static NamedPipeServerNotPetya.cpp -o NamedPipeServerNotPetya.exe

#include <iostream>
#include <windows.h>
using namespace std;
int main(int argc, const char **argv)
{

    wcout << "" << endl;
    wcout << "Creation of a named pipe called \\\\.\\pipe\\my_pipe" << endl;
    //pipe creation
    HANDLE pipe = CreateNamedPipe(
        "\\\\.\\pipe\\my_pipe", // name of the pipe
        3, // PIPE_ACCESS_DUPLEX
        6, // PIPE_TYPE_MESSAGE|PIPE_READMODE_MESSAGE
        1, // only one instance of the named pipe
        0, // no outbound buffer
        0, // no inbound buffer
        0, // use default wait time
        NULL // use default security attributes
        );

    if (pipe == NULL || pipe == INVALID_HANDLE_VALUE) {
        wcout << "The named pipe creation failed";
        return 1;
    }
    wcout << "Waiting for a client connection" << endl;
    
    if (ConnectNamedPipe(pipe, NULL)){// This call blocks the process here until a client connection to the pipe
        wcout << "Reading data from the named pipe" << endl;
        wchar_t buffer[2048];
        DWORD numBytesRead = 0;
        // Read data from the pipe
        while (ReadFile(pipe, buffer, 2048 * sizeof(wchar_t), &numBytesRead, NULL)){
       	    wcout << "Credentials sent by the NotPetya dropped binary: " << buffer << endl;
    	}	 
    }
    //Close the pipe
    CloseHandle(pipe);
    wcout << "Done !" << endl;
    return 0;
}
