
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
    return key_;
}

std::string PlayfairCipher::applyCipher( const std::string& inputText, const CipherMode cipherMode ) const
{
    // Change J -> I

    // If repeated chars in a digraph add an X or Q if XX

    // If the size of the input is odd, add a trailing Z

    // Loop over the input in Digraphs

    //      - Find the coords in the grid for each digraph

    //      - Apply the rules to these coords to get 'new' coords
    
    //      - Find the letter associated with the new coords

    // return the text

    if (cipherMode==cipherMode){}
    std::cout << "Doesn't do anything yet." << std::endl;
    return inputText;
}
