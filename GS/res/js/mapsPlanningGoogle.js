var uci=new google.maps.LatLng(33.6454,-117.8426);
var map;
var flightPath;
var editable = false;
var activePathID = 0;
var activePath = paths[0];
var paths = [];

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

    //flightPath = new google.maps.Polyline({
    //                                          strokeColor:"#0000FF",
    //                                          strokeOpacity:0.8,
    //                                          strokeWeight:2
    //                                      });

    //flightPath.setMap(map);

    //Adds the click listener for ploting waypoints
    google.maps.event.addListener(map, 'click', function(event){
        addLatLng(event.latLng);
        cbridge.pointAddedToMap(event.latLng.lat(),event.latLng.lng(),(paths[activePathID]).getPath().getLength(),activePathID);
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

//Interface functions for working with Cbridge.js

/*
  @brief createNewPath Creates a new GoogleMaps Polyline to act as a flightPath
  and gives it the specified id.
  @param id - the id the new path will have
  @author Jordan Dickson - Feb 15, 2017
*/
function createNewPath(id){
    if(paths[id] === undefined){
        //@todo give paths different colors
        var fp = new google.maps.Polyline({
                                              strokeColor:"#0000FF",
                                              strokeOpacity:0.8,
                                              strokeWeight:2
                                          });
        paths.splice(id,0,fp);
        paths[id].setMap(map);
    }
}


function setActivePath(id){
    activePathID = id;
    activePath = paths[activePathID];
    editable = true;
}

function disableEditing(){
    editable = false;
}

