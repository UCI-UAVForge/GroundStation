import QtQuick 2.0
import QtQuick.Window 2.0
import QtLocation 5.6
import QtPositioning 5.6


Rectangle {
    id: main
    width:512
    height:512
    visible: true
    objectName:"rect"
    property alias coords: uavPosition.text
    Plugin {
        id: mapPlugin
        name: "esri"
    }

    Map {
        id: map
        objectName:"map"
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(33.6405, -117.8443) //the place 38.14792, -76.427995            //(33.6405, -117.8443) // Irvine
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

        function updateCenter(lat, lon) {
            map.center = QtPositioning.coordinate(lat, lon);
        }

        function drawUAV(lat, lon, heading) {
            map.removeMapItem(plane);
            plane.coordinate = QtPositioning.coordinate(lat, lon)
            plane.rotation = heading
            map.addMapItem(plane)
        }

        function removeUAV() {
            map.removeMapItem(plane)
        }

        function clearMap() {
            map.clearMapItems();
        }

        MapQuickItem{id:plane;
                    anchorPoint.x: image.width/4;
                    anchorPoint.y: image.height;
                    sourceItem: Image {id:image;
                                width:30;height:30;
                                fillMode:Image.PreserveAspectFit
                                source: "images/Plane.png"}
        }


    }
    Rectangle {
        id: mapinfo
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
        width: 220; height: 63;
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.margins: 15
        radius: 5
    }
}

