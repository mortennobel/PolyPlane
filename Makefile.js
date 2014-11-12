// 
// Build project for emscripten
// Run using:
// node make.js [-f FILE, --file=FILE, --makefile=FILE] [target]
//

var target = "Release";//"DEBUG";

for (var i=2;i<process.argv.length;i++){
    if (process.argv[i].indexOf('-')===0){
        i++;
    } else  if (i === process.argv.length-1){
        target = process.argv[i];
    }
}

var project = {
    "options": [(target=="debug"?"-O0":"-O3"), "-Werror"/*, "-s USE_SDL=2"*/],
    "buildoptions": ["-std=c++11", "-stdlib=libc++", "-fno-exceptions"],
    "defines": ["GLM_FORCE_RADIANS",(target=="debug"?"DEBUG":"NDEBUG")],
    "targetdir": "../PolyPlane-pages",
    "target": "index.html",
    "includedirs": [ "../kick/src", "../kick/libs/include" ,"./src"],
	"files":[ {
            "root":"../kick/",
            "filter":"src/.*\\.cpp"
        },
        {
            "root":"./src/",
            "filter":".*.cpp"}],
    "embed":[
	{
            "root":"../kick/",
            "filter":"assets/shaders/\\.*"
	},
        {
            "root":".",
            "filter":"poly-assets/models/.*ply"
        },
        {
            "root":"../kick/",
            "filter":"assets/font/.*\\.fnt"
        },
        {
            "root":"../kick/",
            "filter":"assets/ui/.*\\.txt"
        },
        {
            "root":".",
            "filter":"poly-assets/shaders/.*glsl"
        },
        {
            "root":".",
            "filter":"poly-assets/shaders/.*shader"
        }],
    "preload":[
        {
            "root":"../kick",
            "filter":"assets/textures/\\.*"
        },
        {
            "root":"../kick",
            "filter":"assets/ui/\\.*png"
        },
        {
            "root":"../kick",
            "filter":"assets/font/.*\\.png"
        },
        {
            "root":"../kick",
            "filter":"assets/ui/.*\\.png"
        },
        {
            "root":".",
            "filter":"poly-assets/textures/.*\\.png"
        }
    ]
};

module.exports = project;
