import QtQuick 2.0
import QtLocation 5.9

MapQuickItem {
        id: waypoint
        objectName: "point"
        property string label;
        property int r;
        property string pt_color;
        sourceItem:
            Rectangle {
                width: r; height: r; color: pt_color; border.width: 0;
                border.color: "white"; smooth: true; radius: r/2
                Text {
                    text:label
                    anchors.centerIn: parent
                    font.bold: true
                    color:"white";
                }
                MouseArea {
                    anchors.fill:parent;
                    onClicked: {
                        var coord = waypoint.coordinate.toString().split(",");
                        var nextCoord = missionPath.coordinateAt(parseInt(label));
                        waypointInfo.label = "Waypoint #" + label;
                        waypointInfo.coord = waypoint.coordinate;
                        waypointInfo.lat = coord[0];
                        waypointInfo.lon = coord[1];
                        waypointInfo.heading = waypoint.coordinate.azimuthTo(nextCoord);
                        map.setItemsInactive();
                        waypointInfo.visible = true;
                        parent.border.width = 2;
                        parent.border.color = map.activeItemColor;
                    }
                }
            }
        opacity: 1.0
        anchorPoint: Qt.point(sourceItem.width/2, sourceItem.height/2)

}
