// Implementation of : https://www.youtube.com/watch?v=j2HSd3HCpDs
// WARNING :: This compression will produce incorrect compressed string 
//            if curCount exceeds 9 bits i.e. 512 in other words if size
//            of dictionary exceeds 256 in count
//
//=======================================================================
// Example:
//=======================================================================
//   +-------------------------------------------------------------------------------------------------------------------------------------------------+
//   | $ ./lzw                                                                                                             |
//   | Copyleft (ɔ) 2017                                                                                                                               |
//   | LZW implementation (compression level is inversely proportional to entropy of string)                                                           |
//   |                                                                                                                                                 |
//   | Enter a string to compress: thisisastring                                                                                                       |
//   | Original:    001110100 001101000 001101001 001110011 001101001 001110011 001100001 001110011 001110100 001110010 001101001 001101110 001100111  |
//   | Compressed:  001110100 001101000 001101001 001110011 100000010 001100001 001110011 001110100 001110010 001101001 001101110                    |
//   +-------------------------------------------------------------------------------------------------------------------------------------------------+

#include<algorithm> 
#include<bitset> 
#include<cstdlib>
#include<iostream>
#include<list>
#include<map>
#include<string>
#include<sstream>

// if TESTING is 1 program enters testing mode and exits after
// running testing() without further executing main()
#define TESTING 0

using namespace std;

// Number of bits in each of the compressed phase 
const int BITS = 9;

string compress(string inputString){
    string result = "";

    map<string, int> dictionary;
    int curCount = 255;

    // iterates over every character except the last one
    for (int i = 0; i < inputString.length() - 1; i++){
        // curString stores next 2 characters at the start of each
        // iteration
        std::string curString = "";
        curString += inputString[i];
        curString += inputString[i+1];

        // loops until a sequence of character is encountered
        // which is new
        while (dictionary.find(curString) != dictionary.end()){
            curString += curString[2 + i++];
        }

        // this sequence is then inserted to the dictionary
        dictionary.insert(pair<string, int>(curString, ++curCount));

        // Last character is removed since rest of the string is
        // a match from dictionary
        curString = curString.substr(0, curString.length()-1);

        if (curString.length() == 1){
            result += bitset<BITS>((int)curString[0]).to_string();
        } else {
            result += bitset<BITS>(dictionary[curString]).to_string();
        }
        result += " ";
    }

    result += bitset<BITS>(inputString[inputString.length()-1]).to_string();

    return result;
}

int binToDec(string binary){
    long bin, dec = 0, rem, num, base = 1;
    stringstream ss(binary);
    
    ss >> num;
    
    bin = num;
    
    while (num > 0) {
        rem = num % 10;
        dec = dec + rem * base;
        base = base * 2;
        num = num / 10;
    }
    return dec;
}

string decompress(string inputString){
    list<string> phaseList; // Reminds of phase-space :-P
    map<int, string> dictionary;

    string result = "";
    stringstream ss;

    int inputStringLen = inputString.length();
    int curCount = 255;

    if (inputStringLen%BITS != 0){
        throw length_error("Length of string to decompress should be multiple of BITS");
    }

    for (int i = 0; i < inputStringLen/BITS; i++){
        phaseList.push_back(inputString.substr(i*BITS, BITS));
    } 

    while (phaseList.size()-1){
        int curNum = binToDec(phaseList.front());
        phaseList.pop_front();
        int nextNum = binToDec(phaseList.front());
        if (curNum <= 255) {
            result += (char)curNum;
            string toAdd = "";
            ss << (char)curNum << (char)nextNum;
            dictionary.insert(pair<int, string>(++curCount, ss.str()));
        } else {
            result += dictionary[curNum];
        }
        ss.str("");
    }

    if (dictionary.find(binToDec(phaseList.front())) != dictionary.end()){
        result += dictionary[binToDec(phaseList.front())];
    } else {
        result += (char)binToDec(phaseList.front());
    }
    return result;
}

void testing(){
    cout << decompress("001110100001101000001101001001110011100000010100000000001100101") << endl;
}

// Generates a ASCII equivalent of the given string to compare with
// the compressed version
string toASCIIString(string inputString){
    stringstream ss;
    for (int i = 0; i < inputString.length(); i++){
        ss << "  " << bitset<7>((int)inputString[i]) << " ";
    }

    return ss.str();
}

// compares size of two string in returns size difference in percentage
float compare(string a, string b){
    a.erase(remove(a.begin(), a.end(), ' '), a.end());
    b.erase(remove(b.begin(), b.end(), ' '), b.end());

    float lenA = a.length();
    float lenB = b.length();

    return (lenA > lenB ? 100-(lenB/lenA)*100 : (100-(lenB/lenA)*100));
}

int main(){
    #if TESTING
        testing();
        return 0;    
    #endif

    cout << "Copyleft (ɔ) 2017" << endl;
    cout << "LZW implementation (compression level is inversely proportional to entropy of string)\n\n";
    
    int choice = -1;

    while (choice !=0 || choice != 1){
        cout << "Enter 0 for compression and 1 for decompression: ";

        cin >> choice;

        if (choice == 0){
            cout << "Enter a string for compression: ";
            
            string inputString;
            cin >> inputString;

            string original = toASCIIString(inputString);
            string compressed = compress(inputString);

            cout << "Original:\t" << original << endl;
            cout << "Compressed:\t" << compressed << endl
                << endl;

            cout << "String was ";
            if (compare(original, compressed) > 0) {
                cout << compare(original, compressed) << "% compressed!" << endl;
            }
            else {
                cout << -1 * compare(original, compressed) << "% expanded! Enter a string with lower entropy." << endl;
            }
        } else {
            cout << "Enter a compressed string: ";
            string compressedString; cin >> compressedString;
            cout << "Decompressed string is: " << decompress(compressedString);
        }
        
    }
}