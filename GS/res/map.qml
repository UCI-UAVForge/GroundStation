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
        zoomLevel: 18
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
        property var prevSelection;
        property var prevWaypoint;

        MouseArea {
            anchors.fill:parent;
            onClicked: {
                map.setItemsInactive();
            }
        }

       UAVPath {
           id: uavPath;
       }

       MissionPath {
           id: missionPath
           objectName: "missionPath"
       }

       Component {
           id: wp
           Waypoint {}
       }

        Component {
            id:pt
            Point{}
        }

        Component {
            id: polygon
            Polygon{}
        }

        Component {
            id: mapLine
            Path {}
        }

        function addMissionPath(points) {
            clearMissionPath();
//            clearMap();
            for (var i = 0; i < points.length; i++){
                 missionPath.addCoordinate(QtPositioning.coordinate(points[i].x, points[i].y));
            }
            map.addMapItem(missionPath);
        }

        function addWaypoint(point, wpNum, color, radius) {
            var waypt = wp.createObject(map,
                        {"r": radius, "pt_color": color, "objectName": wpNum,
                         "label":parseInt(wpNum)+1, "coordinate": QtPositioning.coordinate(point.x, point.y)});
          //  missionPath.addCoordinate(QtPositioning.coordinate(points.x, points.y));
            waypoints.push(waypt);
            map.addMapItem(waypt);
           // waypt.setActive();
        }
        function setActive(wpNum){
            var waypoint = waypoints[wpNum];
            waypoint.setActive();
            /*
            var coord = waypoint.coordinate.toString().split(",");
            var nextCoord = missionPath.coordinateAt(parseInt(objectName)+1);
            waypointInfo.label = "Waypoint #" + label;
            waypointInfo.coord = waypoint.coordinate;
            waypointInfo.lat = coord[0];
            waypointInfo.lon = coord[1];
            waypointInfo.heading = waypoint.coordinate.azimuthTo(nextCoord);
            map.setItemsInactive();
            map.prevWaypoint = waypoint;
            waypointInfo.visible = true;
            pt.border.width = 2;
            pt.border.color = map.activeItemColor;
            console.log("set Active",waypoint, "coord",waypoint.coordinate);
            */
        }


        function destroyWaypoints() {
            while (waypoints.length > 0) {
                waypoints.pop().destroy();
            }
        }

        function drawPoint(coords, label, color, radius) {
            var point = pt.createObject(map,
                        {"r": radius, "pt_color": color,
                         "label":label, "coordinate": QtPositioning.coordinate(coords.x, coords.y)});
            map.addMapItem(point);
        }

        function drawPolyline(points, color) {
            var line = mapLine.createObject(map, {"original_color": color,"label": "Mission Path", "line.color": color})
            for (var i = 0; i < points.length; i++){
                 line.addCoordinate(QtPositioning.coordinate(points[i].x, points[i].y));
            }
            map.addMapItem(line);
        }

        function drawPolygon(points, color, label) {
            var polyg = polygon.createObject(map, {"color": color, "label":label})
        //    map.addMapItem(polyg);
//            var polygon = mapPolygon.createObject(map, {"color": color, "label":label})
            for (var i = 0; i < points.length; i++){
                polyg.addCoordinate(QtPositioning.coordinate(points[i].x, points[i].y));
            }
           map.addMapItem(polyg);
        }

        function setItemsInactive(d) {
            waypointInfo.visible = false;
            pathInfo.visible = false;
            pointInfo.visible = false;
            if (prevSelection != null) {
                var name = prevSelection.objectName;
                if (name === 'point')
                    prevSelection.sourceItem.border.width = 0;
                if (name === 'polygon')
                    prevSelection.border.width = 0;
                if (name === 'polyline' || name === 'uavPath' || name === 'missionPath') {
                    prevSelection.line.color = prevSelection.original_color;
                }
            }
            if (prevWaypoint != null) {
                prevWaypoint.sourceItem.border.width = 0;
            }
        }

        function changeEditMode(editing) {
            edit.visible = editing;
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

    ItemInfo {
        id: edit;
        color: "orange"
        width: 80; height: 27;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.top: parent.top;
        visible: false;
        label: "Edit Mode"
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

    PointInfo {
        id:pointInfo;
        visible: false;
        TooltipArea {
            text: "Click to center at point"
            onClicked: {map.center = pointInfo.coord;}
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

    ItemInfo {
        id: clearMapButton;
        width: 80; height:30;
        anchors.bottom: parent.bottom; anchors.left: parent.left;
        label: "Clear Map";
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

