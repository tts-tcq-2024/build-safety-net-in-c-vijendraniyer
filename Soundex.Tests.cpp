#include <gtest/gtest.h>
#include "Soundex.h"

// Test case for generating Soundex code for a standard name
TEST(SoundexTestsuite, GenerateSoundex_StandardName) {
    char soundex[5];
    generateSoundex("Vijendran", soundex);
    ASSERT_STREQ(soundex, "V253");
}

// Test case for handling mixed case letters
TEST(SoundexTestsuite, GenerateSoundex_MixedCaseName) {
    char soundex[5];
    generateSoundex("vIjeNDran", soundex);
    ASSERT_STREQ(soundex, "V253"); // Soundex should be case-insensitive
}

// Test case for handling empty strings
TEST(SoundexTestsuite, GenerateSoundex_EmptyString) {
    char soundex[5];
    generateSoundex("", soundex);
    ASSERT_STREQ(soundex, "0000"); // Should return the default Soundex code
}

// Test case for handling a single alphabetic character
TEST(SoundexTestsuite, GenerateSoundex_SingleCharacter) {
    char soundex[5];
    generateSoundex("A", soundex);
    ASSERT_STREQ(soundex, "A000"); // Should return the character followed by three zeros
}

// Test case for handling repeated consonants
TEST(SoundexTestsuite, GenerateSoundex_RepeatedConsonants) {
    char soundex[5];
    generateSoundex("AABB", soundex);
    ASSERT_STREQ(soundex, "A100"); // Only the first unique consonant should be counted
}

// Test case for handling non-alphabetic characters mixed with letters
TEST(SoundexTestsuite, GenerateSoundex_NonAlphabeticCharacters) {
    char soundex[5];
    generateSoundex("A1B2C", soundex);
    ASSERT_STREQ(soundex, "A120"); // Non-alphabetic characters should not affect the Soundex
}

// Test case for handling longer names
TEST(SoundexTestsuite, GenerateSoundex_LongName) {
    char soundex[5];
    generateSoundex("Alexander", soundex);
    ASSERT_STREQ(soundex, "A452"); // Expected Soundex code for "Alexander"
}

// Test case for handling NULL input for Soundex array
TEST(SoundexTestsuite, GenerateSoundex_NullSoundexArray) {
    generateSoundex("Alexander", NULL); // No assertion, checks for no crash
}

// Test case for handling NULL input for name
TEST(SoundexTestsuite, GenerateSoundex_NullName) {
    char soundex[5];
    generateSoundex(NULL, soundex);
    ASSERT_STREQ(soundex, "0000"); // Should return the default Soundex code
}
