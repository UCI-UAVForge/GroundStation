import QtQuick 2.0

ItemInfo {
    width: 155; height: 80;
    anchors.right: parent.right;
    anchors.top: parent.top;
    Item {
        anchors.fill: parent;
        Column {
            anchors.bottom: parent.bottom;
            anchors.horizontalCenter: parent.horizontalCenter;
            anchors.bottomMargin: 10;
            Text { text: '<b>Lat:</b> ' +  uav.coordinate.toString().split(",")[0]; color: "white";}
            Text { text: '<b>Lon:</b> ' +  uav.coordinate.toString().split(",")[1]; color: "white";}
            Text { text: '<b>Heading:</b> ' + headingToCompass(uav.rotation); color: "white";}
        }
    }
}
