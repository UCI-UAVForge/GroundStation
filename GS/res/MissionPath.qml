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
            map.prevSelection = parent;
            pathInfo.visible = true;
            pathInfo.label = "Mission Path";
            var distance = 0;
            for (var i = 1; i < parent.pathLength(); i++) {
                distance += parent.coordinateAt(i-1).distanceTo(parent.coordinateAt(i));
            }
            pathInfo.distance = distance;
            parent.line.color = map.activeItemColor;
        }
    }
}
