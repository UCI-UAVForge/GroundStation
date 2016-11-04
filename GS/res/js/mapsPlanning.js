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
            {edit: {featureGroup: drawnItems,
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
var allPoints;

function updateTable(layer) {
    var allPoints = layer.getLatLngs();
    cbridge.clearTable();
    for(var i=0, len = allPoints.length; i < len; i++) {
        cbridge.addPointToTable(allPoints[i].lat, allPoints[i].lng);
    }
}

function addClickListener(layer) {
    layer.on('click', function(){
        updateTable(layer);
        drawnItems.eachLayer(function(l){
            l.setStyle({color:'blue'});
        });
        layer.setStyle({color:'red'});
    });
}


map.on('draw:created', function(event) {
    var layer = event.layer;
    allPoints = layer.getLatLngs();
    drawnItems.addLayer(layer);
    addClickListener(layer);
    updateTable(layer);
});

map.on('draw:editstop', function(event){
    drawnItems.eachLayer(function(l){
        l.setStyle({color:'blue'});
    });
});



function clearMap() {
    //Called from the c++ side to refresh the map.
    //modified by Arash on 2/23/15: it will now clear the map without
    //changing the zoom level or center of the map
    drawnItems.clearLayers();
}

function addLatLngCoords(lat, lng) {
}
