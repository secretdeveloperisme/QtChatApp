import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    visible: true
    width: 400
    height: 600
    title: qsTr("Server Control")

    Column {
        anchors.fill: parent
        spacing: 20

        Text {
            text: "Server Control"
            font.pixelSize: 24
            horizontalAlignment: Text.AlignHCenter
            Layout.alignment: Qt.AlignHCenter
        }

        Row {
            Button {
                text: "Start Server"
                Layout.alignment: Qt.AlignLeft
                onClicked: {
                    server.startServer()
                }
            }

            Button {
                text: "Stop Server"
                Layout.alignment: Qt.AlignLeft
                onClicked: {
                    server.stopServer()
                }
            }
        }

        Text {
            text: "Server Logs:"
            font.pixelSize: 16
        }

        ListView {
            id: logListView
            width: parent.width
            height: 400
            model: logModel
            delegate: Item {
                width: logListView.width
                height: 30
                Rectangle {
                    width: parent.width
                    height: 30
                    color: "lightgray"
                    Text {
                        anchors.centerIn: parent
                        text: logText
                    }
                }
            }
        }
    }
    Connections {
        target: server
        function onLogMessage(message) {
            logModel.append({
                                "logText": message
                            })
        }
    }

    ListModel {
        id: logModel
    }
}
