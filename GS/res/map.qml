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
    Plugin {
        id: mapPlugin
        name: "esri"
    }

    Map {
        id: map
        objectName:"map"
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(38.14792, -76.427995) //the place            //(33.6405, -117.8443) // Irvine
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
            plane.rotation = 90 - heading
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
                                width:25;height:25;
                                fillMode:Image.PreserveAspectFit
                                source: "images/Plane.png"}
        }

        function addMarker(id,img,lat,lon,x,y,type){
            test = Qt.createQmlObject("
                                    import QtQuick 2.0;
                                    import QtLocation 5.6;
                                    import QtPositioning 5.6;
                                    MapQuickItem{id:marker" + id + ";
                                                property int someNumber: " + type + ";
                                                anchorPoint.x: image.width" + x + ";
                                                anchorPoint.y: image.height" + y + ";
                                                sourceItem: Image{id:image;
                                                            width:30;height:30;
                                                            fillMode:Image.PreserveAspectFit;
                                                            source: \""+img+".png\"}
                                    coordinate: QtPositioning.coordinate(" + lat + "," + lon + ")}", map)

            map.addMapItem(test)
        }

        function addLine(id, width, color, pathlat, pathlon, size, type){
            text = "
                    import QtQuick 2.0;
                    import QtLocation 5.6;

                    MapPolyline{id:image" + id + ";
                                property int someNumber: "+type+";
                                line.width: " + width + ";
                                line.color: '" + color + "'
                                path: ["

            for (var i=0; i<size; ++i){
                if (i!=0)
                    text += ","
                text += "{ latitude: " + pathlat[i] + ", longitude:" + pathlon[i] + "}"
            }

            text += "]}"

            test2 = Qt.createQmlObject(text, map)
            map.addMapItem(test2)
        }

        function remove(type){

        }

    }
}

