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
  
  this.mapArray = [[[{}]]];
  
  this.loadCube = function(x, y, z) {
    return this.mapArray[x][y][z];
  }
  
  this.saveCube = function(cubeSettings) {    
    // Make sure the x,y and z arrays exists
    if(!self.mapArray[cubeSettings.x]) self.mapArray[cubeSettings.x] = [[[{}]]];
    if(!self.mapArray[cubeSettings.x][cubeSettings.y]) self.mapArray[cubeSettings.x][cubeSettings.y] = [[[{}]]];
    if(!self.mapArray[cubeSettings.x][cubeSettings.y][cubeSettings.z]) self.mapArray[cubeSettings.x][cubeSettings.y][cubeSettings.z] = [[[{}]]];
    
    // Set the value
    self.mapArray[cubeSettings.x][cubeSettings.y][cubeSettings.z] = cubeSettings;
  }
  
  
}