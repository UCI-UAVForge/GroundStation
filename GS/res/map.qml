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
        name: "osm" // "mapboxgl", "esri", ...
        // specify plugin parameters if necessary
        // PluginParameter {
        //     name:
        //     value:
        // }
    }
    signal qmlSignal(string wow);
    Map {
        id: map
        objectName:"map"
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(38.14792, -76.427995) //the place            //(33.6405, -117.8443) // Irvine
        zoomLevel: 14
      //  signal qmlSignal(string v)

        property MapQuickItem test
        property MapPolyline test2
        property var text

//        MouseArea {
//            anchors.fill: parent
//            onPressed: {
//                console.log("mouse clicked")
//            }
//        }


        function addMarker(id,img,lat,lon){
            test = Qt.createQmlObject("
                                    import QtQuick 2.0;
                                    import QtLocation 5.6;
                                    import QtPositioning 5.6;
                                    MapQuickItem{id:marker" + id + ";
                                    sourceItem: Image{id:image;
                                                width:30;height:30;
                                                fillMode:Image.PreserveAspectFit;
                                                source: \""+img+".png\"}
                                    coordinate: QtPositioning.coordinate(" + lat + "," + lon + ")}", map)

            map.addMapItem(test)
        }

        function addLine(id, width, color, pathlat, pathlon, size){
            text = "
                    import QtQuick 2.0;
                    import QtLocation 5.6;

                    MapPolyline{id:image" + id + ";
                                line.width: " + width + "
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

    }


}

