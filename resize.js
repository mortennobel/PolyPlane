document.getElementById('output').style.display = "none";

function findPos(obj) {
    var curleft = curtop = 0;
    if (obj.offsetParent) {
        do {
            curleft += obj.offsetLeft;
            curtop += obj.offsetTop;

        } while (obj = obj.offsetParent);
    }
    return [curleft,curtop];
}

var resizeGame = function () {

    var gameArea = document.getElementById('canvas');
    var rect = gameArea.getBoundingClientRect();

    gameArea.width = window.innerWidth;
    gameArea.height = window.innerHeight - findPos(gameArea)[1];

    gameArea.parentElement.style.border = 0;

}

var startupResize = function(){
    var gameArea = document.getElementById('canvas');
    var rect = gameArea.getBoundingClientRect();

    var reload = rect.width != 800; // total hack - keep reloading until emscripten has set the correct size
    if (reload){
        setTimeout(startupResize, 16);
    }
    else {
        resizeGame();
    }
}

window.addEventListener('resize', resizeGame, false);
window.addEventListener('orientationchange', resizeGame, false);
startupResize();
