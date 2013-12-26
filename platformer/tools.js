
    requestAnimFrame = (function () {
        return window.requestAnimationFrame ||
             window.webkitRequestAnimationFrame ||
             window.mozRequestAnimationFrame ||
             window.oRequestAnimationFrame ||
             window.msRequestAnimationFrame ||
             function (/* function FrameRequestCallback */ callback, /* DOMElement Element */ element) {
                 window.setTimeout(callback, 1000 / 60);
             };
    })();

    function InheritFrom(context, obj, arguments){
        context.__proto__ = new obj(arguments);
        context.prototype = context.__proto__;
        return true;
    }

    function RandomInt(max) {
        return parseInt(Math.random() * max);
    }


    function Point(x, y){
        this.x = x || 0;
        this.y = y || 0;
    }

    function Rect(x, y, w, h){
        this.x = x || 0;
        this.y = y || 0;
        this.w = w || 1;
        this.h = h || 1;
	
        Object.defineProperty(this, "cx", {
            get: function(){
                return (this.x + this.w/2);
            }
        });
	
        Object.defineProperty(this, "cy", {
            get: function(){
                return (this.y + this.h/2);
            }
        });

    }

     function getCursorPosition(e) {
        var x;
        var y;
        if (e.pageX != undefined && e.pageY != undefined) {
            x = e.pageX;
            y = e.pageY;
        }
        else {
            x = e.clientX + document.body.scrollLeft +
                    document.documentElement.scrollLeft;
            y = e.clientY + document.body.scrollTop +
                    document.documentElement.scrollTop;
        }
        x -= canvas.offsetLeft;
        y -= canvas.offsetTop;
         
        return [x,y];

    }

    function collideRect(r1, r2) {
        if (r1.x > r2.x + r2.w) return false;
        if (r1.x + r1.w < r2.x) return false;
        if (r1.y > r2.y + r2.h) return false;
        if (r1.y + r1.h < r2.y) return false;
        return true;
    }

    function drawImageRot(img,x,y,width,height,deg){

        //Convert degrees to radian 
        var rad = deg * Math.PI / 180;

        //Set the origin to the center of the image
        ctx.translate(x + width / 2, y + height / 2);

        //Rotate the canvas around the origin
        ctx.rotate(rad);

        //draw the image    
        ctx.drawImage(img,width / 2 * (-1),height / 2 * (-1),width,height);

        //reset the canvas  
        ctx.rotate(rad * ( -1 ) );
        ctx.translate((x + width / 2) * (-1), (y + height / 2) * (-1));
    }


    function collide(obj1, obj2) {
        if (obj1.position.x > obj2.position.x + obj2.size.x) return false;
        if (obj1.position.x + obj1.size.x < obj2.position.x) return false;
        if (obj1.position.y > obj2.position.y + obj2.size.y) return false;
        if (obj1.position.y + obj1.size.y < obj2.position.y) return false;
        return true;
    }
