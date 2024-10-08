import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    id: root
    title: "Login"
    width: 400
    height: 300
    visible: true

    background: Rectangle {
        color: "#f0f0f0"
        radius: 10
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 15

        // Title section
        Text {
            id: title
            text: qsTr("Login")
            font.pixelSize: 28
            font.bold: true
            color: "#333"
            horizontalAlignment: Text.AlignHCenter
            Layout.alignment: Qt.AlignHCenter
        }

        // Username section
        RowLayout {
            Layout.fillWidth: true
            spacing: 10

            Text {
                id: usernameLabel
                text: qsTr("Username:")
                font.pixelSize: 16
                color: "#333"
                Layout.alignment: Qt.AlignLeft
                Layout.fillWidth: true
            }

            TextField {
                id: usernameInput
                Layout.fillWidth: true
                font.pixelSize: 16
                placeholderText: "Enter username"

                // Customization for TextField
                background: Rectangle {
                    color: "#fff"
                    radius: 10
                    border.color: "#ccc"
                    border.width: 1
                }
                padding: 10
            }
        }

        // Group ComboBox section
        RowLayout {
            Layout.fillWidth: true
            spacing: 10

            Text {
                id: groupLabel
                text: qsTr("Group:")
                font.pixelSize: 16
                color: "#333"
                Layout.fillWidth: true
            }

            ComboBox {
                id: groupCombo
                Layout.fillWidth: true
                model: groupModel
                font.pixelSize: 16
                textRole: "key"
                valueRole: "value"
                // Customization for ComboBox
                background: Rectangle {
                    color: "#fff"
                    radius: 10
                    border.color: "#ccc"
                    border.width: 1
                }
                padding: 10

                ListModel {
                    id: groupModel
                    ListElement {
                        value: 1
                        key: "Work"
                    }
                    ListElement {
                        value: 2
                        key: "Student"
                    }
                    ListElement {
                        value: 3
                        key: "C++ class"
                    }
                }
            }
        }

        // Login button
        Button {
            id: btnLogin
            text: "Chat Now"
            font.pixelSize: 16
            background: Rectangle {
                color: "#4CAF50"
                radius: 10
            }
            padding: 10

            Layout.alignment: Qt.AlignHCenter
            onClicked: {
                var profiles = {
                    "hoanglinh": 1,
                    "thanhnguyen": 2,
                    "phucnguyen": 3
                }

                var component = Qt.createComponent("ChatApp.qml")
                var window = component.createObject()
                window.m_username = usernameInput.text
                if (profiles[window.m_username] !== undefined) {
                    window.m_userId = profiles[window.m_username]
                }
                window.m_groupId = groupCombo.currentValue
                window.m_groupName = groupCombo.currentText
                window.show()
                root.close()
            }
        }
    }
}
