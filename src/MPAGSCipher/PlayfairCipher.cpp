
// Standard library includes
#include <iostream>
#include <string>
#include <algorithm>
#include <map>

#include <vector>

// Out project headers
#include "PlayfairCipher.hpp"

PlayfairCipher::PlayfairCipher( const std::string& key ) { //Constructor for the PlayfairCipher class, uses the setKey method to set the key. (set the key_ ???)
    setKey(key);
}

std::string PlayfairCipher::setKey( const std::string& key ) {
    // store the original key
    key_ = key;

    // Append the alphabet
    for ( size_t i{0}; i < alphabetSize_; ++i ) {
        key_+=alphabet_[i];
    }

    // Make sure the key is upper case
    std::string::iterator iter1 { key_.begin() };
    std::transform( key_.begin(), key_.end(), key_.begin(), ::toupper );

    // Remove non-alpha characters
    /*auto checkIsAlpha = [] (char& c) {
        if (isalpha(c)==0) { // If the character is not alphabetic
            return true;
        }
        else {
            return false;
        }
    };*/
    auto charsToRemove { std::remove_if( key_.begin(), key_.end(), [] (char& c) { return !std::isalpha(c); } ) };
    key_.erase(charsToRemove,key_.end());

    // Change J -> I
    std::transform( key_.begin(), key_.end(), key_.begin(), [] (char& c) { if ( c == 'J' ) { return 'I'; } else { return c; }; } );

    // Remove duplicated letters
    std::string encounteredLetters{""};
    auto findDuplicates = [&] ( char& c ) {
        if (encounteredLetters.find(c) != std::string::npos) {
            return true;
        }
        else {
            encounteredLetters+=c;
            return false;
        }
    };
    auto duplicatedToRemove { std::remove_if( key_.begin(), key_.end(), findDuplicates ) };
    key_.erase(duplicatedToRemove,key_.end());


    // Store the coords of each letter
    // Used to create a map of a char -> pair of ints
    using Str2PairMap = std::map<char, std::pair<int,int>>;
    // Used to create a map of a pair of ints -> char
    using Pair2StrMap = std::map<std::pair<int,int>, char>;

    // Make instances of these maps
    Str2PairMap stringtocoords;
    Pair2StrMap coordstostring;

    //Loop over the whole key and assign each letter to its coordinates in the map
    for (size_t i{0}; i < key_.size(); i++) {
        int j = i;
        int xcoord{ j%5 };
        int ycoord{( j/5 )};
        std::pair<int,int> coords{xcoord,ycoord};
        stringtocoords[key_[i]] = coords;
        coordstostring[coords] = key_[i];
    };

    /*for ( auto p : stringtocoords ) {
        std::cout << p.first << ": (" << p.second.first << "," << p.second.second << ")" << std::endl;
    }
    for ( auto p : coordstostring ) {
        std::cout << "(" <<p.first.first << "," << p.first.second << ") :" << p.second << std::endl;
    }*/

    // Store the playfair cipher key map
    stringToCoords_ = stringtocoords;
    coordsToString_ = coordstostring;

    return key_;
}

std::string PlayfairCipher::applyCipher( const std::string& inputText, const CipherMode cipherMode ) const
{
    // Copy the input text so it can be changed
    std::string cipherText{inputText};

    // Change J -> I
    std::transform( cipherText.begin(), cipherText.end(), cipherText.begin(), [] (char& c) { if ( c == 'J' ) { return 'I'; } else { return c; }; } );

    // If repeated chars in a digraph add an X or Q if XX
    // Loop over every other input character
    std::cout << cipherText << std::endl;

    for (size_t i{0}; i < cipherText.size(); i+=2) {
        //If the next letter is the same as the current letter insert a Q after it if it's an X, otherwise add an X
        if (cipherText[i] == cipherText[i+1]) {
            if (cipherText[i] == 'X') {
                cipherText.insert(i+1,1,'Q');
            }
            else {
                cipherText.insert(i+1,1,'X');
            }
        }
    }

    // If the size of the input is odd, add a trailing Z unless the last letter is a Z, in which case add an X
    if ( (cipherText.size() % 2) == 1 ) {
        if ( *cipherText.end() == 'Z' ) {
            cipherText.append("X");
        }
        else {
            cipherText.append("Z");
        }
    }

    std::cout << cipherText << std::endl;

    // Loop over the input in Digraphs
    for ( size_t i{0}; i < cipherText.size(); i += 2) {

    //      - Find the coords in the grid for each digraph
        auto firstCoord {stringToCoords_.find(cipherText[i])};
        auto secondCoord {stringToCoords_.find(cipherText[i+1])};

        // Make sure the coordinates are actually found in the key
        if ( firstCoord==stringToCoords_.end() || secondCoord==stringToCoords_.end() ) {
            std::cerr << "Error: Letter doesn't have corresponding coordinate." << std::endl;
        }

    //      - Apply the rules to these coords to get 'new' coords
        
    
    //      - Find the letter associated with the new coords
    }

    // return the text

    if (cipherMode==CipherMode::Decrypt){
    std::cout << "Doesn't do anything yet." << std::endl;
    }
    return inputText;
}
