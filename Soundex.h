#ifndef SOUNDEX_H
#define SOUNDEX_H

#include <ctype.h>
#include <string.h>
#include <stdio.h>

// Constants
#define SOUND_EX_LENGTH 4

// Structure to represent character to Soundex mapping
typedef struct {
    char letter;
    char code;
} SoundexMapping;

// Soundex mapping table
static const SoundexMapping soundexTable[] = {
    {'A', '0'}, {'B', '1'}, {'C', '2'}, {'D', '3'},
    {'E', '0'}, {'F', '1'}, {'G', '2'}, {'H', '0'},
    {'I', '0'}, {'J', '2'}, {'K', '2'}, {'L', '0'},
    {'M', '5'}, {'N', '5'}, {'O', '0'}, {'P', '1'},
    {'Q', '0'}, {'R', '2'}, {'S', '2'}, {'T', '3'},
    {'U', '0'}, {'V', '1'}, {'W', '0'}, {'X', '2'},
    {'Y', '0'}, {'Z', '2'}
};

// Function to get the Soundex digit for a character
static char getSoundexCodeForCharacter(char c) {
    c = toupper(c); // Convert character to uppercase
    for (int i = 0; i < sizeof(soundexTable) / sizeof(soundexTable[0]); i++) {
        if (soundexTable[i].letter == c) {
            return soundexTable[i].code;
        }
    }
    return '0'; // Return '0' for non-alphabetic characters
}

// Initializes the Soundex code with the first character of the name
static void initializeSoundex(char *soundex, char firstChar) {
    if (soundex == NULL) return; // Ensure soundex is not NULL
    soundex[0] = toupper(firstChar); // Set the first character to uppercase
    memset(soundex + 1, '0', SOUND_EX_LENGTH - 1); // Fill remaining with '0'
    soundex[SOUND_EX_LENGTH] = '\0'; // Null-terminate the string
}

// Processes the name to generate the Soundex code
static void processName(const char *name, char *soundex) {
    if (name == NULL || soundex == NULL) return; // Handle NULL inputs

    int sIndex = 1; // Index for the Soundex code
    for (int cIndex = 1; name[cIndex] && sIndex < SOUND_EX_LENGTH; cIndex++) {
        char code = getSoundexCodeForCharacter(name[cIndex]);
        // Add the code if it's not '0' and different from the last added code
        if (code != '0' && code != soundex[sIndex - 1]) {
            soundex[sIndex++] = code; // Add code and increment index
        }
    }
}

// Generates the Soundex code for a given name
static void generateSoundex(const char *name, char *soundex) {
    if (name == NULL || soundex == NULL) {
        if (soundex != NULL) {
            strcpy(soundex, "0000"); // Set default value if name is NULL
        }
        return;
    }

    initializeSoundex(soundex, name[0]); // Initialize the Soundex with the first character
    processName(name, soundex); // Process the rest of the name to complete the Soundex code
}

#endif // SOUNDEX_H
