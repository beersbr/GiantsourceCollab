VECTOR = (function(){
    var vector = {};

    vector.Vector = function(x, y, z){
        this.x = x || 0;
        this.y = y || 0;
        this.z = z || 0;

        // .magnitude
        Object.defineProperty(this, "magnitude", {
            get: function(){
                return (Math.sqrt(this.x*this.x + this.y*this.y));
            }
        });
    }


    vector.UP    = new vector.Vector( 0, -1);
    vector.DOWN  = new vector.Vector( 0,  1);
    vector.LEFT  = new vector.Vector(-1,  0);
    vector.RIGHT = new vector.Vector( 1,  0);

    vector.add = function(a, b){
        return (new vector.Vector(a.x+b.x, a.y+b.y, a.z+b.z));
    }

    vector.subtract = function(a, b){
        return (new vector.Vector(a.x-b.x, a.y-b.y, a.z-b.z));
    }

    vector.unit = function(v){
        //TODO: set dirty flag on vector to minimize sqrt calls
        var magnitude = v.magnitude;
        return (new vector.Vector(v.x / v.magnitude, v.y / v.magnitude));
    }

    vector.multiplyScalar = function(v, scalar){
        return (new vector.Vector(v.x*scalar, v.y*scalar, v.z*scalar));
    }

    return vector;
})();