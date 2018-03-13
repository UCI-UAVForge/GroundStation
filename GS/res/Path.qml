import QtQuick 2.0
import QtLocation 5.9


MapPolyline {
    line.width: 6;
    line.color: "red";
    smooth: true;
    path: []
    property var original_color: "red";
    MouseArea {
        anchors.fill:parent;
        onClicked: {
            map.setItemsInactive();
            parent.line.color = map.activeItemColor;
        }
    }
}
