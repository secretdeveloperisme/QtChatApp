import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    visible: true
    width: 450
    height: 600
    title: qsTr("Chat App")
    property int userId
    property string username: "unknown"
    property int groupId
    property string groupName: "unknown"

    Rectangle {
        border.width: 1
        border.color: "black"
        anchors.fill: parent
        width: parent.width
        ColumnLayout {
            anchors.fill: parent
            width: parent.width
            anchors.margins: 20
            Column {
                width: parent.width - 20
                Text {
                    id: title
                    text: "Chat App"
                    font.pixelSize: 24
                    horizontalAlignment: Text.AlignHCenter
                    anchors.left: parent.left
                    Layout.alignment: Qt.AlignHCenter
                    height: 50
                }
                Rectangle {
                    width: parent.width
                    height: 50
                    Text {
                        id: userName
                        text: "User: " + username
                        font.pixelSize: 18
                        anchors.left: parent.left
                    }
                    Text {
                        id: groupdId
                        text: "Group: " + groupName
                        font.pixelSize: 18
                        anchors.right: parent.right
                        anchors.rightMargin: 20
                    }
                }
            }

            ListView {
                id: chatListView
                width: parent.width
                Layout.fillHeight: true
                clip: true

                model: chatModel
                delegate: Item {
                    width: chatListView.width
                    height: 80

                    Row {
                        width: parent.width
                        spacing: 10

                        Rectangle {
                            id: incomingAvatar
                            visible: messageType == "incoming"
                            width: 40
                            height: 40
                            radius: 20
                            color: "lightgray"
                            Text {
                                anchors.centerIn: parent
                                text: initials
                                font.pixelSize: 16
                            }
                        }

                        Rectangle {
                            width: parent.width - 40 - 10
                            height: 40
                            color: messageType == "incoming" ? "lightblue" : "lightgreen"
                            radius: 10
                            border.color: "gray"
                            Text {
                                anchors.fill: parent
                                text: messageText
                                padding: 10
                                wrapMode: Text.WordWrap
                            }
                        }

                        Rectangle {
                            id: outgoingAvatar
                            visible: messageType == "outgoing"
                            width: 40
                            height: 40
                            radius: 20
                            color: "lightgray"
                            Text {
                                anchors.centerIn: parent
                                text: "ME"
                                font.pixelSize: 16
                                color: "gray"
                            }
                        }
                    }
                }
                function addItem(text, messageType, username) {

                    chatModel.append({
                                         "messageText": text,
                                         "messageType": messageType,
                                         "initials": username.charAt(
                                                         0).toUpperCase()
                                     })
                    chatListView.positionViewAtEnd()
                }

                Component.onCompleted: {
                    chatListView.positionViewAtEnd()
                }
            }

            Row {
                height: 25
                width: parent.width - 20
                TextField {
                    id: inputField
                    width: parent.width * 0.8
                    height: parent.height
                    font.pixelSize: 16
                    placeholderText: "Input a message"
                    background: Item {
                        anchors.fill: parent
                        Rectangle {
                            anchors.fill: parent
                            color: "lightblue"
                        }
                    }
                }

                Button {
                    text: "Send"
                    width: parent.width * 0.2
                    height: parent.height

                    onClicked: {
                        if (inputField.text !== "") {
                            if (chatClient.sendMessage(userId, username,
                                                       groupId, groupName,
                                                       inputField.text)) {
                                chatListView.addItem(inputField.text,
                                                     "outgoing", "")
                                inputField.text = ""
                            }
                        }
                    }
                }
            }
        }
    }
    Connections {
        target: chatClient
        function onReceivedMessage(ownerId, ownerName, groupId, groupName, content) {
            chatListView.addItem(content, "incoming", ownerName)
        }
    }

    ListModel {
        id: chatModel
    }
}
