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
var flightPath = [];
//Actual flight path of the UAV, Constructed from data Recieved from UAV/test machine
var flightPath_actual;
var i = 0;
var marker;

function plotPoint(lat, lng) {
    L.marker([lat, lng]).addTo(map);
    map.redraw();
}

function plotPointOnMap(lat,lng,mapID){
    flightPath.push([lat, lng]);
    document.getElementById("ok").innerHTML = flightPath.toString();
}

function plotPolyline() {
    flightPath_actual = L.polyline(flightPath);
    drawnItems.addLayer(flightPath_actual).addTo(map);
    map.removeControl(drawControl);
    map.fitBounds(flightPath_actual.getBounds(), {padding:[50, 50]});
}

function startFlight() {
    marker = L.Marker.movingMarker(flightPath, 20000).addTo(map);
    drawnItems.addLayer(marker);
    marker.start();
}

function addDrawControl() {
    map.addControl(drawControl);
}

function stopFlight() {
    marker.stop();
//    drawnItems.removeLayer(marker);
//    map.addControl(drawControl);
}

//In case a reload is necessary
var readyStateCheckInterval = setInterval(function() {
    if (document.readyState === "complete") {
        clearInterval(readyStateCheckInterval);
        cbridge.addNewMap();
    }
}, 10);

