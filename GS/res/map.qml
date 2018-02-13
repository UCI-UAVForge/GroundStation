import QtQuick 2.2
import QtQuick.Window 2.0
import QtLocation 5.6
import QtPositioning 5.6
import QtQuick.Controls 1.2 //QtQuick Components
import QtQuick.Dialogs 1.1 //Dialogs
import "../res"


Rectangle {
    id: main
    width:512
    height:512
    visible: true
    objectName:"rect"
    property alias coords: uavPosition.text
    property bool centerUAV

    Plugin {
        id: mapPlugin
        name: "esri"
    }

    Map {
        id: map
        objectName:"map"
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(38.14792, -76.427995) //the place 38.14792, -76.427995            //(33.6405, -117.8443) // Irvine
        zoomLevel: 14
        Component.onCompleted: {
                    for( var i_type in supportedMapTypes ) {
                     //   console.log(supportedMapTypes[i_type].name);
                        if(supportedMapTypes[i_type].name.localeCompare( "World Imagery" ) === 0 ) {
                            activeMapType = supportedMapTypes[i_type]
                        }
                    }
                }
        property MapQuickItem test
        property MapCircle newPoint
        property MapPolyline test2
        property var text

        Component {
            id: mapMarker
            MapCircle {
                radius: 25
                border.width: 0
            }
        }

        Component {
            id: mapLine
            MapPolyline {
                line.width: 3
            }
        }

        Component {
            id: mapPolygon
            MapPolygon {
            border.width: 0
            }
        }

        function drawPoint(point, color) {
             var p = mapMarker.createObject(map,
                         {"center.latitude": point.x,
                          "center.longitude" : point.y,
                          "color" : color})
             map.addMapItem(p);
        }

        function drawPolyline(points, color) {
            var line = mapLine.createObject(map, {"line.color": color})
            for (var i = 0; i < points.length; i++){
                 line.addCoordinate(QtPositioning.coordinate(points[i].x, points[i].y));
            }
            map.addMapItem(line);
        }

        function drawPolygon(points, color) {
            var polygon = mapPolygon.createObject(map, {"color": color})
            for (var i = 0; i < points.length; i++){
                 polygon.addCoordinate(QtPositioning.coordinate(points[i].x, points[i].y));
            }
            map.addMapItem(polygon);
        }
        function changeMapInfoColor(color) {
            for (var i=0;i<map.mapItems.length;i++)
                if (map.mapItems[i].objectName === 'mapinfo')
                    map.mapItems[i].uavsize -= 5;
        }


        function updateCenter(lat, lon) {
            if (centerUAV) {
                map.center = QtPositioning.coordinate(lat, lon);
            }
        }

        function drawUAV(lat, lon, heading) {
            map.removeMapItem(plane);
            plane.coordinate = QtPositioning.coordinate(lat, lon)
            plane.rotation = heading
            map.addMapItem(plane)
        }

        function removeUAV() {
            map.removeMapItem(plane)
            uavHeading.text = ""
            uavPosition.text = "No Data Received"
        }

        function clearMap() {
            map.clearMapItems();
        }

        function incUAVsize() {
            plane.uavsize += 5;
        }
        function decUAVsize() {
            plane.uavsize -= 5;
        }


        MapQuickItem{id:plane;
                    objectName: 'plane'
                    property int uavsize: 50
                    anchorPoint.x: image.width/2;
                    anchorPoint.y: image.height/2;
                    sourceItem: Image {id:image;
                                width:plane.uavsize;height:plane.uavsize;
                                fillMode:Image.PreserveAspectFit
                                source: "images/Plane.png"}
                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true
                        onEntered: {
                            console.log("Mouse over plane");
                        }
                    }
        }


    }
    Rectangle {
        id: mapinfo
        objectName: "mapInfo"
        Text {
            text: "UAV POSITION"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            color: "white"
            font.bold: true
            anchors.margins:5
        }

        Text {
            id: uavPosition
            objectName: "uavPosition"
            text: "No Data Received"
            color: "white"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.centerIn: parent
            anchors.margins: 5
            function updateUAVPosition(coords) {
                uavPosition.text = coords;
            }
        }

        Text {
            id: uavHeading
            objectName: "uavHeading"
            text: ""
            color: "white"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.margins: 5
            function updateUAVHeading(heading) {
                uavHeading.text = heading;
            }
        }

        color: Qt.rgba(0, 0, 0, 0.55)
        width: 200; height: 63;
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.margins: 15
        radius: 5
        function toggleCenter(lat, lon) {
            if(centerUAV) {
                centerUAV = false;
                mapinfo.color = Qt.rgba(0, 0, 0, 0.55);
            } else {
                centerUAV = true;
                mapinfo.color = "#AA116611"
            }
        }
        TooltipArea {
            text: "Toggle focus on UAV"
            onClicked: {mapinfo.toggleCenter()}
        }

    }


    Rectangle {
        id: planesettings
        Rectangle {
            id: increaseUAVSize
            Text {
                text: "+"
                font.pointSize: 16
                font.bold: true
                color: "white"
                anchors.centerIn: parent
            }
            TooltipArea {
                text: "Increase UAV size"
                onClicked: {map.incUAVsize()}
            }
            anchors.top:parent.top
            width: 35; height: 30
            color: "transparent"
        }
        Rectangle {
            id: decreaseUAVSize
            Text {
                text: "-"
                font.pointSize: 23
                font.bold: true
                color: "white"
                anchors.centerIn: parent
            }
            TooltipArea {
                text: "Decrease UAV size"
                onClicked: { map.decUAVsize()}
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
}

