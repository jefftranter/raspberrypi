import QtQuick 2.0

Rectangle {
    id: button
    property alias text: textLabel.text
    signal clicked();

    border.width: 1
    border.color: "black"
    radius: 4
    width: textLabel.width + 4
    height: textLabel.height + 4
    Text {
      id: textLabel
      anchors.verticalCenter: parent.verticalCenter
      anchors.horizontalCenter: parent.horizontalCenter
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            button.clicked();
        }
    }
}
