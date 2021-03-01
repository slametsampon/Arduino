var slideDarkness = document.getElementById("darknessRange");
var outputDarkness = document.getElementById("darknessSetting");
var actualBrightness = document.getElementById("brightness");

var slideDistance = document.getElementById("distanceRange");
var outputDistance = document.getElementById("distanceSetting");
var actualDistance = document.getElementById("distance");

outputDarkness.innerHTML = slideDarkness.value;
outputDistance.innerHTML = slideDistance.value;

slideDarkness.oninput = function() {
    outputDarkness.innerHTML = this.value;
}

outputDistance.innerHTML = slideDistance.value;

slideDistance.oninput = function() {
    outputDistance.innerHTML = this.value;
}
