function Sprite(args){
        if(args == undefined) args = {}

        this.frameWidth = args.frameWidth || -1;
        this.frameHeight = args.frameHeight || -1;
        this.image = args.image || null;
        this.frameTime = args.frameTime || -1; //1000/60 * 4;

        // error handling => didnt pass in frame width and height and image
        if(this.frameWidth < 0) {
            // Some error
        }
        if(this.frameHeight < 0) {
            // Some error
        }
        if(this.frameTime < 0) {
            // Some error
        }
        if(!this.image) {
            // Some error
        }
        //console.log(args);
        this.imageWidth = this.image.width;
        this.imageHeight = this.image.height;

        this.framesCount = this.imageWidth / this.frameWidth;
        this.currentFrame = 0;
		//console.log('TOTAL FRAMES = '+ this.framesCount);
        this.currentFrameTime = 0;
        this.currentFrameElapsedTime = 0;
        this.currentFrameImage = document.createElement("canvas");
        this.currentFrameContext = this.currentFrameImage.getContext("2d");
        this.currentFrameImage.width = this.frameWidth;
        this.currentFrameImage.height = this.frameHeight;

        this.render = function(rotation){

            this.currentFrameContext.clearRect(0, 0, this.frameWidth, this.frameHeight);

            if (rotation) {

                //Convert degrees to radian 
                var rad = rotation * Math.PI / 180;

                //Set the origin to the center of the image
                this.currentFrameContext.translate(this.frameWidth / 2, this.frameHeight / 2);

                //Rotate the canvas around the origin
                 this.currentFrameContext.rotate(rad);

                //draw the image    
                 this.currentFrameContext.drawImage(this.image,this.frameWidth / 2 * (-1),this.frameHeight / 2 * (-1),this.frameWidth,this.frameHeight);

                //reset the canvas  
                 this.currentFrameContext.rotate(rad * ( -1 ) );
                 this.currentFrameContext.translate((this.frameWidth / 2) * (-1), (this.frameHeight / 2) * (-1));

            } else {
                
                 this.currentFrameContext.drawImage(this.image, this.frameWidth*this.currentFrame, 0, this.frameWidth, this.frameHeight, 0, 0, this.frameWidth, this.frameHeight);

            }
            if(this.currentFrameElapsedTime < this.frameTime){
                this.currentFrameElapsedTime += GAME.elapsedTime;
            }
            else {
                this.currentFrame = (this.currentFrame + 1) % this.framesCount;
                this.currentFrameElapsedTime = (this.currentFrameElapsedTime - this.frameTime);
            }

            return this.currentFrameImage;
        }
    }