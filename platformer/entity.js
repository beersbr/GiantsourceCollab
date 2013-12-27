function Entity(args){
    if(args == undefined) args = {};

    var x = args.x || 0;
    var y = args.y || 0;
    var w = args.w || 1;
    var h = args.h || 1;
    this.hitW = args.hitW || w;
    this.hitH = args.hitH || h;



    this.position = new VECTOR.Vector(x, y);
    this.size = new VECTOR.Vector(w, h);
    this.hitSize = new VECTOR.Vector(w, h);
    this.velocity = new VECTOR.Vector();

    this.image = null;

    this.update = function (elapsedTime) { throw "NOT IMPLEMENTED"; };
    this.draw = function (renderContext) { throw "NOT IMPLEMENTED"; };

    this.toRect = function () {
        var hw = this.size.x / 2;
        var hh = this.size.y / 2;
        return (new Rect(this.position.x - hw, this.position.y - hh, this.size.x, this.size.y));
    }

    this.hitBox = function () {

        var hw = (this.size.x-this.hitW) / 2;
        var hh = (this.size.y-this.hitH) / 2;

        return (new Rect(this.position.x - hw, this.position.y - hh, this.hitW, this.hitH));
    }
}