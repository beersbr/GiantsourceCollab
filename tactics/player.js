    function Player(args){
        if(args == undefined) args = {};
        InheritFrom(this, Entity, args);
        //console.log(args);
        
        this.image = RESOURCES.get(GAME.CurrentPlayer.name);
        this.sprite = new Sprite({ image: this.image, frameTime: (1000/60 * 8), frameHeight: GAME.CurrentPlayer.sprite.h, frameWidth: GAME.CurrentPlayer.sprite.w});


        var XP = 0,
            HP = 150, 
            MP = 300,
            STR = 10,
            DEX = 10, 
            INT = 10;
            
            

        this.level = this.XP / 100;
        
       
/*
        this.update = function(){

            var frameMoveSpeed = moveSpeed;

            if (GAME.Keyboard.keyIsDown("shift")) {
                if(! isSprinting){
                    nonSprintElapsedTime += GAME.elapsedTime;

                    if(nonSprintElapsedTime > sprintInterval || lastSprintTime == -1){
                        frameMoveSpeed = sprintSpeed;
                        isSprinting = true;
                        lastSprintTime = +(new Date());
                        nonSprintElapsedTime = 0;
                        sprintLength += GAME.elapsedTime;
                    }
                }
                else{
                    sprintElapsedTime += GAME.elapsedTime;
                    if(sprintElapsedTime > sprintTime){
                        isSprinting = false;
                        sprintElapsedTime = 0;
                    }
                    else{
                        frameMoveSpeed = sprintSpeed;
                        sprintLength += GAME.elapsedTime;
                    }
                }
            }
            else { 
                // Not sprinting
                isSprinting = false;
                sprintElapsedTime = 0;
                nonSprintElapsedTime += GAME.elapsedTime;            
                if(nonSprintElapsedTime > sprintInterval) sprintLength = 0;
            } 

            // Show run bar
            this.runBar();
            
            // Update character movement

            if (GAME.Keyboard.keyIsDown("a")) {
                this.velocity.x -= frameMoveSpeed;
            }
            if (GAME.Keyboard.keyIsDown("d")) {
                this.velocity.x += frameMoveSpeed;
            }
            if (GAME.Keyboard.keyIsDown("w")) {
                this.velocity.y -= frameMoveSpeed;
            }
            if (GAME.Keyboard.keyIsDown("s")) {
                this.velocity.y += frameMoveSpeed;
            }

            // only shoot in one direction at a time, so we use if else

            // had to change to shoot function to update the elapsed time every frame

            if (GAME.Keyboard.keyIsDown("left_arrow") || GAME.Keyboard.keyIsDown("j")) {
                this.shoot(VECTOR.LEFT);
            }
            else if (GAME.Keyboard.keyIsDown("right_arrow") || GAME.Keyboard.keyIsDown("l")) {
                this.shoot(VECTOR.RIGHT);
            }
            else if (GAME.Keyboard.keyIsDown("up_arrow") || GAME.Keyboard.keyIsDown("i")) {
                this.shoot(VECTOR.UP);
            }
            else if (GAME.Keyboard.keyIsDown("down_arrow") || GAME.Keyboard.keyIsDown("k")) {
                this.shoot(VECTOR.DOWN);
            }
            else {
                this.shoot(null);
            }
        
            this.velocity = VECTOR.multiplyScalar(this.velocity, (GAME.elapsedTime / 1000));
            this.position = VECTOR.add(this.position, this.velocity);
        }

        this.shoot = function(direction) {
            if(! isShooting && direction != null){
                lastShotTime = +(new Date());
                isShooting = true;
                // spawn a bullet with the direction 
                GAME.bullets.push(new Bullet({playerTarget:this.playerTarget,direction:direction, position: this.position}));
                this.shotsFired++;

                var shootAudio = RESOURCES.get(GAMECONFIG.players[this.playerTarget].fx.shoot.name);
                shootAudio.load();
                shootAudio.volume = 0.3;
                shootAudio.play();
            }
            else {
                lastShotElapsedTime += GAME.elapsedTime;
                if(lastShotElapsedTime > shootInterval){
                    isShooting = false;
                    lastShotElapsedTime = 0.0;
                }
            }
        }
        
        // Calculate percentage of run bar to show
        this.runBar = function() {
          
          var runBar = {};
          
          // Run bar color
          runBar.containerColor = "rgb(24, 24, 24)";
          runBar.color = "rgb(24, 240, 204)";
          
          // Run bar coordinates
          runBar.x = 25;
          runBar.y = 30;
          //runBar.w = 100;
          runBar.h = 10;
          
          // If sprinting, decrease the bar
          if(isSprinting){
            runBarPercent = 100 - parseInt((sprintElapsedTime / sprintTime) * 100);
          }
          
          // ElseIf not sprinting, but still within sprintTime
          else if(nonSprintElapsedTime + sprintLength < sprintTime && lastSprintTime > 0){
            runBarPercent = 100 - (parseInt(((nonSprintElapsedTime + sprintLength) / sprintTime) * 100));
          }
          
          // Elseif not sprinting, 
          else if(nonSprintElapsedTime > 0 && nonSprintElapsedTime < sprintInterval && lastSprintTime > 0){
            runBarPercent = parseInt((nonSprintElapsedTime / sprintInterval) * 100);
          }
          
          
          runBar.w = runBarPercent
          
          // Display Run bar container
          GAME.renderingContext.fillStyle = runBar.containerColor;
          GAME.renderingContext.fillRect(runBar.x-1,runBar.y-1,102,runBar.h+2); 
          
          // Display Run bar
          GAME.renderingContext.fillStyle = runBar.color;
          GAME.renderingContext.fillRect(runBar.x,runBar.y,runBar.w,runBar.h); 
          
        }

        this.draw = function (rc) {
            var r = this.toRect();
            rc.save();
            var image = this.sprite.render();
            rc.drawImage(image, r.x, r.y, r.w, r.h);
            //rc.fillStyle = "rgb(255, 0, 255)";
            //rc.fillRect(r.x, r.y, r.w, r.h);
            rc.restore();
        }
*/        
    }// end of player