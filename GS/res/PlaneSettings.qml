import QtQuick 2.4
import QtQuick.Window 2.0
//import QtLocation 5.6
import QtPositioning 5.6
import QtQuick.Controls 1.2 //QtQuick Components
import QtQuick.Dialogs 1.1 //Dialogs
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0
import QtLocation 5.6


Rectangle {
    id: planesettings
    property var map;
    Rectangle {
        id: increaseUAVSize
        Text {
            id:incTxt
            text: "+"
            font.pointSize: 16
            font.bold: true
            color: "white"
            anchors.centerIn: parent
        }
        TooltipArea {
            text: "Increase UAV size"
            onClicked: {map.incUAVsize()}
            onEntered: incTxt.color = "#b8fcbf"
            onExited: incTxt.color = "white"
        }
        anchors.top:parent.top
        width: 35; height: 30
        color: "transparent"
    }
    Rectangle {
        id: decreaseUAVSize
        Text {
            id:decTxt
            text: "-"
            font.pointSize: 23
            font.bold: true
            color: "white"
            anchors.centerIn: parent
        }
        TooltipArea {
            text: "Decrease UAV size"
            onClicked: {map.decUAVsize()}
            onEntered: decTxt.color = "#fcbfb8"
            onExited: decTxt.color = "white"
        }
        anchors.bottom:parent.bottom
        color: "transparent"
        width: 35; height: 30
    }
    width: 35; height: 60
    anchors.bottom: parent.bottom
    anchors.right: parent.right
    anchors.margins: 15
    color: Qt.rgba(0, 0, 0, 0.55)
    radius: 5
}
