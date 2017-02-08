//Prad Tantiwuttipong 11/4/16

//Variables to create leaflet map. Using OSM tiles.
var osmUrl = 'http://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png',
        osmAttrib = '&copy; <a href="http://openstreetmap.org/copyright">OpenStreetMap</a> contributors',
        osm = L.tileLayer(osmUrl, {maxZoom: 20, attribution: osmAttrib}),
        map = new L.Map('map', {center: new L.LatLng(33.6454,-117.8426), zoom: 13});

var drawnItems = new L.FeatureGroup().addTo(map);

osm.addTo(map);

//Drawing tools options
var drawControl = new L.Control.Draw(
            {position:'topright',
                edit: {featureGroup: drawnItems,
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

//Fixes a bug where it draws double the points.
map.on('click');


var allPoints,
    selectedLayer;

//Changes color of line selected to red
function selectColor(layer) {
    drawnItems.eachLayer(function(l){
        l.setStyle({color:'blue'});
    });
    layer.setStyle({color:'red'});
}

//Adds selected points to the table when line is saved.
function updateTable(layer) {
    var allPoints = layer.getLatLngs();
    cbridge.clearTable();
    for(var i=0, len = allPoints.length; i < len; i++) {
        cbridge.addPointToTable(allPoints[i].lat, allPoints[i].lng);
    }
}


function addClickListener(layer) {
    layer.on('click', function(){
        allPoints = layer.getLatLngs();
        updateTable(layer);
        selectColor(layer);
        selectedLayer = layer;
        var startPopup = L.popup()
            .setLatLng(allPoints[0])
            .setContent("Start")
            .openOn(map);
    });
}

function onDraw(event) {
    var layer = event.layer;
    allPoints = layer.getLatLngs();
    selectColor(layer);
    selectedLayer = layer;
    drawnItems.addLayer(layer);
    addClickListener(layer);
    updateTable(layer);
}

map.on('draw:created', onDraw);

map.on('draw:editstop', function(event){
    updateTable(selectedLayer);
    selectColor(selectedLayer);
});

map.on('draw:deleted', function(event){
    var layers = event.layers;
    layers.eachLayer(function(layer) {
        if (layer === selectedLayer) {
            cbridge.clearTable();
        }
    });
});


function clearMap() {
    //Called from the c++ side to refresh the map.
    //pretty redundant button
    drawnItems.clearLayers();
}

function addLatLngCoords(lat, lng) {
}

/////execution
var flightPlan = [];
//Actual flight path of the UAV, Constructed from data Recieved from UAV/test machine
var flightPlanLine;
var i = 0;
// Current position of the UAV
var uavPos;
// Array containing path of UAV
var uavPath = [];
// Polyline used to draw UAV path on map
var uavPathLine;
// Layer containing uavPos, uavPath, and uavPathLine
var positionLayer = new L.FeatureGroup().addTo(map);

//Adds flight plan to array
function addFlightPlan(lat,lng,mapID){
    flightPlan.push([lat, lng]);
}

//Plots the planned route that the UAV should follow
function plotFlightPlan() {
    flightPlanLine = L.polyline(flightPlan, {opacity:0.6});
    drawnItems.addLayer(flightPlanLine).addTo(map);
    map.removeControl(drawControl);
    map.fitBounds(flightPlanLine.getBounds(), {padding:[50, 50]});
}

//Plots actual position and route of the UAV
function plotUAVPosition(lat, lng) {
    positionLayer.clearLayers();
    uavPath.push([lat, lng]);
    if (uavPath.length > 1) {
        uavPathLine = L.polyline(uavPath, {color: 'red', opacity: 0.9}).addTo(map);
    }
    uavPos = new L.Marker([lat, lng]).addTo(map);
    positionLayer.addLayer(uavPos);
    positionLayer.addLayer(uavPathLine);
    map.redraw();
}

// Adds draw controls back when moving from flight execution to flight planning
function addDrawControl() {
    map.addControl(drawControl);
}


//In case a reload is necessary
var readyStateCheckInterval = setInterval(function() {
    if (document.readyState === "complete") {
        clearInterval(readyStateCheckInterval);
        cbridge.addNewMap();
    }
}, 10);

