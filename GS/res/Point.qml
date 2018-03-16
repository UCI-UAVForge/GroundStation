import QtQuick 2.7
import QtLocation 5.9
import QtPositioning 5.8

MapQuickItem {
        id:point;
        objectName: "point"
        property string label;
        property int r;
        property string pt_color;

        function setActive(){
            var coord = point.coordinate.toString().split(",");
            pointInfo.coord = point.coordinate;
            pointInfo.label = label;
            pointInfo.lat = coord[0];
            pointInfo.lon = coord[1];
            map.setItemsInactive();
            map.prevSelection = point;
            pointInfo.visible = true;
            pt.border.width = 2;
            pt.border.color = map.activeItemColor;
        }

        sourceItem:
            Rectangle { id:pt;
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
                        setActive();
                    }
                }
            }
        opacity: 1.0
        anchorPoint: Qt.point(sourceItem.width/2, sourceItem.height/2)
}
