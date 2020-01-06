#include "Morse.h"

#include <QChar>
#include <QHash>
#include <QString>
#include <QStringList>

#include <array>

const std::array<QString, 26> LETTER_TO_MORSE = {
    ". ---",         // A
    "--- . . .",     // B
    "--- . ---- .",  // C
    "--- . .",       // D
    ".",             // E
    ". . --- .",     // F
    "--- --- .",     // G
    ". . . .",       // H
    ". .",           // I
    ". --- --- ---", // J
    "--- . ---",     // K
    ". --- . .",     // L
    "--- ---",       // M
    "--- .",         // N
    "--- --- ---",   // O
    ". --- --- .",   // P
    "--- --- . ---", // Q
    ". --- .",       // R
    ". . .",         // S
    "---",           // T
    ". . ---",       // U
    ". . . ---",     // V
    ". --- ---",     // W
    "--- . . ---",   // X
    "--- . --- ---", // Y
    "--- --- . .",   // Z
};

const std::array<QString, 10> DIGIT_TO_MORSE = {
    ". --- --- --- ---",   // 0
    ". .  --- --- ---",    // 1
    ". . .  --- ---",      // 2
    ". . . .  ---",        // 3
    ". . . . .",           // 4
    "--- . . . .",         // 5
    "--- --- . . .",       // 6
    "--- --- --- . .",     // 7
    "---- --- --- --- .",  // 8
    "--- --- --- --- ---", // 9
};

const QHash<QString, QChar> MORSE_TO_LETTER = {
    {". ---", 'A'},              //
    {"--- . . .", 'B'},          //
    {"--- . ---- .", 'C'},       //
    {"--- . .", 'D'},            //
    {".", 'E'},                  //
    {". . --- .", 'F'},          //
    {"--- --- .", 'G'},          //
    {". . . .", 'H'},            //
    {". .", 'I'},                //
    {". --- --- ---", 'J'},      //
    {"--- . ---", 'K'},          //
    {". --- . .", 'L'},          //
    {"--- ---", 'M'},            //
    {"--- .", 'N'},              //
    {"--- --- ---", 'O'},        //
    {". --- --- .", 'P'},        //
    {"--- --- . ---", 'Q'},      //
    {". --- .", 'R'},            //
    {". . .", 'S'},              //
    {"---", 'T'},                //
    {". . ---", 'U'},            //
    {". . . ---", 'V'},          //
    {". --- ---", 'W'},          //
    {"--- . . ---", 'X'},        //
    {"--- . --- ---", 'Y'},      //
    {"--- --- . .", 'Z'},        //
    {". --- --- --- ---", '0'},  //
    {". .  --- --- ---", '1'},   //
    {". . .  --- ---", '2'},     //
    {". . . .  ---", '3'},       //
    {". . . . .", '4'},          //
    {"--- . . . .", '5'},        //
    {"--- --- . . .", '6'},      //
    {"--- --- --- . .", '7'},    //
    {"---- --- --- --- .", '8'}, //
    {"--- --- --- --- ---", '9'},
};

constexpr auto MORSE_WORD_SEPARATOR = "       ";
constexpr auto MORSE_LETTER_SEPARATOR = "   ";

///////////////////////////////////////////////////////////////////////

constexpr inline bool is_number(const char c) { return c >= '0' && c <= '9'; }
constexpr inline bool is_character(const char c) {
  return c >= 'a' && c <= 'z';
}
constexpr inline bool is_whitespace(const char c) {
  return c == ' ' || c == '\n' || c == '\t';
}

QString filter_valid_characters(const QString &text) {
  QString output;

  for (const auto qc : text.trimmed()) {
    const char letter = qc.toLower().toLatin1();

    // Skip extra spaces between words
    if (!output.isEmpty() && is_whitespace(output.back().toLatin1()) &&
        is_whitespace(letter))
      continue;

    // Add only numbers and letters
    if (is_number(letter) || is_character(letter))
      output.append(letter);
    else if (is_whitespace(letter))
      output.append(' ');
  }

  return output;
}

namespace morse {

QString english_to_morse(const QString &text) {
  QStringList translated_words;

  // Strip invalid characters and split by words
  for (const auto &word : filter_valid_characters(text).split(' ')) {
    QStringList translated_letters;

    // Convert one character at a time
    for (const auto letter : word) {
      const char c = letter.toLower().toLatin1();
      QString translated_letter;

      if (is_number(c)) {
        translated_letter = DIGIT_TO_MORSE[c - '0'];
      } else if (is_character(c)) {
        translated_letter = LETTER_TO_MORSE[c - 'a'];
      }

      translated_letters.push_back(translated_letter);
    }

    const auto translated_word =
        translated_letters.join(MORSE_LETTER_SEPARATOR);
    translated_words.push_back(translated_word);
  }

  return translated_words.join(MORSE_WORD_SEPARATOR);
}

QString morse_to_english(const QString &text) {
  QStringList translated_words;

  // Go through all words and try to convert every letter into english
  for (const auto &word : text.trimmed().split(MORSE_WORD_SEPARATOR)) {
    QString word_translated;

    for (auto letter : word.split(MORSE_LETTER_SEPARATOR)) {
      auto it = MORSE_TO_LETTER.find(letter);
      if (it != MORSE_TO_LETTER.end())
        word_translated.append(it.value());
    }

    if (!word_translated.isEmpty())
      translated_words.push_back(word_translated);
  }

  return translated_words.join(' ');
}

} // namespace morse
