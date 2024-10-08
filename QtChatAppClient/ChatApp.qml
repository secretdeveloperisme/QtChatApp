import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    id: root
    visible: true
    width: 450
    height: 600
    title: qsTr("Chat App")
    property int m_userId
    property string m_username: "unknown"
    property int m_groupId
    property string m_groupName: "unknown"

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
                        id: userNameLabel
                        text: "User: " + m_username
                        font.pixelSize: 18
                        anchors.left: parent.left
                    }
                    Text {
                        id: groupdId
                        text: "Group: " + m_groupName
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

                model: messageListModel
                delegate: Item {
                    width: chatListView.width
                    height: 80

                    Row {
                        width: parent.width
                        spacing: 10

                        Rectangle {
                            id: incomingAvatar
                            visible: ownerId != root.m_userId
                            width: 40
                            height: 40
                            radius: 20
                            color: "lightgray"
                            Text {
                                anchors.centerIn: parent
                                text: ownerName.charAt(0).toUpperCase()
                                font.pixelSize: 16
                            }
                        }

                        Rectangle {
                            width: parent.width - 40 - 10
                            height: 40
                            color: ownerId == root.m_userId ? "lightblue" : "lightgreen"
                            radius: 10
                            border.color: "gray"
                            Text {
                                anchors.fill: parent
                                text: content
                                padding: 10
                                wrapMode: Text.WordWrap
                            }
                        }

                        Rectangle {
                            id: outgoingAvatar
                            visible: ownerId == root.m_userId
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
                            if (chatClient.sendMessage(m_userId, m_username,
                                                       m_groupId, m_groupName,
                                                       inputField.text)) {
                                inputField.text = ""
                            }
                        }
                    }
                }
            }
        }
    }
}
