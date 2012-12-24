/** NetHasher: A Hashing Program for NetStory
 *  @author Oliver Chu
 *  @project NetStory, the networked Cave Story written by 2 Olivers.
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstddef>
#include <string>

using namespace std;

char *getPtrToFileContents(string filePath, int *sz) {
    ifstream inFile;
    size_t size = 0; // here
    inFile.open(filePath.c_str(), ios::in|ios::binary|ios::ate );
    char* oData = NULL;
    inFile.seekg(0, ios::end); // set the pointer to the end
    size = inFile.tellg() ; // get the length of the file
    cout << "Size of file: " << size << "\n";
    inFile.seekg(0, ios::beg); // set the pointer to the beginning
    oData = new char[size + 1]; //  for the '\0'
    inFile.read(oData, size);
    oData[size] = '\0' ; // set '\0'
    cout << "Data size: " << strlen(oData) << "\n";
    sz[0] = (int) size;
    return oData;
}

char *hash(string filePath) {
    char hashCode[32];
    for (int i = 0; i < 32; i++) {
        hashCode[i] = 0;
    }
    int bigness = 4;
    char *memoryAddr = getPtrToFileContents(filePath, &bigness);
    // Initialize the hash code...
    int limit = bigness < 32 ? bigness : 32;
    for (int i = 0; i < limit; i++) {
        hashCode[i] = memoryAddr[i];
    }
    int maximum = bigness - 32;
    // Then do random things to it.
    for (int j = limit; j < maximum; j++) {
        hashCode[j % 32] ^= memoryAddr[j];
        hashCode[(j + 1) % 32] |= memoryAddr[j];
        hashCode[(j + 2) % 32] &= memoryAddr[j];
        int randomAssAddress = (j + 3) % 32;
        hashCode[randomAssAddress] = ~hashCode[randomAssAddress];
    }
    return hashCode;
}

int main() {
    // Call some function here.
    return 0;
}
