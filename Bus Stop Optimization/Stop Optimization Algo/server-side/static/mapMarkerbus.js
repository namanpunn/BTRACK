// new info panel
infoWindow = new google.maps.InfoWindow();
// location tab creation
const locationButton = document.createElement("button");
// location tab text
locationButton.textContent = "Pan to Current Location";
// add the button as a input
locationButton.classList.add("custom-map-control-button");
// bind the button above with google maps API control
map.controls[google.maps.ControlPosition.TOP_CENTER].push(locationButton);
// listening for click by user
locationButton.addEventListener("click", () => {
// Try HTML5 geolocation.
if (navigator.geolocation) {
    navigator.geolocation.getCurrentPosition(
    (position) => {
        panTo();
    },
    // if exception pass error
    () => {
        handleLocationError(true, infoWindow, map.getCenter());
    },
    );
} else {
    // Browser doesn't support Geolocation or a fatal error
    handleLocationError(false, infoWindow, map.getCenter());
}
});

function panTo(){
console.log('panTo called, please check if fix');

map.panTo(buscoords);
map.setZoom(15);
}

// error handling function
function handleLocationError(browserHasGeolocation, infoWindow, pos) {
infoWindow.setPosition(pos);
infoWindow.setContent(
    browserHasGeolocation
    ? "Error: The Geolocation service failed. Bus location unavailable/unrefreshable."
    : "Error: Unexpected FATAL error. Please report this data back.",
);
}