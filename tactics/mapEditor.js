mapGrid = [[]];

var newColButton = "<td class=\"newCol\"><input type=\"button\" value=\"+\" onclick=\"addCol($(this).closest('tr').attr('id').replace('row',''))\" /></td>",
    newRowButton = "<tr class=\"newRow\"><td><input type=\"button\" value=\"+\" onclick=\"addRow()\" /></td></tr>";


var imageList = ["tile-fire","tile-glass","tile-grass","tile-stone","tile-wood"];
var tileTypes = {};
    tileTypes.grass = 1;
    tileTypes.wood = 2;
    tileTypes.stone = 3;
    tileTypes.glass = 4;
    tileTypes.fire = 5;

function Tile(args) {
  
  if(args == undefined) args = {};

  this.enabled = true;       // Tile can be moved onto (there is pry a better name for this)
  this.x = args.x || 0;      // Row
  this.y = args.y || 0;      // Column
  this.z = args.z || 0;      // Elevation
  this.hp = args.hp || 100;
  this.image = args.image || null; // 3d image file/object/or something?
  this.damage = args.image || 0;   // Damage taken when on tile
  this.type = args.type || 0;      // Grass, Rock, Wood, Water, Fire, Etc
  
  this.onStep = args.onStep || ""; // Function to run when tile is stpped on  
  this.onDeath = args.onDeath || "";  // Function to run when tile loses all hp
  
}

function addRow() {
  
  var row = $("#mapGrid tr").length;
  var newRow = "<tr id=\"row"+row+"\"><td id=\"row"+row+"-col1\"><div></div></td>"+newColButton+"</tr>";  
  $("#mapGrid tr.newRow").before(newRow);
  $("#mapGrid #row"+row+"-col1").click(function() { activateTile(this) });
  mapGrid.push(new Array(new Tile({"x":row,"y":1})));
}

function addCol(row) {
  var col = $("#mapGrid #row"+row+" td").length;
  var newCol = "<td id=\"row"+row+"-col"+col+"\"><div></div></td>";
  $("#mapGrid #row"+row+" td.newCol").before(newCol);
  $("#mapGrid #row"+row+"-col"+col).click(function() { activateTile(this) });
  mapGrid[row - 1].push(new Tile({"x":row,"y":col}));
}

function addTile(row, col) {
  
}

function activateTile(e) {
  if($(e).hasClass('newCol')) return false;
  if($(e).closest("tr").hasClass('newRow')) return false;
  
  $("#mapGrid td").removeClass("activeTile");
  $(e).addClass("activeTile");
  
  
  var t = $(e).attr("id").replace("row","").replace("col","").split("-");
  var row = t[0];
  var col = t[1];
  loadTileInfo(row, col);
}

function loadTileInfo(row, col) {
  
  var tile = mapGrid[row - 1][col - 1];   
  $("#tile-enabled-"+(tile.enabled ? "true" : "false")).prop("checked","true");
  $("#tile-x").val(tile.x);
  $("#tile-y").val(tile.y);
  $("#tile-z").val(tile.z);
  $("#tile-hp").val(tile.hp);
  $("#tile-image").val(tile.image);
  $("#tile-damage").val(tile.damage);
  $("#tile-type").val(tile.type);
  $("#tile-onStep").val(tile.onStep);  
  $("#tile-onDeath").val(tile.onDeath);  
  
}

function saveTile() {
  var row = $("#tile-x").val() - 1;
  var col = $("#tile-y").val() - 1;
  var tile = mapGrid[row][col];
  
  // Save tile values
  tile.enabled = parseInt($("input[name=tile-enabled]:checked").val());
  tile.z = $("#tile-z").val();
  tile.hp = $("#tile-hp").val();
  tile.image = $("#tile-image").val();
  tile.damage = $("#tile-damage").val();
  tile.type = $("#tile-type").val();  
  tile.onStep = $("#tile-onStep").val();  
  tile.onDeath = $("#tile-onDeath").val();  
  
  console.log(tile);
  
  toggleTile({"enabled":tile.enabled,"x":tile.x,"y":tile.y});
  
  // Update image
  $("#mapGrid td#row"+tile.x+"-col"+tile.y+" div").attr("style","background-image:url("+tile.image+")");
}

function readMap() {
  
  readBlob();
}

function readBlob(opt_startByte, opt_stopByte) {

  var files = document.getElementById('loadMap').files;
  if (!files.length) {
    alert('Please select a file!');
    return;
  }

  var file = files[0];
  var start = parseInt(opt_startByte) || 0;
  var stop = parseInt(opt_stopByte) || file.size - 1;

  var reader = new FileReader();

  // If we use onloadend, we need to check the readyState.
  reader.onloadend = function(evt) {
    if (evt.target.readyState == FileReader.DONE) { // DONE == 2
      mapGrid = $.parseJSON(evt.target.result);
      loadMap(); 
    }
  };

  var blob = file.slice(start, stop + 1);
  reader.readAsBinaryString(blob);
}
  
function loadMap() {
  
  // Clear out current map
  $("#mapGrid tbody").html("");
  
  // Start the gridHTML
  var gridHTML = "";
  
  // Loop through each row
  for(var r in mapGrid) {
    var row = mapGrid[r];
    // Loop through each column
    for(var c in row) {      
      var tile = row[c];
      
      // Strings for pre and post content
      var preText = "",
          postText = ""; 
      
      // Add tr tags for start and end of rows
      if(c == 0) preText = " <tr id='row"+(parseInt(r) + 1)+"'>";
      if(c == row.length - 1) postText = newColButton+"</tr>";
      
        
      // Add the tile to the page
      gridHTML += preText+"<td id=\"row"+(parseInt(r)+1)+"-col"+(parseInt(c)+1)+"\"><div style='background-image:url("+tile.image+")'></div></td>"+postText;
    }
  }
  
  // Add the new row button as the last row
  gridHTML += newRowButton;
  
  // Add the html to the table
  $("#mapGrid tbody").append(gridHTML);     
  
  // Make tiles clickable to activate
  $("#mapGrid td").click(function() { activateTile(this) });
  
  // Activate row 1 col 1
  $("#mapGrid td#row1-col1").click();
}

function saveMap() {
  window.open("data:text/octet-stream," + JSON.stringify(mapGrid));  
}

function loadTileImages() {
  // Store the html in a string
  var h = "";
  
  // Start with an option for a new image
  h += "<option value='0'>Add...</option>";
  
  for(var i in imageList) {
     h += "<option value='resources/"+imageList[i]+".jpg'>"+imageList[i]+".jpg</option>";
  }
  $("#tile-image").append(h);
}

function loadTileTypes() {
  // Store the html in a string
  var h = "";
  
  for(var t in tileTypes) {
     h += "<option value='"+tileTypes[t]+"'>"+t+"</option>";
  }
  $("#tile-type").append(h);
}

function enableTile(args) {
  if(args == undefined) args = {};
  args.enabled = args.enabled || 1;
  toggleTile(args);
}

function disableTile(args) {
  if(args == undefined) args = {};
  args.enabled = args.enabled || 0;
  toggleTile(args)
}

function toggleTile(args) {
  
  if(args == undefined) args = {};
  var enabled = args.enabled || 0;
  var x = args.x || $("#tile-x").val();
  var y = args.y || $("#tile-y").val();
  
  if(enabled) $("#row"+x+"-col"+y).removeClass("disabledTile");
  else $("#row"+x+"-col"+y).addClass("disabledTile");
}

function init() {
  
  loadTileImages(); 
  loadTileTypes(); 
  
  // Make tiles clickable to activate
  $("#mapGrid td").click(function() { activateTile(this) });
  
  // Trigger to load map after file is selected
  document.getElementById('loadMap').addEventListener('change', readMap, false);
  
  // Add a new tile at row 1, col 1
  mapGrid[0][0] = new Tile({"x":1,"y":1});
  
  // Click the title to activate it
  $("#mapGrid td").click();
  
}

window.onload = function () {
  init();
}