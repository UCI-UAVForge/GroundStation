import QtQuick 2.7

Rectangle {
    radius: 5;
    color: Qt.rgba(0,0,0,0.55);
    anchors.margins: 15;
    property string label;
    Text {
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.top: parent.top;
        anchors.margins: 5
        text: label;
        color: "white";
        font.bold: true;
    }
    function headingToCompass(heading) {
        var compass = heading + "° ";
        if ((heading<360 && heading>348.75) || (heading>=0 && heading<=11.25))
            return compass + "N";
        if (heading>11.25 && heading<=33.75)
            return compass + "NNE";
        if (heading>33.75 && heading<=56.25)
            return compass + "NE";
        if (heading>56.25 && heading<=78.75)
            return compass + "ENE";
        if (heading>78.75 && heading<=101.25)
            return compass + "E";
        if (heading>101.25 && heading<=123.75)
            return compass + "ESE";
        if (heading>123.75 && heading<=146.25)
            return compass + "SE";
        if (heading>146.25 && heading<=168.75)
            return compass + "SSE";
        if (heading>168.75 && heading<=191.25)
            return compass + "S";
        if (heading>191.25 && heading<=213.75)
            return compass + "SSW";
        if (heading>213.75 && heading<=236.25)
            return compass + "SW";
        if (heading>236.25 && heading<=258.75)
            return compass + "WSW";
        if (heading>258.75 && heading<=281.25)
            return compass + "W";
        if (heading>281.25 && heading<=303.75)
            return compass + "WNW";
        if (heading>303.75 && heading<=326.25)
            return compass + "NW";
        if (heading>326.25 && heading<=348.75)
            return compass + "NNW";
        return "MapWidget::headingToCompass - Greater than 359";
    }
}
