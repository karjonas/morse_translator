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

constexpr auto MORSE_WORD_SPACE = "       ";
constexpr auto MORSE_LETTER_SPACE = "   ";

///////////////////////////////////////////////////////////////////////

constexpr inline bool is_number(const char c) { return c >= '0' && c <= '9'; }
constexpr inline bool is_character(const char c) {
  return c >= 'a' && c <= 'z';
}
constexpr inline bool is_whitespace(const char c) { return c == ' '; }

QString filter_valid_characters(const QString &text_raw) {
  const QString text = text_raw.trimmed();
  QString output;
  output.reserve(text.size());

  const size_t num_chars = text.size();
  for (int letter_idx = 0; letter_idx < num_chars; letter_idx++) {
    const char letter = text.at(letter_idx).toLower().toLatin1();

    // Skip extra spaces between words
    if (letter_idx > 0 && is_whitespace(text.at(letter_idx - 1).toLatin1()) &&
        is_whitespace(letter))
      continue;

    // Add only numbers and letters
    if (is_number(letter) || is_character(letter) || is_whitespace(letter))
      output.append(letter);
  }

  return output;
}

namespace morse {

QString english_to_morse(const QString &text) {
  QString result;

  auto words = filter_valid_characters(text).split(' ');
  const size_t num_words = words.size();
  for (int word_idx = 0; word_idx < num_words; word_idx++) {
    const auto &word = words[word_idx];

    if (word.isEmpty())
      continue;

    const size_t num_chars = word.size();
    for (int letter_idx = 0; letter_idx < num_chars; letter_idx++) {
      const char c = word.at(letter_idx).toLower().toLatin1();

      if (is_number(c)) {
        result.append(DIGIT_TO_MORSE[c - '0']);
      } else if (is_character(c)) {
        result.append(LETTER_TO_MORSE[c - 'a']);
      }

      // Add space between letters
      if (letter_idx < (num_chars - 1))
        result.append(MORSE_LETTER_SPACE);
    }

    // Add space between words
    if (word_idx < (num_words - 1))
      result.append(MORSE_WORD_SPACE);
  }

  return result;
}

QString morse_to_english(const QString &text) {
  QString result;
  auto words = text.trimmed().split(MORSE_WORD_SPACE);

  const size_t num_words = words.size();

  for (int i = 0; i < num_words; i++) {
    const auto &word = words[i];
    auto letters = word.split(MORSE_LETTER_SPACE);

    for (auto letter : letters) {
      auto it = MORSE_TO_LETTER.find(letter);
      if (it != MORSE_TO_LETTER.end())
        result.append(it.value());
    }

    // Add space between words
    if (i < (num_words - 1))
      result.append(' ');
  }

  return result;
}

} // namespace morse
