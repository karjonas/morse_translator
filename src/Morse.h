#pragma once

#include <QString>

namespace morse {

QString english_to_morse(const QString &text);
QString morse_to_english(const QString &text);

} // namespace morse
