#include <QGuiApplication>
#include <QMetaObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlProperty>

#include <iostream>

#include "Morse.h"

enum class Language { English, Morse };

class Backend : public QObject {
  Q_OBJECT
  Q_PROPERTY(QString text_english READ get_text_english WRITE set_text_english)
  Q_PROPERTY(QString text_morse READ get_text_morse WRITE set_text_morse)

public:
  QString get_text_english() const { return m_text_english; }
  QString get_text_morse() const { return m_text_morse; }

  void set_text_english(const QString &text) {
    update_text(text, Language::English);
  }
  void set_text_morse(const QString &text) {
    update_text(text, Language::Morse);
  }

signals:
  void text_updated(const QString &english, const QString &morse);

private:
  void update_text(const QString &new_text, Language language) {
    if (language == Language::English && new_text != m_text_english) {
      m_text_english = new_text;
      m_text_morse = morse::english_to_morse(m_text_english);
      text_updated(m_text_english, m_text_morse);
    } else if (language == Language::Morse && new_text != m_text_morse) {
      m_text_morse = new_text;
      m_text_english = morse::morse_to_english(m_text_morse);
      text_updated(m_text_english, m_text_morse);
    }
  }

  QString m_text_english;
  QString m_text_morse;
};

int main(int argc, char *argv[]) {
  QGuiApplication app(argc, argv);

  QCoreApplication::addLibraryPath("./");

  QQmlApplicationEngine engine;
  Backend backend;
  engine.rootContext()->setContextProperty("backend", &backend);
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;

  // Callback for setting text in qml
  QObject::connect(&backend, &Backend::text_updated,
                   [root = engine.rootObjects().first()](const QString &english,
                                                         const QString &morse) {
                     root->setProperty("englishText", QVariant(english));
                     root->setProperty("morseText", QVariant(morse));
                   });

  backend.set_text_english(
      "Type anything in this window to translate it into morse code. Only "
      "letters and numbers will be translated. To translate from morse to "
      "english type in the right side window. The morse code needs to adhere "
      "to the specification below. \n"
      "\n"
      "International Morse Code:\n"
      "\n"
      "1. The length of a dot is one unit.\n"
      "2. A dash is three units.\n"
      "3. The space between parts of the same letter is one unit.\n"
      "4. The space between letters is three units.\n"
      "5. The space between words is seven units.\n"
      "\n"
      "The right window is showing this text translated to morse code.");

  return app.exec();
}

#include "main.moc"
