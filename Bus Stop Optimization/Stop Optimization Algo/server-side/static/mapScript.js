function initMap() {
    const latitude = parseFloat(gpsData.latitude);
    const longitude = parseFloat(gpsData.longitude);
    console.log(latitude);
    console.log(longitude);
    const map = new google.maps.Map(document.getElementById("map"), {
      center: { lat: latitude, lng: longitude },
      zoom: 15,
    });

    const buscoords = {lat: latitude, lng: longitude  };

    const marker = new google.maps.Marker({
      position: buscoords,
      map: map,
       icon: {
         url: markerIconUrl, // path
         scaledSize: new google.maps.Size(400,400), // Setting the desired width and height
       }
    });
    

    // Define waypoints (replace with your actual waypoints)
    const waypoints = [
      {lat:28.31720153505583 ,lng:76.91070993179935},
      {lat:28.315545789061837 ,lng:76.89685069561884},
      {lat:28.328728531947725 ,lng:76.91394381093588},
      {lat:28.336578774765716 ,lng:76.92151563530608},
      {lat:28.357508384203687 ,lng:76.93838634840272},
      {lat:28.3651367510074 ,lng: 76.94147625314923},
      {lat:28.37737120386127 ,lng:76.95709743851673},
      {lat:28.38058893209867 ,lng:76.96347804867774},
      {lat:28.414660896873006 ,lng:76.99451090882599},
      {lat:28.446746048096752 ,lng: 77.03290505293396},  // Example waypoint
    ];

    // Create a LatLngBounds object to auto-zoom the map
    const bounds = new google.maps.LatLngBounds();

    // Create an array to hold the waypoints for Directions API request
    const waypointsForDirections = waypoints.slice(1, waypoints.length - 1).map(waypoint => ({
      location: new google.maps.LatLng(waypoint.lat, waypoint.lng),
      stopover: true
    }));

    // Request directions from Google Maps Directions API
    const directionsService = new google.maps.DirectionsService();
    const request = {
      origin: new google.maps.LatLng(waypoints[0].lat, waypoints[0].lng),
      destination: new google.maps.LatLng(waypoints[waypoints.length - 1].lat, waypoints[waypoints.length - 1].lng),
      waypoints: waypointsForDirections,
      travelMode: google.maps.TravelMode.DRIVING
    };

    directionsService.route(request, function(response, status) {
      if (status == google.maps.DirectionsStatus.OK) {
        const directionsDisplay = new google.maps.DirectionsRenderer({
          map: map,
          directions: response,
          suppressMarkers: true
        });

        addWaypointMarkers(map, waypoints, response.routes[0].legs);
      }
    })

    function addWaypointMarkers(map, waypoints, legs) {
      for (let i = 0; i < legs.length; i++) {
        const waypointMarker = new google.maps.Marker({
          map: map,
          position: legs[i].start_location,
          label: String.fromCharCode(65 + i), // A, B, C, ...
        });
      }
    }
}