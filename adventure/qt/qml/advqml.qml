import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

ColumnLayout {

RowLayout {

ColumnLayout {

GroupBox {
    title: qsTr("Move Commands:")

GridLayout {
        columns: 2
        Button { text: qsTr("U&p"); }
        Button { text: qsTr("&North") }
        Button { text: qsTr("&West") }
        Button { text: qsTr("E&ast") }
        Button { text: qsTr("D&own"); }
        Button { text: qsTr("&South"); }
    }
}

GroupBox {
    title: qsTr("Global Commands:")

GridLayout {
        columns: 2
        Button { text: qsTr("&Look"); }
        Button { text: qsTr("&Inventory") }
        Button { text: qsTr("&Help") }
        Button { text: qsTr("&Quit") }
    }
}

}

ColumnLayout {

GroupBox {
    title: qsTr("Item Commands:")

    GridLayout {
        columns: 3
        Button { text: qsTr("&Take"); checkable: true; checked: true }
        Button { text: qsTr("&Drop"); checkable: true }
        Button { text: qsTr("&Use") ; checkable: true }
        Button { text: qsTr("&Examine"); checkable: true }
    }
}

GroupBox {
    title: qsTr("Inventory Items:")

    GridLayout {
        columns: 3
        Button { text: qsTr("flashlight") }
        Button { text: qsTr("-") }
        Button { text: qsTr("-") }
        Button { text: qsTr("-") }
        Button { text: qsTr("-") }
    }
}

GroupBox {
    title: qsTr("Local Items:")

    GridLayout {
        columns: 3
        Button { text: qsTr("key") }
        Button { text: qsTr("-") }
        Button { text: qsTr("-") }
        Button { text: qsTr("-") }
        Button { text: qsTr("-") }
        Button { text: qsTr("-") }
    }
}

}

}

GroupBox {
    title: qsTr("Status:")
    width: parent.width

TextEdit {
    width: parent.width
    text: "The Abandoned Farmhouse Adventure\nby Jeff Tranter <tranter@pobox.com>"
}

}

}
