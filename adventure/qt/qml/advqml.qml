import QtQuick 2.0

Column {

Row {

Column {

Text {
     text: "Commands:"
}

Grid {
    columns: 3
    spacing: 2

    Button {
        text: "Go"
        onClicked: {
        console.log("Go button clicked")
        }
    }
    Button { text: "Look" }
    Button { text: "Use"  }
    Button { text: "Examine" }
    Button { text: "Take" }
    Button { text: "Drop" }
    Button { text: "Inventory" }
    Button { text: "Help" }
    Button { text: "Quit" }
}

}

Column {

    Text {
        text: "Directions:"
    }

    Grid {
        columns: 2
        spacing: 2

        Button { text: "Up" }
        Button { text: "North" }
        Button { text: "West" }
        Button { text: "East" }
        Button { text: "Down" }
        Button { text: "South" }
    }
}

}

TextEdit {
    id: textEdit
    width: 100
    height: 100
    focus: true
    cursorVisible: true
    text: "Abandoned Farmhouse Adventure\nBy Jeff Tranter\n? "
    Component.onCompleted: textEdit.cursorPosition = textEdit.length
}

}
