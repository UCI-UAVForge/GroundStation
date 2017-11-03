import QtQuick 2.0
import QtQuick.Window 2.0
import QtLocation 5.6
import QtPositioning 5.6
import "js/Test.js" as Test

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

//        MouseArea {
//            anchors.fill: parent
//            onPressed: {
//                console.log("mouse clicked")
//                Test.meow()
//            }
//        }


        function addMarker(img,lat,lon){
            test = Qt.createQmlObject("
import QtQuick 2.0;
import QtLocation 5.6;
import QtPositioning 5.6;
MapQuickItem{id:marker;
sourceItem: Image{id:image;
                width:30;height:30;
                fillMode:Image.PreserveAspectFit;
                source: \""+img+".png\"}
coordinate: QtPositioning.coordinate(" + lat + "," + lon + ")}", map)

            map.addMapItem(test)
        }

    }


}

