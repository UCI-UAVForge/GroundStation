import QtQuick 2.0
import QtLocation 5.9

MapQuickItem{id:plane;
            objectName: 'plane'
            property int uavsize: 50
            anchorPoint.x: image.width/2;
            anchorPoint.y: image.height/2;
            antialiasing: true;
            sourceItem: Image {id:image;
                        width:plane.uavsize;height:plane.uavsize;
                        fillMode:Image.PreserveAspectFit
                        source: "images/Plane.png"}
}
