function cubeObject() {
  var cubeObject = {
    "x": 0,
    "y": 0,
    "z": 0,
    "faces": {
        "up": {
            "hp": 0,
            "image": "",
            "damage": 0,
            "type": 0,
            "onStep": "",
            "onDeath": ""
        },
        "down": {
            "hp": 0,
            "image": "",
            "damage": 0,
            "type": 0,
            "onStep": "",
            "onDeath": ""
        },
        "north": {
            "hp": 0,
            "image": "",
            "damage": 0,
            "type": 0,
            "onStep": "",
            "onDeath": ""
        },
        "south": {
            "hp": 0,
            "image": "",
            "damage": 0,
            "type": 0,
            "onStep": "",
            "onDeath": ""
        },
        "east": {
            "hp": 0,
            "image": "",
            "damage": 0,
            "type": 0,
            "onStep": "",
            "onDeath": ""
        },
        "west": {
            "hp": 0,
            "image": "",
            "damage": 0,
            "type": 0,
            "onStep": "",
            "onDeath": ""
        }
    }
  };
  return cubeObject;
}

function tactex(args) {
  if(args == undefined) args = {};
  
  var self = this;
  var faces = ["up","down","north","south","east","west"];
  
  this.mapArray = [[[{}]]];
  
  this.loadCube = function(x, y, z) {
    return this.mapArray[x][y][z];
  }
  
  this.newCube = function(cubeSettings) {    
    
    // Build the cube object and add the settings
    var cubeObj = new cubeObject();
    cubeObj.x = cubeSettings.x;
    cubeObj.y = cubeSettings.y;
    cubeObj.z = cubeSettings.z;
    
    // Make sure the x,y and z arrays exists, then set the value
    if(!self.mapArray[cubeObj.x]) self.mapArray[cubeObj.x] = [[[cubeObj]]];
    if(!self.mapArray[cubeObj.x][cubeObj.y]) self.mapArray[cubeObj.x][cubeObj.y] = [[cubeObj]];
    if(!self.mapArray[cubeObj.x][cubeObj.y][cubeObj.z]) self.mapArray[cubeObj.x][cubeObj.y][cubeObj.z] = [cubeObj];
  }

  this.saveCube = function() {
    
    var x = $("#tile-x").val();
    var y = $("#tile-y").val();
    var z = $("#tile-z").val();
    
    var cubeSettings = new cubeObject();
    
    // Save tile values
    for(var f in faces) {
      cubeSettings.faces[faces[f]].hp = $("#tile-"+faces[f]+"-hp", $("#if_cubeEditor").contents()).val();      
      cubeSettings.faces[faces[f]].damage = $("#tile-"+faces[f]+"-damage", $("#if_cubeEditor").contents()).val();
      cubeSettings.faces[faces[f]].type = $("#tile-"+faces[f]+"-type", $("#if_cubeEditor").contents()).val();  
      cubeSettings.faces[faces[f]].onStep = $("#tile-"+faces[f]+"-onStep", $("#if_cubeEditor").contents()).val();  
      cubeSettings.faces[faces[f]].onDeath = $("#tile-"+faces[f]+"-onDeath", $("#if_cubeEditor").contents()).val();  
      cubeSettings.faces[faces[f]].image = $("#tile-"+faces[f]+"-image", $("#if_cubeEditor").contents()).val();
      
      // Update map editor image 
      mapEditCanvas.cubes[mapEditCanvas.cubesIndex[cubeSettings.x][cubeSettings.y][cubeSettings.z]].changeTexture(faces[f],cubeSettings.faces[faces[f]].image);    
    }
  }  
  
}