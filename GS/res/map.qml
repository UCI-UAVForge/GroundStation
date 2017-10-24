import QtQuick 2.0
import QtQuick.Window 2.0
import QtLocation 5.6
import QtPositioning 5.6

Item {
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
        center: QtPositioning.coordinate(59.91, 10.75) // Oslo
        zoomLevel: 14
      //  signal qmlSignal(string v)
        MapQuickItem {
            id:marker
            sourceItem: Image{
                id: image
                source: "Map-Marker.png"

            }
            coordinate: map.center
            anchorPoint.x: image.width / 2
            anchorPoint.y: image.height / 2
        }

        MouseArea {
            anchors.fill: parent
            onPressed: {
                console.log('clicked')
            }
        }
    }

}
