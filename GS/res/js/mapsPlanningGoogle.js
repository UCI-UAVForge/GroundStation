var uci=new google.maps.LatLng(33.6454,-117.8426);
var map;
var flightPath;
var editable = false;
var activePathID = 0;
var paths = [];
var activePath = paths[0];

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

//    flightPath = new google.maps.Polyline({
//                                              strokeColor:"#0000FF",
//                                              strokeOpacity:0.8,
//                                              strokeWeight:2
//                                          });

//    flightPath.setMap(map);

    //Adds the click listener for ploting waypoints
    google.maps.event.addListener(map, 'click', function(event){
        var len = activePath.getPath().getLength();
        activePath.getPath().push(event.latLng);
        cbridge.pointAddedToMap(event.latLng.lat(),event.latLng.lng(),len,activePathID);
    });
    cbridge.finishedLoading();
}

//Interface functions for working with Cbridge.js

/*
  @brief createNewPath Creates a new GoogleMaps Polyline to act as a flightPath
  and gives it the specified id.
  @param id - the id the new path will have
  @author Jordan Dickson - Feb 15, 2017
*/


function createNewPath(id){
    console.log("creating new path");
    if(!paths[id]){
        //@todo give paths different colors
        var fp = new google.maps.Polyline({
                                              strokeColor:"#FF00FF",
                                              strokeOpacity:0.8,
                                              strokeWeight:2
                                          });
        paths[id] = fp;
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

function appendPointToPath(lat,lng,id){
    if(paths[id]){
        var coord = new google.maps.LatLng(lat,lng);
        paths[id].getPath().push(coord);
    }
}

function insertPointToMap(lat,lng,index,id){
    if(paths[id]){
        var coord = new google.maps.LatLng(lat,lng);
        paths[id].getPath().insertAt(index,coord);
    }
}

function removePointFromMap(index, id){
    if(paths[id]){
        paths[id].getPath().removeAt(index);
    }
}

function clearFlightPath(id){
    if(paths[id]){
        paths[id].getPath().clear();
    }
}
