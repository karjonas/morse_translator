#pragma once

#include <QString>

/* These methods will convert text between english and morse while skipping
 * non-translatable characters */
namespace morse {

QString english_to_morse(const QString &text);
QString morse_to_english(const QString &text);

} // namespace morse
