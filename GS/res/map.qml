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
        name: "esri" // "mapboxgl", "esri", ...
        // specify plugi parameters if necessary
        // PluginParameter {
        //     name:
        //     value:
        // }
      //  PluginParameter {name:"here.app_id"; value: "hFarTBZF6AzJvLKzd55C"}
       // PluginParameter {name: "here.token"; value: "h_jMLCAluu0BmDSWXExNyw"}
      //  PluginParameter {name: "here.mapping.highdpi_tiles"; value:"true"}
       // PluginParameter { name:"googlemaps.maps.apikey"; value: "AIzaSyAjYKn9mABOOi_NRjaJjsx5JhOU8IjLmJQ"}
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
        Component.onCompleted: {
                    for( var i_type in supportedMapTypes ) {
                        console.log(supportedMapTypes[i_type].name);
                        if(supportedMapTypes[i_type].name.localeCompare( "World Imagery" ) === 0 ) {
                            activeMapType = supportedMapTypes[i_type]
                        }
                    }
                }
        property MapQuickItem test
        property MapPolyline test2
        property var text

//        MouseArea {
//            anchors.fill: parent
//            onPressed: {
//                console.log("mouse clicked")
//            }
//        }


        function addMarker(id,img,lat,lon,x,y){
            test = Qt.createQmlObject("
                                    import QtQuick 2.0;
                                    import QtLocation 5.6;
                                    import QtPositioning 5.6;
                                    MapQuickItem{id:marker" + id + ";
                                                anchorPoint.x: image.width" + x + ";
                                                anchorPoint.y: image.height" + y + ";
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

