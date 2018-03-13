import QtQuick 2.0
import QtLocation 5.9


MapPolyline {
    line.width: 6;
    line.color: "#bdc3c7";
    opacity: 0.7;
    smooth: true;
    path: []
    property int distance;
    property var original_color: "#bdc3c7";
    MouseArea {
        anchors.fill:parent;
        onClicked: {
            map.setItemsInactive();
            pathInfo.visible = true;
            pathInfo.label = "Mission Path";
            pathInfo.distance = distance;
            parent.line.color = map.activeItemColor;
        }
    }
}
