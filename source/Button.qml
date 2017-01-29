import QtQuick 2.0

Item {
    id: button
    //  key caption strings top,bottom or middle
    property string txt: ""
    //  font scale factor
    property real sc: 12.0

    //  position
    property int xx: 0
    property int yy: 0
    //  dimension
    property int w: 40
    property int h: 40

    //  pressed, highlight
    property bool on: false

    Rectangle {
               color: on ? Qt.rgba(0.3, 0.45, 0.6, 1) : Qt.rgba(0.1, 0.2, 0.3, 1)
        border.color: on ? Qt.rgba(0.8, 0.92, 1.0, 1) : Qt.rgba(0.2, 0.4, 0.6, 1)
        radius: 5
        border.width: 1
        antialiasing: true

        x: xx
        y: yy
        width:  w
        height: h

        Text {
            color: on ? Qt.rgba(0.9, 0.96, 1.0, 1) : Qt.rgba(0.7, 0.85, 1.0, 1)
            text: txt

            font.family: "Tahoma"
            font.pixelSize: sc

            //anchors.centerIn: parent
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.margins: 5
        }
    }
}
