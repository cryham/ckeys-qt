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
        anchors.top: parent.top
        anchors.left: parent.left
        //anchors.margins: 10
        anchors.topMargin: 8
        anchors.leftMargin: 12
        spacing: 12

        Label {
            id: label1
            //color: white

            text: qsTr("Title")
            width: 100

            font.family: "Tahoma"
            font.pixelSize: 16
        }

        /*Item {
            id: spacer10
            Layout.preferredHeight: 14
            Layout.preferredWidth: 14
        }*/


        ComboBox {
            //id: box
            //currentIndex: 2
            activeFocusOnPress: true

            style: comboStyle

            ListModel {
               id: list
               objectName:"list"
                    }

            id: typeComboBox

            model: comboModel.comboList

            /*menu: ContextMenu {
                MenuItem { text: "Option A"}
                MenuItem { text: "Option B"}
            }*/

            //model: model1
            /* ListModel {
                id: cbItems
                ListElement { text: "Banana" }
                ListElement { text: "Apple" }
                ListElement { text: "Coconut" }
            }*/
            width: 160
        }


        /*TextField {  //editbox
            id: firstName
            textColor: "#ACE"
            Layout.minimumWidth: 140
            Layout.fillWidth: true
            Layout.columnSpan: 3
            placeholderText: qsTr("name")
        }/**/

        /*TextArea {
            id: textArea
            width: 200
            height: 40
            //Layout.fillHeight: true
            //Layout.fillWidth: true
        }/**/


        CheckBox {
            id: controlC
            text: qsTr("Check")
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


            Button {
                id: save1
                text: qsTr("Save")
                style: buttonStyle
            //onClicked:
            }
            Button {
                id: cancel1
                text: qsTr("Cancel")
                style: buttonStyle
        }
    }


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

            label: Text {
                id: text
                text: control.text
                color: control.pressed ? "#77A" : "#CCF"
                font.pixelSize: 16 //control.height * 0.25
                font.family: "Tahoma" //openSans.name

                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.fill: parent
                //anchors.margins: 10
            }
            background: Rectangle {

                anchors.margins: 10

                gradient: Gradient {
                    GradientStop {
                        color: control.pressed ? "#224" : "#335"
                        position: 0
                    }
                    GradientStop {
                        color: "#224"
                        position: 1
                    }
                }
                Rectangle {
                    height: 1
                    width: parent.width
                    anchors.top: parent.top
                    color: "#446"
                    visible: !control.pressed
                }
                Rectangle {
                    height: 1
                    width: parent.width
                    anchors.bottom: parent.bottom
                    color: "#112"
                }
            }
            /*background: Rectangle {
                implicitHeight: 32
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
            }*/
        }
    }

    Component {
        id: sliderStyle
        SliderStyle {
            handle: Rectangle {
                width: 8
                height: 16
                color: control.pressed ? "#39f" : "#28e"
                border.color: "#16c"
                antialiasing: true
                radius: 2
                Rectangle {
                    anchors.fill: parent
                    anchors.margins: 1
                    color: "transparent"
                    antialiasing: true
                    border.color: "#39c"
                    //radius: height/2
                }
            }
            groove: Rectangle {
                height: 8
                //implicitWidth: window.width / columnFactor
                implicitHeight: 22

                antialiasing: true
                color: "#136"
                border.color: "#124"
                //radius: height/2
                Rectangle {
                    anchors.fill: parent
                    anchors.margins: 1
                    color: "transparent"
                    antialiasing: true
                    border.color: "#66224466"
                    //radius: height/2
                }
            }
        }
    }

    Component {
        id: comboStyle
            ComboBoxStyle {
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
      }
}
