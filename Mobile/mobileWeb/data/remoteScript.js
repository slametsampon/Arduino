var slider = document.getElementById("speedRange");
var output = document.getElementById("speed");
output.innerHTML = slider.value;

slider.oninput = function() {
    output.innerHTML = this.value;
}
function updateAction(cmd) {
    var state;
    document.getElementById('btnForwardImg').src = 'beforeForward.png';
    document.getElementById('btnStopImg').src = 'beforeStop.png';
    document.getElementById('btnBackwardImg').src = 'beforeBackward.png';
    document.getElementById('btnRightImg').src = 'beforeRight.png';
    document.getElementById('btnLeftImg').src = 'beforeLeft.png';
    switch (cmd) {
        case "btnForward":
            state = "Forward";
            document.getElementById('btnForwardImg').src = 'activeForward.png';
            break;
        case "btnLeft":
            state = "Left";
            document.getElementById('btnLeftImg').src = 'activeLeft.png';
            break;
        case "btnRight":
            state = "Right";
            document.getElementById('btnRightImg').src = 'activeRight.png';
            break;
        case "btnBackward":
            state = "Backward";
            document.getElementById('btnBackwardImg').src = 'activeBackward.png';
            break;
        case "btnStop":
            state = "Stop";
            document.getElementById('btnStopImg').src = 'activeStop.png';
            break;
        default:
        break;
    }                
    document.getElementById("Status").innerHTML = state;
}
