var uci=new google.maps.LatLng(33.6454,-117.8426);
var map;
var flightPath;
var clickable = false;

//Setup function that creates the initial map state.
function initializeMap() {
    //alert("initializing!");
    var featureOpts = [{
                           elementType: 'labels',
                           stylers:[
                               {visibility: 'off'}
                           ]
                       }];

    var mapCanvas = document.getElementById('map_canvas');
    var mapOptions = {
        center: uci,
        zoom: 13,
        mapTypeId: google.maps.MapTypeId.SATELLITE
    };

    map = new google.maps.Map(mapCanvas, mapOptions);

    flightPath = new google.maps.Polyline({
                                              strokeColor:"#0000FF",
                                              strokeOpacity:0.8,
                                              strokeWeight:2
                                          });

    flightPath.setMap(map);

    //Adds the click listener for ploting waypoints
    google.maps.event.addListener(map, 'click', function(event){
        addLatLng(event.latLng);
        //cbridge.addPointToTable(event.latLng.lat(),event.latLng.lng());
        cbridge.addPointToTable(event.latLng.lat(),event.latLng.lng());
    });
}

function addLatLngCoords(lat,lng) {
    //Used on the c++ side to add a new point to the map.
    var location = new google.maps.LatLng(lat,lng);
    addLatLng(location);
    return "Adding new point.";
}

function addLatLng(myLocation) {
    //Adds a new point to the flightpath list by pushing the myLocation tuple to the list.
    flightPath.getPath().push(myLocation);
}

function clearMap() {
    //Called from the c++ side to refresh the map.
    //modified by Arash on 2/23/15: it will now clear the map without
    //changing the zoom level or center of the map
    //modified by Jordan 5/22/15: no longer needs to reinitialize
    flightPath.getPath().clear();
}
