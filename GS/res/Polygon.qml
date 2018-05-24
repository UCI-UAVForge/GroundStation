import QtQuick 2.7
import QtLocation 5.9
import QtPositioning 5.8

MapPolygon {
        id:polyg;
        objectName: "polygon"
        border.width: 0;
        MouseArea {
            anchors.fill:parent;
            onClicked: {
                map.setItemsInactive();
                map.prevSelection = polyg;
                parent.border.width = 2;
                parent.border.color = map.activeItemColor;
            }
        }

}
