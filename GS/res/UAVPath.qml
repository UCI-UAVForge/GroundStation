import QtQuick 2.0
import QtLocation 5.9

MapPolyline {
    objectName: "uavPath";
    line.width: 4;
    line.color: "red";
    smooth: true;
    path: []
    property var original_color: "red";
    MouseArea {
        anchors.fill:parent;
        onClicked: {
            itemInfo.label = "UAV Path";
            itemInfo.visible = true;
            map.setItemsInactive();
            parent.line.color = map.activeItemColor;
        }
    }
}
