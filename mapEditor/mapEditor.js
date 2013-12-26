mapGrid = [[]];

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
  
  this.onStep = function() {}  // Function to run when tile is stpped on  
  this.onDeath = function() {}  // Function to run when tile loses all hp
  
}

function addRow() {
  
  var row = $("#mapGrid tr").length;
  var newRow = "<tr id=\"row"+row+"\"><td id=\"row"+row+"-col1\"><div></div></td><td class=\"newCol\"><input type=\"button\" value=\"+\" onclick=\"addCol($(this).closest('tr').attr('id').replace('row',''))\" /></td></tr>";  
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
  
  $("#tile-enabled").val(tile.enabled);
  $("#tile-x").val(tile.x);
  $("#tile-y").val(tile.y);
  $("#tile-z").val(tile.z);
  $("#tile-hp").val(tile.hp);
  $("#tile-image").val(tile.image);
  $("#tile-damage").val(tile.damage);
  $("#tile-type").val(tile.type);
  
}

function saveTile() {
  var row = $("#tile-x").val() - 1;
  var col = $("#tile-y").val() - 1;
  var tile = mapGrid[row][col];
  tile.enabled = $("#tile-enabled").val();
  tile.z = $("#tile-z").val();
  tile.hp = $("#tile-hp").val();
  tile.image = $("#tile-image").val();
  tile.damage = $("#tile-damage").val();
  tile.type = $("#tile-type").val();
}

window.onload = function () {
  // Make tiles clickable to activate
  $("#mapGrid td").click(function() { activateTile(this) });
  
  // Add a new tile at row 1, col 1
  mapGrid[0][0] = new Tile({"x":1,"y":1});
  
  // Click the title to activate it
  $("#mapGrid td").click();
  
}