#ifndef MPAGSCIPHER_PLAYFAIRCIPHER_HPP
#define MPAGSCIPHER_PLAYFAIRCIPHER_HPP

#include <string>
#include <vector>

#include "CipherMode.hpp"



/**
 * \filePlayfairCipher.hpp
 * \brief Contains the declaration of the PlayfairCipher class
 */

/**
 * \class PlayfairCipher
 * \brief Encrypt or decrypt text using the Playfair cipher with the given key
 */

class PlayfairCipher {
  public:
    /**
     * Create a new PlayfairCipher with the given key
     *
     * \param key the key to use in the cipher
     */
    explicit PlayfairCipher( const std::string& key );

    /**
     * Sets the key (for use in the constructor)
     * 
     * \param key the key to use in the cipher
     */
    std::string setKey ( const std::string& key );

    /**
     * Apply the cipher to the provided text
     *
     * \param inputText the text to encrypt or decrypt
     * \param cipherMode whether to encrypt or decrypt the input text
     * \return the result of applying the cipher to the input text
     */
    std::string applyCipher( const std::string& inputText, const CipherMode cipherMode ) const;

  private:
    /// The alphabet - used to determine the cipher character given the plain character and the key
    const std::vector<char> alphabet_ = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    /// The size of the alphabet
    const std::vector<char>::size_type alphabetSize_ = alphabet_.size();
    

    /// The cipher key
    std::string key_ = "";
};


#endif
