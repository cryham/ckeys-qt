import QtQuick 2.0
import OpenGLUnderQML 1.0

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
/*
    Button {  xx: 100; yy: 100;  w: 1.0; h: 0.8;  txt: "Esc";  }
    Button {  xx: 100; yy: 140;  w: 2.5; h: 1.0;  txt: "Shift"; on:true;  }
    Button {  xx: 100; yy: 190;  w: 2.0; h: 1.0;  txt: "Enter";  }
*/

}
