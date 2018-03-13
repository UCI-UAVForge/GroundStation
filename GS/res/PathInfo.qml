import QtQuick 2.0

ItemInfo {
    width: 155; height: 45;
    anchors.horizontalCenter: parent.horizontalCenter;
    anchors.bottom: parent.bottom;
    property string distance;
    Item {
        anchors.fill: parent;
        Column {
            anchors.bottom: parent.bottom;
            anchors.horizontalCenter: parent.horizontalCenter;
            anchors.bottomMargin: 8;
            Text { text: '<b>Distance:</b> ' + distance; color: "white";}
        }
    }
}


