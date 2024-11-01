#include <ctype.h>
#include <string.h>
#include <stdio.h>

#define SOUND_EX_LENGTH 4  // Define the fixed length of the Soundex code

// Struct to map letters to corresponding Soundex codes
typedef struct {
    char letter;  // Character to be mapped
    char code;    // Soundex code for the character
} SoundexMapping;

// Soundex mappings for alphabetic characters
static const SoundexMapping soundexTable[] = {
    {'A', '0'}, {'B', '1'}, {'C', '2'}, {'D', '3'},
    {'E', '0'}, {'F', '1'}, {'G', '2'}, {'H', '0'},
    {'I', '0'}, {'J', '2'}, {'K', '2'}, {'L', '4'},
    {'M', '5'}, {'N', '5'}, {'O', '0'}, {'P', '1'},
    {'Q', '2'}, {'R', '6'}, {'S', '2'}, {'T', '3'},
    {'U', '0'}, {'V', '1'}, {'W', '0'}, {'X', '2'},
    {'Y', '0'}, {'Z', '2'}
};

/**
 * @brief Gets the Soundex code for a given character.
 * 
 * @param c The character to look up.
 * @return char The Soundex code corresponding to the character.
 *         Returns '0' if the character is not found in the mapping.
 */
static char getSoundexCodeForCharacter(char c) {
    c = toupper(c);  // Convert character to uppercase
    for (int i = 0; i < sizeof(soundexTable) / sizeof(soundexTable[0]); i++) {
        if (soundexTable[i].letter == c) {
            return soundexTable[i].code;  // Return matching code
        }
    }
    return '0';  // Return '0' for characters not in the mapping
}

/**
 * @brief Initializes the Soundex array with the first letter of the name.
 * 
 * @param soundex Pointer to the Soundex character array.
 * @param firstChar The first character of the name.
 */
static void initializeSoundex(char *soundex, char firstChar) {
    if (soundex) {  // Check if soundex is not NULL
        soundex[0] = toupper(firstChar);  // Set first character
        memset(soundex + 1, '0', SOUND_EX_LENGTH - 1);  // Fill remaining with '0'
        soundex[SOUND_EX_LENGTH] = '\0';  // Null-terminate the string
    }
}

/**
 * @brief Fills remaining Soundex array positions with '0' if needed.
 * 
 * @param soundex Pointer to the Soundex character array.
 * @param sIndex Pointer to the current index in the Soundex array.
 */
static void addPadding(char *soundex, int *sIndex) {
    if (soundex) {  // Check if soundex is not NULL
        while (*sIndex < SOUND_EX_LENGTH) {
            soundex[(*sIndex)++] = '0';  // Add '0' until length is reached
        }
        soundex[SOUND_EX_LENGTH] = '\0';  // Null-terminate the string
    }
}

/**
 * @brief Checks if the Soundex code can be added to the array.
 * 
 * @param code The Soundex code to add.
 * @param soundex Pointer to the Soundex character array.
 * @param sIndex Pointer to the current index in the Soundex array.
 * @return int Returns 1 if the code can be added, 0 otherwise.
 */
static int canAddCode(char code, char *soundex, int *sIndex) {
    return code != '0' && *sIndex < SOUND_EX_LENGTH && soundex[*sIndex - 1] != code;
}

/**
 * @brief Processes a single character in the name to get and add its Soundex code.
 * 
 * @param c The character to process.
 * @param soundex Pointer to the Soundex character array.
 * @param sIndex Pointer to the current index in the Soundex array.
 */
static void processSingleCharacter(char c, char *soundex, int *sIndex) {
    char code = getSoundexCodeForCharacter(c);
    if (canAddCode(code, soundex, sIndex)) {
        soundex[(*sIndex)++] = code;  // Add code and increment index
    }
}

/**
 * @brief Validates the input name; checks if NULL, empty, or non-alphabetic start.
 * 
 * @param name The input name string to validate.
 * @return int Returns 1 if the input is invalid, 0 if valid.
 */
static int isInputInvalid(const char *name) {
    return !name || name[0] == '\0' || !isalpha(name[0]);
}

/**
 * @brief Handles invalid input by setting Soundex to "0000".
 * 
 * @param soundex Pointer to the Soundex character array.
 */
static void handleInvalidInput(char *soundex) {
    if (!soundex) return;  // If soundex is NULL, do nothing
    strcpy(soundex, "0000");  // Set default invalid code
}

/**
 * @brief Processes all characters in the name (except the first one).
 * 
 * @param name The input name string.
 * @param soundex Pointer to the Soundex character array.
 * @param sIndex Pointer to the current index in the Soundex array.
 */
static void processNameCharacters(const char *name, char *soundex, int *sIndex) {
    for (int i = 1; name[i] != '\0' && *sIndex < SOUND_EX_LENGTH; i++) {
        processSingleCharacter(name[i], soundex, sIndex);  // Process each character
    }
}

/**
 * @brief Generates Soundex code for a given name.
 * 
 * @param name The input name string.
 * @param soundex Pointer to the Soundex character array where the result is stored.
 */
static void generateSoundex(const char *name, char *soundex) {
    if (isInputInvalid(name)) {  // Check if input name is invalid
        handleInvalidInput(soundex);  // Set default code for invalid input
        return;
    }

    if (soundex) {  // Ensure soundex is not NULL before proceeding
        initializeSoundex(soundex, name[0]);  // Initialize with the first character
        int sIndex = 1;  // Start index for adding Soundex codes
        processNameCharacters(name, soundex, &sIndex);  // Process remaining characters
        addPadding(soundex, &sIndex);  // Add padding if necessary
    }
}
