// Implementation of : https://www.youtube.com/watch?v=j2HSd3HCpDs
// WARNING :: This compression will produce incorrect compressed string 
//            if curCount exceeds 9 bits i.e. 512 
//
//
// Example:
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

// Generates a ASCII equivalent of the given string to compare with
// the compressed version
string toASCIIString(string inputString){
    stringstream ss;
    for (int i = 0; i < inputString.length(); i++){
        ss << "  " << bitset<7>((int)inputString[i]) << " ";
    }

    return ss.str();
}

void testing(){
    char sampleChar = '\n';
    cout << bitset<BITS>((int)sampleChar).to_string() << endl;
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
    cout << "Enter a string to compress: ";

    string inputString; cin >> inputString;
    
    string original = toASCIIString(inputString);
    string compressed = compress(inputString);

    cout << "Original:\t" << original << endl;
    cout << "Compressed:\t" << compressed << endl << endl;

    cout << "String was ";
    if (compare(original, compressed) > 0){
        cout << compare(original, compressed) << "% compressed!" << endl;
    } else {
        cout << -1*compare(original, compressed) << "% expanded! Enter a string with lower entropy." << endl;        
    }
}