import QtQuick 2.0
import QtQuick.Controls 1.0

ApplicationWindow
{
    visible: true
    width: 640
    height: 480
    title: qsTr("Morse Translator")
    id: app
    property alias morseText: morseField.text
    property alias englishText: englishField.text

    Column {
        id: column
        spacing: 2

        Row {
            id: row
            spacing: 2

            TextArea  {
                id: englishField
                objectName: "englishField"
                wrapMode: TextInput.WordWrap
                width: app.width/2 - row.spacing/2
                height: app.height - column.spacing
                onTextChanged: backend.text_english = text
            }

            TextArea {
                id: morseField
                objectName: "morseField"
                wrapMode: TextInput.WordWrap
                width: app.width/2 - row.spacing/2
                height: app.height - column.spacing
                onTextChanged: backend.text_morse = text
            }
        }
    }
}
