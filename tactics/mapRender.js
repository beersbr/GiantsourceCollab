function getMap(mapId) { 
  $.ajax({url:"resources/map"+mapId+".json",dataType:"json",success:renderTiles});
}

function renderTiles(mapObj) {
  
  // Loop through each row
  for(var r in mapObj) {
    var row = mapObj[r];
    // Loop through each column
    for(var c in row) {      
      var tile = row[c];
      // Set the class for tile  
      var tileClass = "";
      if(r == 0) tileClass += " top";      // First row, top of map
      if(c == row.length - 1) tileClass += " right";    // Last column, right of map
      if(r == mapObj.length - 1) tileClass += " bottom";   // Last row, bottom of map
      if(c == 0) tileClass += " left";     // First column, left of map
        
      // Add the tile to the page
      $("#map").append("<div class='"+tileClass+"'><img src='"+tile.image+"'/></div>");     
    }
  }
}



window.onload = function () {
  getMap(1);
}