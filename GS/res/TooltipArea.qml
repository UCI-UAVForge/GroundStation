import QtQuick 2.2
import QtQuick.Controls.Private 1.0

// TooltipArea.qml
// This file contains private Qt Quick modules that might change in future versions of Qt
// Tested on: Qt 5.4.1

MouseArea {
    id: _root
    property string text: ""
    property bool hovered

    anchors.fill: parent
    hoverEnabled: _root.enabled
    onExited: Tooltip.hideText()
    onCanceled: Tooltip.hideText()
    //onHoveredChanged: hovered ? _root.opacity = 0 : _root.opacity = .2;
    Timer {
        interval: 700
        running: _root.enabled && _root.containsMouse && _root.text.length
        onTriggered: Tooltip.showText(_root, Qt.point(_root.mouseX, _root.mouseY), _root.text)
    }
}
