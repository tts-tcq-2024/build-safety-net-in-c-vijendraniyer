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

// Function prototypes
static char getSoundexCodeForCharacter(char c);
static void initializeSoundex(char *soundex, char firstChar);
static int canAddCodeToSoundex(char code, const char *soundex, int sIndex);
static void addCodeToSoundex(char *soundex, char code, int *sIndex);
static void processCharacter(char c, char *soundex, int *sIndex);
static void iterateCharacters(const char *name, char *soundex);
static void processNameCharacters(const char *name, char *soundex);
static void handleNullInputs(const char *name, char *soundex);
static void generateSoundex(const char *name, char *soundex);

// Get the Soundex digit for a character
static char getSoundexCodeForCharacter(char c) {
    c = toupper(c); // Convert character to uppercase
    for (int i = 0; i < sizeof(soundexTable) / sizeof(soundexTable[0]); i++) {
        if (soundexTable[i].letter == c) {
            return soundexTable[i].code;
        }
    }
    return '0'; // Return '0' for non-alphabetic characters
}

// Initialize the Soundex code with the first character of the name
static void initializeSoundex(char *soundex, char firstChar) {
    if (soundex == NULL) return; // Ensure soundex is not NULL
    soundex[0] = toupper(firstChar); // Set the first character to uppercase
    memset(soundex + 1, '0', SOUND_EX_LENGTH - 1); // Fill remaining with '0'
    soundex[SOUND_EX_LENGTH] = '\0'; // Null-terminate the string
}

// Determine if the code can be added to Soundex
static int canAddCodeToSoundex(char code, const char *soundex, int sIndex) {
    return code != '0' && (sIndex == 1 || code != soundex[sIndex - 1]);
}

// Add the Soundex code to the output
static void addCodeToSoundex(char *soundex, char code, int *sIndex) {
    if (canAddCodeToSoundex(code, soundex, *sIndex)) {
        soundex[(*sIndex)++] = code; // Add code and increment index
    }
}

// Process a character and update the Soundex code
static void processCharacter(char c, char *soundex, int *sIndex) {
    char code = getSoundexCodeForCharacter(c);
    addCodeToSoundex(soundex, code, sIndex);
}

// Iterate over the characters of the name and process them
static void iterateCharacters(const char *name, char *soundex) {
    int sIndex = 1; // Index for the Soundex code
    for (int cIndex = 1; name[cIndex] && sIndex < SOUND_EX_LENGTH; cIndex++) {
        processCharacter(name[cIndex], soundex, &sIndex);
    }
}

// Process the name to generate the Soundex code
static void processNameCharacters(const char *name, char *soundex) {
    if (name == NULL || soundex == NULL) return; // Handle NULL inputs
    iterateCharacters(name, soundex); // Iterate and process characters
}

// Handle NULL inputs for generateSoundex
static void handleNullInputs(const char *name, char *soundex) {
    if (soundex != NULL) {
        strcpy(soundex, "0000"); // Set default value if name is NULL
    }
}

// Generate the Soundex code for a given name
static void generateSoundex(const char *name, char *soundex) {
    if (name == NULL || soundex == NULL) {
        handleNullInputs(name, soundex);
        return;
    }

    initializeSoundex(soundex, name[0]); // Initialize the Soundex with the first character
    processNameCharacters(name, soundex); // Process the rest of the name to complete the Soundex code
}

#endif // SOUNDEX_H
