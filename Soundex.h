#include <ctype.h>
#include <string.h>
#include <stdio.h>

#define SOUND_EX_LENGTH 4

typedef struct {
    char letter;
    char code;
} SoundexMapping;

static const SoundexMapping soundexTable[] = {
    {'A', '0'}, {'B', '1'}, {'C', '2'}, {'D', '3'},
    {'E', '0'}, {'F', '1'}, {'G', '2'}, {'H', '0'},
    {'I', '0'}, {'J', '2'}, {'K', '2'}, {'L', '4'},
    {'M', '5'}, {'N', '5'}, {'O', '0'}, {'P', '1'},
    {'Q', '0'}, {'R', '6'}, {'S', '2'}, {'T', '3'},
    {'U', '0'}, {'V', '1'}, {'W', '0'}, {'X', '2'},
    {'Y', '0'}, {'Z', '2'}
};

static char getSoundexCodeForCharacter(char c) {
    c = toupper(c);
    for (int i = 0; i < sizeof(soundexTable) / sizeof(soundexTable[0]); i++) {
        if (soundexTable[i].letter == c) {
            return soundexTable[i].code;
        }
    }
    return '0';
}

static void initializeSoundex(char *soundex, char firstChar) {
    soundex[0] = toupper(firstChar);
    memset(soundex + 1, '0', SOUND_EX_LENGTH - 1);
    soundex[SOUND_EX_LENGTH] = '\0';
}

static int canAddCodeToSoundex(char code, const char *soundex, int sIndex) {
    return code != '0' && (sIndex == 1 || code != soundex[sIndex - 1]);
}

static void addCodeToSoundex(char *soundex, char code, int *sIndex) {
    if (canAddCodeToSoundex(code, soundex, *sIndex) && *sIndex < SOUND_EX_LENGTH) {
        soundex[(*sIndex)++] = code;
    }
}

static void generateSoundex(const char *name, char *soundex) {
    if (name == NULL || soundex == NULL) {
        strcpy(soundex, "0000");
        return;
    }

    initializeSoundex(soundex, name[0]);

    int sIndex = 1;
    char prevCode = '0';

    for (int i = 1; name[i] != '\0' && sIndex < SOUND_EX_LENGTH; i++) {
        char code = getSoundexCodeForCharacter(name[i]);

        // Skip if it's the same as the previous code or is '0'
        if (code != '0' && code != prevCode) {
            addCodeToSoundex(soundex, code, &sIndex);
        }

        prevCode = code;
    }

    // Ensure the Soundex code is null-terminated and padded
    while (sIndex < SOUND_EX_LENGTH) {
        soundex[sIndex++] = '0';
    }
    soundex[SOUND_EX_LENGTH] = '\0';
}
