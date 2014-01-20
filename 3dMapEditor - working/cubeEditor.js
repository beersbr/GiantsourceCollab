var faces = ["up","down","north","south","east","west"];
var facePositions = {
  "up" : {"x": 0, "y": 0},
  "down" : {"x": 0, "y": 180},
  "north" : {"x": 90, "y": 0},
  "south" : {"x": 270, "y": 0},
  "east" : {"x": 360, "y": 270},
  "west" : {"x": 360, "y": 90}
};
var imageList = ["tile-dirt-1","tile-grass-1","tile-water-1","tile-wood-1"];

var tileTypes = {};
    tileTypes.grass = 1;
    tileTypes.wood = 2;
    tileTypes.stone = 3;
    tileTypes.glass = 4;
    tileTypes.fire = 5;
    tileTypes.dirt = 6;
    tileTypes.water = 7;

mapGrid = [[]];

mapGrid[0].push(cubeObject);

function loadTileImages() {
  // Store the html in a string
  var h = "";
  
  // Start with an option for a new image
  h += "<option value='0'>Add...</option>";
  
  for(var i in imageList) {
     h += "<option value='"+imageList[i]+".jpg'>"+imageList[i]+".jpg</option>";
  }
  $(".tile-image").append(h);
}

function loadTileTypes() {
  // Store the html in a string
  var h = "";
  
  for(var t in tileTypes) {
     h += "<option value='"+tileTypes[t]+"'>"+t+"</option>";
  }
  $(".tile-type").append(h);
}

function saveTile() {
  var row = $("#tile-x").val();
  var col = $("#tile-y").val();
  var tile = mapGrid[row][col];
  
  // Save tile values
  tile.enabled = parseInt($("input[name=tile-enabled]:checked").val());
  tile.z = $("#tile-z").val();
  tile.hp = $("#tile-hp").val();
  for(var i in faces) {
    tile.faces[faces[i]].image = $("#tile-"+faces[i]+"-image").val();
    tile.faces[faces[i]].damage = $("#tile-"+faces[i]+"-damage").val();
    tile.faces[faces[i]].type = $("#tile-"+faces[i]+"-type").val();  
    tile.faces[faces[i]].onStep = $("#tile-"+faces[i]+"-onStep").val();  
    tile.faces[faces[i]].onDeath = $("#tile-"+faces[i]+"-onDeath").val();  
  }
  
  console.log(tile);
  
  //toggleTile({"enabled":tile.enabled,"x":tile.x,"y":tile.y});
  
  // Update image
  $("#mapGrid td#row"+tile.x+"-col"+tile.y+" div").attr("style","background-image:url("+tile.image+")");
}

function activeFaceTab(face) {
  // Clear all tabs
  $("#tileStatsWindow #section-tabs span").removeClass("span-active");        
  // Set this as active
  $("#tab-"+face).addClass("span-active");
  
  // Clear all sections
  $("#tileStatsWindow section").removeClass("section-active");        
  // Set this as active
  $("#section-"+face).addClass("section-active");
  
  // Rotate to that face
  x = facePositions[face].x;
  y = facePositions[face].y;
}

loadTileImages(); 
loadTileTypes(); 

$("#tileStatsWindow #section-tabs span").click(function() { activeFaceTab($(this).data("face")) });