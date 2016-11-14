//JavaScript code edited Jordan for UCI UAV Forge. Feb 18th 2015.
//Additional edits by Nathan. Feb 21st 2015.
var osmUrl = 'http://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png',
        osmAttrib = '&copy; <a href="http://openstreetmap.org/copyright">OpenStreetMap</a> contributors',
        osm = L.tileLayer(osmUrl, {maxZoom: 20, attribution: osmAttrib}),
        map = new L.Map('map', {center: new L.LatLng(33.6454,-117.8426), zoom: 13});

var drawnItems = new L.FeatureGroup().addTo(map);

osm.addTo(map);

var flightPath = [];
//Actual flight path of the UAV, Constructed from data Recieved from UAV/test machine
var flightPath_actual;

var i = 0;

function plotPointOnMap(lat,lng,mapID){
    flightPath.push([lat, lng]);
    document.getElementById("ok").innerHTML = flightPath.toString();
}

function plotPolyline() {
    flightPath_actual = L.polyline(flightPath).addTo(map);
    map.fitBounds(flightPath_actual.getBounds(), {padding:[50, 50]});
}

function startUAV() {
    var marker = L.Marker.movingMarker(flightPath, 20000).addTo(map);
    marker.start();
}

var readyStateCheckInterval = setInterval(function() {
    if (document.readyState === "complete") {
        clearInterval(readyStateCheckInterval);
        cbridge.addNewMap();
    }
}, 10);


function clearMap() {
    //Called from the c++ side to refresh the map.
    //modified by Arash on 2/23/15: it will now clear the map without
    //changing the zoom level or center of the map
    //modified by Jordan 5/22/15: no longer requires a reinitialize
}








