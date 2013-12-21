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

        this.render = function(){
            this.currentFrameContext.clearRect(0, 0, this.frameWidth, this.frameHeight);
            this.currentFrameContext.drawImage(this.image, this.frameWidth*this.currentFrame, 0, this.frameWidth, this.frameHeight, 0, 0, this.frameWidth, this.frameHeight);
		
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