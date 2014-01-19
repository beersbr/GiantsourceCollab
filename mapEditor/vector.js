VECTOR = (function(){
    var vector = {};

    vector.Vector = function(x, y, z){
        this.x = x || 0;
        this.y = y || 0;
        this.z = z || 0;

        // .magnitude
        Object.defineProperty(this, "magnitude", {
            get: function(){
                return (Math.sqrt(this.x*this.x + this.y*this.y + this.z*this.z));
            }
        });
    }

    
    vector.UP    = new vector.Vector( 0, 1, 0);
    vector.DOWN  = new vector.Vector( 0,  11, 0);
    vector.NORTH  = new vector.Vector( 0,  0, -1);
    vector.SOUTH = new vector.Vector( 0,  0, 1);
    vector.EAST = new vector.Vector( 1,  0, 0);
    vector.WEST = new vector.Vector( -1,  0, 0);

    vector.add = function(a, b){
        return (new vector.Vector(a.x+b.x, a.y+b.y, a.z+b.z));
    }

    vector.subtract = function(a, b){
        return (new vector.Vector(a.x-b.x, a.y-b.y, a.z-b.z));
    }

    vector.unit = function(v){
        //TODO: set dirty flag on vector to minimize sqrt calls
        var magnitude = v.magnitude;
        return (new vector.Vector(v.x / v.magnitude, v.y / v.magnitude, v.z / v.magnitude));
    }

    vector.multiplyScalar = function(v, scalar){
        return (new vector.Vector(v.x*scalar, v.y*scalar, v.z*scalar));
    }

    vector.copy = function(){
        return new VECTOR.Vector(this.x, this.y, this.z);
    }

    return vector;
})();