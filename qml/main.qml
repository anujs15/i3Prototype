import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Window {
    id: mainWindow
    visible: true
    width: 800
    height: 600
    title: qsTr("i3 Keyboard Interceptor")
    color: "black"

    property string keyHistory: ""

    Component.onCompleted: {
        i3Connector.connectToI3()
        keyboardInterceptor.startIntercepting()
    }

    onClosing: {
        keyboardInterceptor.stopIntercepting()
        i3Connector.disconnectFromI3()
    }

    Rectangle {
        anchors.fill: parent
        color: "#2d2d2d"

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 30
            spacing: 20

            Text {
                Layout.alignment: Qt.AlignHCenter
                text: "Keyboard ShortCuts"
                color: "white"
                font.pixelSize: 28
                font.bold: true
            }

            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 80
                color: "#1a1a1a"
                border.color: "#3498db"
                border.width: 2
                radius: 5

                Text {
                    anchors.centerIn: parent
                    text: keyboardInterceptor.currentKey
                    color: "#00ff00"
                    font.pixelSize: 36
                    font.bold: true
                }

                Text {
                    anchors {
                        top: parent.top
                        left: parent.left
                        margins: 5
                    }
                    text: "Press any Key:"
                    color: "#888888"
                    font.pixelSize: 16
                }
            }
        }
    }
}
