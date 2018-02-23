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
                        if(supportedMapTypes[i_type].name.localeCompare( "World Imagery" ) === 0 ) {
                            activeMapType = supportedMapTypes[i_type]
                        }
                    }
                }

        property var activeItemColor: "white";

        MouseArea {
            anchors.fill:parent;
            onClicked: {
                map.setItemsInactive();
                itemLabelRect.visible = false;
            }
        }

        MapPolyline {
            id: uavPath;
            objectName: "polyline";
            line.width: 4;
            line.color: "red";
            path: []
            property var original_color: "red";
            MouseArea {
                anchors.fill:parent;
                onClicked: {
                    itemLabel.text = "UAV Path";
                    itemLabelRect.visible = true;
                    map.setItemsInactive();
                    parent.line.color = map.activeItemColor;
                }
            }

        }

        Component {
            id: mapMarker
            MapCircle {
                objectName: "marker"
                border.width: 0
                antialiasing: true
                MouseArea {
                    anchors.fill:parent;
                    onClicked: {
                        map.setItemsInactive();
                        //parent.border.width = 2;
                        //parent.border.color = map.activeItemColor;
                    }
                }
            }
        }

        Component {
            id: mapLine
            MapPolyline {
                objectName: "polyline";
                line.width: 3
                property string label;
                property var original_color;
                MouseArea {
                    anchors.fill:parent;
                    onClicked: {
                        itemLabel.text = label;
                        itemLabelRect.visible = true;
                        map.setItemsInactive();
                        parent.line.color = map.activeItemColor;
                    }
                }
            }
        }

        Component {
            id: mapPolygon
            MapPolygon {
                objectName: "polygon"
                border.width: 0
                property string label;
                MouseArea {
                    anchors.fill:parent;
                    onClicked: {
                        itemLabel.text = label;
                        itemLabelRect.visible = true;
                        map.setItemsInactive();
                        parent.border.width = 2;
                        parent.border.color = map.activeItemColor;
                    }
                }
                antialiasing: true
            }
        }

        Component {
            id: pointLabel;
            MapQuickItem {
                id: item;
                property string label;
                sourceItem: Text{
                    text: label;
                    color:"#242424"
                    font.bold: true
                    styleColor: "#ECECEC"
                    style: Text.Outline
                    antialiasing: true
                }
                antialiasing: true
                anchorPoint: Qt.point(sourceItem.width/2, sourceItem.height/2)
            }
        }

        function drawPoint(point, label, color, radius) {
            var p = mapMarker.createObject(map,
                         {"center.latitude": point.x,
                          "center.longitude" : point.y,
                          "color" : color,
                          "radius" : radius})
            map.addMapItem(p);
            var pl = pointLabel.createObject(map,
                         {"label": label,
                          "coordinate": QtPositioning.coordinate(point.x, point.y)})
            map.addMapItem(pl);
        }

        function drawPolyline(points, color) {
            var line = mapLine.createObject(map, {"original_color": color,"label": "Mission Path", "line.color": color})
            for (var i = 0; i < points.length; i++){
                 line.addCoordinate(QtPositioning.coordinate(points[i].x, points[i].y));
            }
            map.addMapItem(line);
        }

        function drawPolygon(points, color, label) {
            var polygon = mapPolygon.createObject(map, {"color": color, "label":label})
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

        function setItemsInactive() {
            for (var i=0;i<map.mapItems.length;i++) {
                if (map.mapItems[i].objectName === 'polygon')
                    map.mapItems[i].border.width = 0;
                if (map.mapItems[i].objectName === 'polyline') {
                    map.mapItems[i].line.color = map.mapItems[i].original_color;
                }
            }
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
            uavPath.addCoordinate(plane.coordinate);
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
        }
    }

    PlaneSettings {
        map: map
    }

    Rectangle{
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
            centerUAV = centerUAV ? false:true;
            mapinfo.color = centerUAV ? "#AA116611" : Qt.rgba(0, 0, 0, 0.55);
        }
        TooltipArea {
            text: "Toggle focus on UAV"
            onClicked: {mapinfo.toggleCenter()}
        }
    }

    Rectangle {
        id: itemLabelRect;
        width: 100;
        height:30;
        visible: false;
        radius: 5;
        Text {
            anchors.centerIn: parent;
            id:itemLabel;
            color:"white";
            font.bold: true;
        }
        color: Qt.rgba(0,0,0,0.55);
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.bottom: parent.bottom;
        anchors.margins: 15;

    }

}

