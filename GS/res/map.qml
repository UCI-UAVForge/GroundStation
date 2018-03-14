import QtQuick 2.4
import QtQuick.Window 2.0
import QtPositioning 5.6
import QtQuick.Controls 1.2 //QtQuick Components
import QtQuick.Dialogs 1.1 //Dialogs
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0
import QtLocation 5.9

Rectangle {
    id: main
    width:512
    height:512
    visible: true
    objectName:"rect"
    property bool centerUAV

    Plugin {
        id: mapPlugin
        name: "esri"
    }

    Map {
        id: map
        objectName:"map"
        anchors.fill: parent
        antialiasing: true
        plugin: mapPlugin
        center: QtPositioning.coordinate(33.771175, -117.695560) //the place 38.14792, -76.427995            //(33.6405, -117.8443) // Irvine
        zoomLevel: 14
        Component.onCompleted: {
                    for( var i_type in supportedMapTypes ) {
                        if(supportedMapTypes[i_type].name.localeCompare( "World Imagery" ) === 0 ) {
                            activeMapType = supportedMapTypes[i_type]
                        }
                    }
                }

        property var activeItemColor: "white";
        property var waypoints : [];
        property bool armState : false;

        Component {
            id:wp;
            Waypoint {}
        }
        MouseArea {
            anchors.fill:parent;
            onClicked: {
                map.setItemsInactive();
            }
        }
            MapPolyline {
                id: uavPath;
                objectName: "uavPath";
                line.width: 4;
                line.color: "red";
                smooth: true;
                path: []
                property var original_color: "red";
                MouseArea {
                    anchors.fill:parent;
                    onClicked: {
                        itemInfo.label = "UAV Path";
                        itemInfo.visible = true;
                        map.setItemsInactive();
                        parent.line.color = map.activeItemColor;
                    }
                }
            }

       MissionPath {
           id: missionPath
           objectName: "missionPath"
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
                    }
                }
            }
        }

        Component {
            id: mapLine
            MapPolyline {
                objectName: "polyline";
                line.width: 6
                property string label;
                property var original_color;
                antialiasing: true;
                smooth: true;
                opacity:0.7;
                path: [];
                MouseArea {
                    anchors.fill:parent;
                    onClicked: {
                        itemInfo.label = label;
                        itemInfo.visible = true;
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
                        //areaInfo.visible = false;
                        waypointInfo.label = label;
                        waypointInfo.visible = true;
                        map.setItemsInactive();
                        parent.border.width = 2;
                        parent.border.color = map.activeItemColor;
                    }
                }
                antialiasing: true
            }
        }

        function drawPoint(point, label, color, radius) {
            var waypt = wp.createObject(map,
                        {"r": radius, "pt_color": color, "objectName": label,
                         "label":label, "coordinate": QtPositioning.coordinate(point.x, point.y)});
            waypoints.push(waypt);
            map.addMapItem(waypt);
        }

        function destroyWaypoints() {
            while (waypoints.length > 0) {
                waypoints.pop().destroy();
            }
        }

        function drawPolyline(points, color) {
            var line = mapLine.createObject(map, {"original_color": color,"label": "Mission Path", "line.color": color})
            for (var i = 0; i < points.length; i++){
                 line.addCoordinate(QtPositioning.coordinate(points[i].x, points[i].y));
                 missionPath.addCoordinate(QtPositioning.coordinate(points[i].x, points[i].y));
            }
            map.addMapItem(missionPath);
            //map.addMapItem(line);
        }

        function drawPolygon(points, color, label) {
            var polygon = mapPolygon.createObject(map, {"color": color, "label":label})
            for (var i = 0; i < points.length; i++){
                 polygon.addCoordinate(QtPositioning.coordinate(points[i].x, points[i].y));
            }
            map.addMapItem(polygon);
        }

        function setItemsInactive() {
            waypointInfo.visible = false;
            pathInfo.visible = false;
            for (var i=0; i < waypoints.length; i++) {
               waypoints[i].sourceItem.border.width = 0;
            }

            for (var i=0;i<map.mapItems.length;i++) {
                var item = map.mapItems[i];
                var name = item.objectName;
                if (name === 'polygon')
                    item.border.width = 0;
                if (name === 'polyline' || name === 'uavPath' || name === 'missionPath') {
                    item.line.color = item.original_color;
                }
            }
        }

        function updateArmState(state) {
            armState = state;
            if (armState) {
                map.addMapItem(uavPath);
            }
        }

        function updateCenter(lat, lon) {
            if (centerUAV) {
                map.center = QtPositioning.coordinate(lat, lon);
            }
        }

        function drawUAV(lat, lon, heading) {
            map.removeMapItem(uav);
            uavInfo.visible = true;
            uav.coordinate = QtPositioning.coordinate(lat, lon);
            uav.rotation = heading;
            if (armState) {
                uavPath.addCoordinate(uav.coordinate);
            }
            map.addMapItem(uav);
        }

        function removeUAV() {
            map.removeMapItem(uav)
            uavInfo.visible = false;
        }

        function clearMap() {
            destroyWaypoints();
            clearPath(missionPath);
            map.clearMapItems();
        }

        function incUAVsize() {
            uav.uavsize += 5;
        }
        function decUAVsize() {
            uav.uavsize -= 5;
        }

        function clearPath(path) {
            while (path.pathLength() > 0) {
                path.removeCoordinate(0);
            }
        }

        function clearMissionPath() {
            clearPath(missionPath);
            destroyWaypoints();
        }
    }

    PlaneSettings {
        map: map
    }

    UAV {
        id:uav;
    }

    UAVInfo {
        id:uavInfo;
        visible: false;
        label: "UAV Position"
        function toggleCenter(lat, lon) {
            centerUAV = centerUAV ? false:true;
            uavInfo.color = centerUAV ? "#AA116611" : Qt.rgba(0, 0, 0, 0.55);
        }
        TooltipArea {
            text: "Toggle focus on UAV"
            onClicked: {uavInfo.toggleCenter()}
        }
    }

    WaypointInfo {
        id:waypointInfo;
        visible: false;
        TooltipArea {
            text: "Click to center at waypoint"
            onClicked: {map.center = waypointInfo.coord;}
        }
    }

    PathInfo {
        id: pathInfo;
        visible: false;
    }

    Rectangle {
        id: clearMapButton;
        width: 80;
        height:30;
        radius: 5;
        Text {
            anchors.centerIn: parent;
            text: "Clear Map";
            color:"white";
            font.bold: true;
        }
        color: Qt.rgba(0,0,0,0.55);
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.margins: 15;
        TooltipArea {
            text: "Clear map of all objects."
            onClicked: {
                map.clearMap();
                map.clearPath(uavPath);
                map.clearPath(missionPath);
            }
        }
    }
}

