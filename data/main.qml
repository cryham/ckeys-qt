import QtQuick 2.0
import QtQuick.Controls 1.2
//import QtQuick 2.6
//import QtQuick.Controls 2.2

import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Private 1.0
import QSquircle 1.0

Item {

    width: 1200
    height: 600

    Squircle {
        objectName: "base"
        SequentialAnimation on t {
            NumberAnimation { to: 1; duration: 2500; easing.type: Easing.InQuad }
            NumberAnimation { to: 0; duration: 2500; easing.type: Easing.OutQuad }
            loops: Animation.Infinite
            running: true
        }
    }

    /*GridLayout {
        id: gridLayout

        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.rightMargin: 12
        anchors.leftMargin: 12
        anchors.topMargin: 12
        columnSpacing: 8
        rowSpacing: 8
        rows: 2
        columns: 7
        enabled: false
    }/**/

    RowLayout {
        anchors.topMargin: 20
        anchors.leftMargin: 20
        //anchors.right: parent.right
        //anchors.rightMargin: 12
        //anchors.top: gridLayout.bottom
        //anchors.fill: parent

        Label {
            id: label1
            //color: white
            text: qsTr("Title")
            //Layout.columnSpan: 2
        }

        /*Item {
            id: spacer10
            Layout.preferredHeight: 14
            Layout.preferredWidth: 14
        }*/

        /*ComboBox {
            id: title
            Layout.columnSpan: 2
            Layout.fillWidth: true
            model: ["Paris", "Oslo", "London"]

            style: ComboBoxStyle {
            background: Rectangle {
            implicitWidth: 200
            implicitHeight: 25
            color: "#1F2F3F"
            border.width: 1
            border.color: !control.enabled ? "#DADAD9" : control.activeFocus ? "#3C3C3B" : "#9D9C9C"
            antialiasing: true
            Rectangle {
                id: glyph
                width: 10
                height: 10
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 10
                color: !control.enabled ? "#DADAD9" : control.hovered ? "#1D5086" : "#5791CD"
                states: State {
                    name: "inverted"
                    when: __popup.__popupVisible
                    PropertyChanges { target: glyph; rotation: 180 }
                }
            }
          } }
        }/**/

        ComboBox {
            id: box
            currentIndex: 2
            activeFocusOnPress: true
            style: ComboBoxStyle {
                id: comboBox
                background: Rectangle {
                    id: rectCategory
                    //radius: 5
                    border.width: 1
                    color: "#235"
                }
                label: Text {
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.pointSize: 10
                    font.family: "Tahoma"
                    //font.capitalization: Font.SmallCaps
                    color: "#ACE"
                    text: control.currentText
                }

                // drop-down customization here
                property Component __dropDownStyle: MenuStyle {
                    __maxPopupHeight: 400
                    __menuItemType: "comboboxitem"

                    frame: Rectangle {              // background
                        color: "#369"
                        border.width: 2
                        //radius: 5
                    }

                    itemDelegate.label:             // an item text
                        Text {
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        font.pointSize: 10
                        font.family: "Tahoma"
                        color: styleData.selected ? "#DEF" : "#ACE"
                        text: styleData.text
                    }

                    itemDelegate.background: Rectangle {  // selection of an item
                        radius: 2
                        color: styleData.selected ? "#57A" : "transparent"
                    }

                    __scrollerStyle: ScrollViewStyle { }
                }

                property Component __popupStyle: Style {
                    property int __maxPopupHeight: 400
                    property int submenuOverlap: 0

                    property Component frame: Rectangle {
                        width: (parent ? parent.contentWidth : 0)
                        height: (parent ? parent.contentHeight : 0) + 2
                        border.color: "#48C"
                        property real maxHeight: 500
                        property int margin: 1
                    }

                    property Component menuItemPanel: Text {
                        text: "NOT IMPLEMENTED"
                        color: "red"
                        font {
                            pixelSize: 14
                            bold: true
                        }
                    }

                    property Component __scrollerStyle: null
                }
            }

            model: model1
            /* ListModel {
                id: cbItems
                ListElement { text: "Banana" }
                ListElement { text: "Apple" }
                ListElement { text: "Coconut" }
            }*/
            width: 200
        }

        /*TextField {
            id: firstName
            textColor: "#ACE"
            Layout.minimumWidth: 140
            Layout.fillWidth: true
            Layout.columnSpan: 3
            placeholderText: qsTr("name")
        }*/

        /*TextArea {
            id: textArea
            x: 8
            y: 8
            width: 300
            //height: 40
            //Layout.fillHeight: true
            //Layout.fillWidth: true
        }*/

        CheckBox {
            id: controlC
            text: qsTr("CheckBox")
            checked: true
            width: 150
        }
        /*RadioButton {
            id: controlR
            text: qsTr("Radio")
            checked: true
        }/**/

        Slider {
            id: sld1
            value: 0.4
            width: 150
            style: sliderStyle
        }

        RowLayout {
            Layout.alignment: Qt.AlignTop | Qt.AlignRight
            Button {
                id: save1
                text: qsTr("Save")
                style: buttonStyle
            }
            Button {
                id: cancel1
                text: qsTr("Cancel")
                style: buttonStyle
            }
        }
    }


    MessageDialog {
        id: aboutDialog
        icon: StandardIcon.Information
        title: qsTr("About")
        text: "Qt Quick UI Forms"
        informativeText: qsTr("This example demonstrates how to separate the implementation of an application from the UI using ui.qml files.")
    }

    MenuBar {
        Menu {
            title: qsTr("&File")
            MenuItem {
                text: qsTr("E&xit")
                //shortcut: StandardKey.Quit
                onTriggered: Qt.quit()
            }
        }
        Menu {
            title: qsTr("&Help")
            MenuItem {
                text: qsTr("About...")
                onTriggered: aboutDialog.open()
            }
        }
    }

/*
    Button {  xx: 100; yy: 100;  w: 1.0; h: 0.8;  txt: "Esc";  }
    Button {  xx: 100; yy: 140;  w: 2.5; h: 1.0;  txt: "Shift"; on:true;  }
    Button {  xx: 100; yy: 190;  w: 2.0; h: 1.0;  txt: "Enter";  }
*/

    /*Text {
        id: label
        color: "black"
        wrapMode: Text.WordWrap
        text: "The label and its border is rendered using QML"
        font.family: "Tahoma"
        font.pixelSize: 21
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.margins: 20
    }/**/


    Component {
        id: buttonStyle
        ButtonStyle {
            //font.pointSize: 10
            //font.family: "Tahoma"

            background: Rectangle {
                //implicitHeight: 22
                //implicitWidth: window.width / columnFactor
                color: control.pressed ? "#5070B0" : control.activeFocus ? "#50A0C0" : "#406090"
                antialiasing: true
                border.color: "#406080"
                //radius: height/2
                Rectangle {
                    anchors.fill: parent
                    anchors.margins: 1
                    color: "transparent"
                    antialiasing: true
                    visible: !control.pressed
                    border.color: "#aaffffff"
                    //radius: height/2
                }
            }
        }
    }

    Component {
        id: sliderStyle
        SliderStyle {
            handle: Rectangle {
                width: 18
                height: 18
                color: control.pressed ? "#def" : "#cde"
                border.color: "#abc"
                antialiasing: true
                radius: height/2
                Rectangle {
                    anchors.fill: parent
                    anchors.margins: 1
                    color: "transparent"
                    antialiasing: true
                    border.color: "#9ab"
                    //radius: height/2
                }
            }
            groove: Rectangle {
                height: 8
                //implicitWidth: window.width / columnFactor
                implicitHeight: 22

                antialiasing: true
                color: "#345"
                border.color: "#234"
                //radius: height/2
                Rectangle {
                    anchors.fill: parent
                    anchors.margins: 1
                    color: "transparent"
                    antialiasing: true
                    border.color: "#66445566"
                    //radius: height/2
                }
            }
        }
    }


}
