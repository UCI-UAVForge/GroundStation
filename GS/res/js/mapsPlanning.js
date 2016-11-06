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
    lastLayer;

//Changes color of line selected to red
function selectColor(layer) {
    drawnItems.eachLayer(function(l){
        l.setStyle({color:'blue'});
    });
    layer.setStyle({color:'red'});
}

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
        lastLayer = layer;
        var startPopup = L.popup()
            .setLatLng(allPoints[0])
            .setContent("Start")
            .openOn(map);
    });
}


map.on('draw:created', function(event) {
    var layer = event.layer;
    allPoints = layer.getLatLngs();
    var newpopup = L.popup({ closeOnClick: false }).setContent("Start");
    var marker = L.marker(allPoints[0], {
          draggable: true,
    }).addTo(map);
    selectColor(layer);
    lastLayer = layer;
    drawnItems.addLayer(layer);
    addClickListener(layer);
    updateTable(layer);
});

map.on('draw:editstop', function(event){
    updateTable(lastLayer);
    selectColor(lastLayer);
});

map.on('draw:deleted', function(event){
    var layers = event.layers;
    layers.eachLayer(function(layer) {
        if (layer === lastLayer) {
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
