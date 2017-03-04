//Prad Tantiwuttipong 11/4/16
//Updated 2/26/17

var map = new L.Map('map', {center: new L.LatLng(33.6454,-117.8426), zoom: 13});
var drawControl;
var paths = new L.FeatureGroup();   //Contains all paths
map.addLayer(paths);
var markers = new L.LayerGroup();   //Contains all markers
var activePath;                     //Active path
var tableSelectionPath;             //Path selected on table
var uavPath;                        //Current UAV Path
var newPath;                        //Path sent through cbridge
var newPathPoints= [];                  //Points of newPath

//Variables to create leaflet map. Using OSM tiles.
function initializeMap() {
    var osmUrl = 'http://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png',
        osmAttrib = '&copy; <a href="http://openstreetmap.org/copyright">OpenStreetMap</a> contributors',
        osm = L.tileLayer(osmUrl, {maxZoom: 20, attribution: osmAttrib});

    osm.addTo(map);

    //Drawing tool options
    drawControl = new L.Control.Draw(
                {position:'topright',
                    edit: {featureGroup: paths,
                        allowIntersection: true
                    },
                    draw: { polygon : false,
                        marker: false,
                        circle: false,
                        rectangle: false,
                        polyline: {
                            shapeOptions: {
                                color: 'blue'
                            }
                        }
                    }
                });

    map.addControl(drawControl);
}


//Changes activePath display properties
function showActivePath() {
    paths.eachLayer(function(path) {
        path.setStyle({color:'blue'});
    });
    activePath.setStyle({color:'red'});
}

//Updates table with points from activePath. Table always shows the active path.
function updateTable() {
    var activePathPoints = activePath.getLatLngs();
    cbridge.clearTable();
    for(var i = 0, len = activePathPoints.length; i < len; i++) {
        cbridge.pointAddedToMap(activePathPoints[i].lat, activePathPoints[i].lng, 0, 0);
    }
}
//Adds a listener to check for actions on any path.
function addPathListener(path) {
    path.on('click', function(){
        activePath = path;
        showActivePath();
        updateTable();
    });
}


map.on('draw:created', function(event){
    var newPath = event.layer;
    paths.addLayer(newPath).addTo(map);
    activePath = newPath;
    addPathListener(newPath);
    showActivePath();
    updateTable();
});

map.on('draw:editstop', function(event){
    updateTable();
});

map.on('draw:deleted', function(event){
    var deletedPaths = event.layers;
    deletedPaths.eachLayer(function(deletedPath) {
        if (deletedPath === activePath) {
            cbridge.clearTable();
        }
    });
});

map.on('draw:deletestart', function(event) {
   removePath(tableSelectionPath);
   markers.clearLayers();
});

map.on('draw:editstart', function(event){
    removePath(tableSelectionPath);
    markers.clearLayers();
});

function appendPointToPath(lat, lng, id) {
    newPathPoints.push([lat, lng]);
}

function createNewPath(id) {
    newPath = L.polyline(newPathPoints);
    paths.addLayer(newPath).addTo(map);
    newPathPoints = [];
}

function clearAllPaths() {
    paths.clearLayers();
}

function removePath(path){
    if (paths.hasLayer(path)){
        paths.removeLayer(path);
    }
}
function removeMarker(marker) {
    if (markers.hasLayer(marker)){
        markers.removeLayer(marker);
    }
}


function addPath(source) {
    removePath(tableSelectionPath);
    markers.clearLayers();
    if (newPathPoints.length != 0) {
        if (source === "tableSelection"){
            addTableSelectionPath();
        }
        else if(source === "table") {

        }
        else if(source === "planning") {
            addPlanningPath();
        }
        else if(source === "execution") {
            addUAVPath();
        }
    }
}

function addPlanningPath() {
    var planningPath = L.polyline(newPathPoints, {color:'blue', opacity:0.6});
    paths.addLayer(planningPath).addTo(map);
    newPathPoints = [];
}

function addTableSelectionPath() {
    tableSelectionPath = L.polyline(newPathPoints, {color:'yellow'});
    markers.addLayer(L.marker(newPathPoints[0])).addTo(map);
    markers.addLayer(L.marker(newPathPoints[newPathPoints.length-1])).addTo(map);
    paths.addLayer(tableSelectionPath).addTo(map);
    newPathPoints = [];
}

function addUAVPath() {
    removePath(uavPath);
    //document.getElementById("ok").innerHTML = newPathPoints
    uavPath = L.polyline(newPathPoints, {color:'orange'});
    paths.addLayer(uavPath).addTo(map);
    newPathPoints = [];
}

function disableEditing(){
    map.removeControl(drawControl);
    paths.clearLayers();
    activePath.setStyle({color:'green', opacity:0.5});
    paths.addLayer(activePath).addTo(map);
}



//function addSelectedPath(lat, lng) {
//    flightPlanLine = L.polyline(flightPlan, {opacity:0.6});
//    drawnItems.addLayer(flightPlanLine).addTo(map);
//    map.removeControl(drawControl);
//    map.fitBounds(flightPlanLine.getBounds(), {padding:[50, 50]});
//}

///////execution
//var flightPlan = [];
////Actual flight path of the UAV, Constructed from data Recieved from UAV/test machine
//var flightPlanLine;
//var i = 0;
//// Current position of the UAV
//var uavPos;
//// Array containing path of UAV
//var uavPath = [];
//// Polyline used to draw UAV path on map
//var uavPathLine;
//// Layer containing uavPos, uavPath, and uavPathLine
//var positionLayer = new L.FeatureGroup().addTo(map);

////Adds flight plan to array
//function addFlightPlan(lat,lng,mapID){
//    flightPlan.push([lat, lng]);
//}

////Plots the planned route that the UAV should follow
//function plotFlightPlan() {
//    flightPlanLine = L.polyline(flightPlan, {opacity:0.6});
//    drawnItems.addLayer(flightPlanLine).addTo(map);
//    map.removeControl(drawControl);
//    map.fitBounds(flightPlanLine.getBounds(), {padding:[50, 50]});
//}

////Plots actual position and route of the UAV
//function plotUAVPosition(lat, lng) {
//    positionLayer.clearLayers();
//    uavPath.push([lat, lng]);
//    if (uavPath.length > 1) {
//        uavPathLine = L.polyline(uavPath, {color: 'red', opacity: 0.9}).addTo(map);
//    }
//    uavPos = new L.Marker([lat, lng]).addTo(map);
//    positionLayer.addLayer(uavPos);
//    positionLayer.addLayer(uavPathLine);
//    map.redraw();
//}

//// Adds draw controls back when moving from flight execution to flight planning
//function addDrawControl() {
//    map.addControl(drawControl);
//}



