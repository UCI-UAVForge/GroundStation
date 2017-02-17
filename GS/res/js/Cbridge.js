window.onload = function() {
    if (location.search != "")
        var baseUrl = (/[?&]webChannelBaseUrl=([A-Za-z0-9\-:/\.]+)/.exec(location.search)[1]);
    else
        var baseUrl = "ws://localhost:20270";
    //alert(baseUrl);
    var socket = new WebSocket(baseUrl);
    //alert("Starting Socket!");
    socket.onclose = function() {
        console.error("web channel closed");
    };

    socket.onerror = function(error) {
        console.error("web channel error: " + error);
    };
    socket.onopen = function() {
        //alert("Socket open!");
        new QWebChannel(socket, function(channel) {
            // make dialog object accessible globally
            window.cbridge = channel.objects.cbridge;

            cbridge.createNewPath.connect(function(id) {
                createNewPath(id);
            });

            cbridge.setActivePath.connect(function(id) {
                setActivePath(id);
            });

            cbridge.disableEditing.connect(function() {
                disableEditing();
            });

            cbridge.appendPointToPath.connect(function(lat, lng, id) {
                appendPointToMap(lat,lng,id);
            });

            cbridge.insertPointToMap.connect(function(lat, lng, index, id) {
                insertPointToMap(lat,lng,index,id);
            });

            cbridge.removePointFromMap.connect(function(index, id){
                removePointFromMap(index,id);
            });

            cbridge.clearFlightPath.connect(function(id){
                clearFlightPath(id);
            });

            initializeMap();
        });

    }
}
