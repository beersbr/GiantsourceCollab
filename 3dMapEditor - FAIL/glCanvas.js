  function glCanvas(args) {
    if(args == undefined) args = {};
    
    this.gl = null;

    this.x = args.x || 0.0;
    this.y = args.y || 0.0;
    this.z = args.z || -5.0;
        
    this.xRot = args.xRot || 0;
    this.xSpeed = args.xSpeed || 0;
    this.yRot = args.yRot || 0;
    this.ySpeed = args.ySpeed || 0;
    this.zRot = args.zRot || 0;
    this.zSpeed = args.zSpeed || 0;

    this.shaderProgram = null;
    
    this.mvMatrix = mat4.create();
    this.pMatrix = mat4.create();
    this.mvMatrixStack = [];
    
    this.cubes = [];
    
    var lastTime = 0;
  
    this.initGL = function(canvas) {
        try {
            this.gl = canvas.getContext("experimental-webgl");
            this.gl.viewportWidth = canvas.width;
            this.gl.viewportHeight = canvas.height;
        } catch (e) {
        }
        if (!this.gl) {
            alert("Could not initialise WebGL, sorry :-(");
        }
    };
  
    this.getShader = function(gl, id) {
      var shaderScript = document.getElementById(id);
      if (!shaderScript) {
          return null;
      }
  
      var str = "";
      var k = shaderScript.firstChild;
      while (k) {
          if (k.nodeType == 3) {
              str += k.textContent;
          }
          k = k.nextSibling;
      }
  
      var shader;
      if (shaderScript.type == "x-shader/x-fragment") {
          shader = this.gl.createShader(this.gl.FRAGMENT_SHADER);
      } else if (shaderScript.type == "x-shader/x-vertex") {
          shader = this.gl.createShader(this.gl.VERTEX_SHADER);
      } else {
          return null;
      }
  
      this.gl.shaderSource(shader, str);
      this.gl.compileShader(shader);
  
      if (!this.gl.getShaderParameter(shader, this.gl.COMPILE_STATUS)) {
          alert(this.gl.getShaderInfoLog(shader));
          return null;
      }
  
      return shader;
    };
    
    this.initShaders = function() {
        var fragmentShader = this.getShader(this.gl, "shader-fs");
        var vertexShader = this.getShader(this.gl, "shader-vs");
    
        this.shaderProgram = this.gl.createProgram();
        this.gl.attachShader(this.shaderProgram, vertexShader);
        this.gl.attachShader(this.shaderProgram, fragmentShader);
        this.gl.linkProgram(this.shaderProgram);
    
        if (!this.gl.getProgramParameter(this.shaderProgram, this.gl.LINK_STATUS)) {
            alert("Could not initialise shaders");
        }
    
        this.gl.useProgram(this.shaderProgram);
    
        this.shaderProgram.vertexPositionAttribute = this.gl.getAttribLocation(this.shaderProgram, "aVertexPosition");
        this.gl.enableVertexAttribArray(this.shaderProgram.vertexPositionAttribute);
    
        this.shaderProgram.textureCoordAttribute = this.gl.getAttribLocation(this.shaderProgram, "aTextureCoord");
        this.gl.enableVertexAttribArray(this.shaderProgram.textureCoordAttribute);
    
        this.shaderProgram.pMatrixUniform = this.gl.getUniformLocation(this.shaderProgram, "uPMatrix");
        this.shaderProgram.mvMatrixUniform = this.gl.getUniformLocation(this.shaderProgram, "uMVMatrix");
        this.shaderProgram.samplerUniform = this.gl.getUniformLocation(this.shaderProgram, "uSampler");
    }; 

    this.handleLoadedTexture = function(texture) {
        
        //this.gl.blendFunc(this.gl.SRC_ALPHA, this.gl.ONE_MINUS_SRC_ALPHA);
        //this.gl.enable(this.gl.BLEND);
        this.gl.bindTexture(this.gl.TEXTURE_2D, texture);
        
        // Set the parameters so we can render any size image.
        this.gl.texParameteri(this.gl.TEXTURE_2D, this.gl.TEXTURE_WRAP_S, this.gl.CLAMP_TO_EDGE);
        this.gl.texParameteri(this.gl.TEXTURE_2D, this.gl.TEXTURE_WRAP_T, this.gl.CLAMP_TO_EDGE);
        this.gl.texParameteri(this.gl.TEXTURE_2D, this.gl.TEXTURE_MIN_FILTER, this.gl.NEAREST);
        this.gl.texParameteri(this.gl.TEXTURE_2D, this.gl.TEXTURE_MAG_FILTER, this.gl.NEAREST);
        
        // Upload the image into the texture.
        this.gl.texImage2D(this.gl.TEXTURE_2D, 0, this.gl.RGBA, this.gl.RGBA, this.gl.UNSIGNED_BYTE, texture.image);
        this.gl.bindTexture(this.gl.TEXTURE_2D, null);    
        
    };

    this.setMatrixUniforms = function() {
      this.gl.uniformMatrix4fv(this.shaderProgram.pMatrixUniform, false, this.pMatrix);
      this.gl.uniformMatrix4fv(this.shaderProgram.mvMatrixUniform, false, this.mvMatrix);
    };


    this.mvPushMatrix = function() {
        var copy = mat4.create();
        mat4.set(this.mvMatrix, copy);
        this.mvMatrixStack.push(copy);
    };
    
    this.mvPopMatrix = function() {
        if (this.mvMatrixStack.length == 0) {
            throw "Invalid popMatrix!";
        }
        this.mvMatrix = this.mvMatrixStack.pop();
    };

    this.drawScene = function() {
        this.gl.viewport(0, 0, this.gl.viewportWidth, this.gl.viewportHeight);
        this.gl.clear(this.gl.COLOR_BUFFER_BIT | this.gl.DEPTH_BUFFER_BIT);
    
        mat4.perspective(45, this.gl.viewportWidth / this.gl.viewportHeight, 0.1, 100.0, this.pMatrix);
    
        mat4.identity(this.mvMatrix);
    
        mat4.translate(this.mvMatrix, [this.x, this.y, this.z]);
    
        mat4.rotate(this.mvMatrix, degToRad(this.xRot), [1, 0, 0]);
        mat4.rotate(this.mvMatrix, degToRad(this.yRot), [0, 1, 0]);
        mat4.rotate(this.mvMatrix, degToRad(this.zRot), [0, 0, 1]);
    
        
        // Loop through each cube
        for(var c in this.cubes) {
          
          this.cubes[c].drawScene();
          //this.drawCube(this.cubes[c]);
        }
        
    }
    
    this.animate = function() {
      /*
        var timeNow = new Date().getTime();
        if (this.lastTime != 0) {
            var elapsed = timeNow - this.lastTime;
    
            //xRot += (xSpeed * elapsed) / 1000.0;
            this.xRot = x;
            //yRot += (ySpeed * elapsed) / 1000.0;
            this.yRot = y;
        }
        this.lastTime = timeNow;
        */
    }
    
    
    this.tick = function() {
        //tick = this.tick;
        //requestAnimFrame(function(){tick();});
        handleKeys();
        this.drawScene();
        this.animate();
    }
    
    
    
    this.webGLStart = function() {
        var canvas = document.getElementById("cubeEditor");
        this.initGL(canvas);
        this.initShaders();
        
        this.cubes.push(new glCube({"canvas":this}));
        this.cubes[0].initBuffers();
        this.cubes[0].initTextures();
    
        this.gl.clearColor(0.0, 0.0, 0.0, 1.0);
        this.gl.enable(this.gl.DEPTH_TEST);
    
        document.onkeydown = handleKeyDown;
        document.onkeyup = handleKeyUp;
    
        this.tick();
    }
  
  }
  
  
  function glCube(args) {
    
    var canvas = args.canvas || null;
    this.cubeVertexPositionBuffer = null;
    this.cubeVertexTextureCoordBuffer = null;
    this.uCubeVertexIndexBuffer = null;
    this.dCubeVertexIndexBuffer = null;
    this.nCubeVertexIndexBuffer = null;
    this.sCubeVertexIndexBuffer = null;
    this.eCubeVertexIndexBuffer = null;
    this.wCubeVertexIndexBuffer = null; 
    

    var cubeTextures = {
        uCubeTexture: null,
        dCubeTexture: null,
        nCubeTexture: null,
        sCubeTexture: null,
        eCubeTexture: null,
        wCubeTexture: null
    };

    this.initBuffers = function() {
        
        this.cubeVertexPositionBuffer = canvas.gl.createBuffer();
        canvas.gl.bindBuffer(canvas.gl.ARRAY_BUFFER, this.cubeVertexPositionBuffer);
        var vertices = [
            // Up face
            -1.0, -1.0,  1.0,
             1.0, -1.0,  1.0,
             1.0,  1.0,  1.0,
            -1.0,  1.0,  1.0,
    
            // Down face
            -1.0, -1.0, -1.0,
            -1.0,  1.0, -1.0,
             1.0,  1.0, -1.0,
             1.0, -1.0, -1.0,
    
            // North face
            -1.0,  1.0, -1.0,
            -1.0,  1.0,  1.0,
             1.0,  1.0,  1.0,
             1.0,  1.0, -1.0,
    
            // South face
            -1.0, -1.0, -1.0,
             1.0, -1.0, -1.0,
             1.0, -1.0,  1.0,
            -1.0, -1.0,  1.0,
    
            // East face
             1.0, -1.0, -1.0,
             1.0,  1.0, -1.0,
             1.0,  1.0,  1.0,
             1.0, -1.0,  1.0,
    
            // West face
            -1.0, -1.0, -1.0,
            -1.0, -1.0,  1.0,
            -1.0,  1.0,  1.0,
            -1.0,  1.0, -1.0,
        ];
        canvas.gl.bufferData(canvas.gl.ARRAY_BUFFER, new Float32Array(vertices), canvas.gl.STATIC_DRAW);
        this.cubeVertexPositionBuffer.itemSize = 3;
        this.cubeVertexPositionBuffer.numItems = 24;
    
        this.cubeVertexTextureCoordBuffer = canvas.gl.createBuffer();
        canvas.gl.bindBuffer(canvas.gl.ARRAY_BUFFER, this.cubeVertexTextureCoordBuffer);
        var textureCoords = [
            // Up face
            0.0, 0.0,
            1.0, 0.0,
            1.0, 1.0,
            0.0, 1.0,
    
            // Down face
            1.0, 0.0,
            1.0, 1.0,
            0.0, 1.0,
            0.0, 0.0,
    
            // North face
            0.0, 1.0,
            0.0, 0.0,
            1.0, 0.0,
            1.0, 1.0,
    
            // South face
            1.0, 1.0,
            0.0, 1.0,
            0.0, 0.0,
            1.0, 0.0,
    
            // East face
            1.0, 0.0,
            1.0, 1.0,
            0.0, 1.0,
            0.0, 0.0,
    
            // West face
            0.0, 0.0,
            1.0, 0.0,
            1.0, 1.0,
            0.0, 1.0,
        ];
        canvas.gl.bufferData(canvas.gl.ARRAY_BUFFER, new Float32Array(textureCoords), canvas.gl.STATIC_DRAW);
        this.cubeVertexTextureCoordBuffer.itemSize = 2;
        this.cubeVertexTextureCoordBuffer.numItems = 24;
        
        
        // Up face
        this.uCubeVertexIndexBuffer = canvas.gl.createBuffer();
        canvas.gl.bindBuffer(canvas.gl.ELEMENT_ARRAY_BUFFER, this.uCubeVertexIndexBuffer);
        var uCubeVertexIndices = [0, 1, 2,      0, 2, 3];
        canvas.gl.bufferData(canvas.gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(uCubeVertexIndices), canvas.gl.STATIC_DRAW);
        this.uCubeVertexIndexBuffer.itemSize = 1;
        this.uCubeVertexIndexBuffer.numItems = 6;
        
        // Down face
        this.dCubeVertexIndexBuffer = canvas.gl.createBuffer();
        canvas.gl.bindBuffer(canvas.gl.ELEMENT_ARRAY_BUFFER, this.dCubeVertexIndexBuffer);
        var dCubeVertexIndices = [4, 5, 6,      4, 6, 7];
        canvas.gl.bufferData(canvas.gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(dCubeVertexIndices), canvas.gl.STATIC_DRAW);
        this.dCubeVertexIndexBuffer.itemSize = 1;
        this.dCubeVertexIndexBuffer.numItems = 6;
        
        // North face
        this.nCubeVertexIndexBuffer = canvas.gl.createBuffer();
        canvas.gl.bindBuffer(canvas.gl.ELEMENT_ARRAY_BUFFER, this.nCubeVertexIndexBuffer);
        var nCubeVertexIndices = [8, 9, 10,     8, 10, 11];
        canvas.gl.bufferData(canvas.gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(nCubeVertexIndices), canvas.gl.STATIC_DRAW);
        this.nCubeVertexIndexBuffer.itemSize = 1;
        this.nCubeVertexIndexBuffer.numItems = 6;
        
        // South face
        this.sCubeVertexIndexBuffer = canvas.gl.createBuffer();
        canvas.gl.bindBuffer(canvas.gl.ELEMENT_ARRAY_BUFFER, this.sCubeVertexIndexBuffer);
        var sCubeVertexIndices = [12, 13, 14,   12, 14, 15];
        canvas.gl.bufferData(canvas.gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(sCubeVertexIndices), canvas.gl.STATIC_DRAW);
        this.sCubeVertexIndexBuffer.itemSize = 1;
        this.sCubeVertexIndexBuffer.numItems = 6;
        
        // East face
        this.eCubeVertexIndexBuffer = canvas.gl.createBuffer();
        canvas.gl.bindBuffer(canvas.gl.ELEMENT_ARRAY_BUFFER,this. eCubeVertexIndexBuffer);
        var eCubeVertexIndices = [16, 17, 18,   16, 18, 19];
        canvas.gl.bufferData(canvas.gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(eCubeVertexIndices), canvas.gl.STATIC_DRAW);
        this.eCubeVertexIndexBuffer.itemSize = 1;
        this.eCubeVertexIndexBuffer.numItems = 6;
        
        // West face
        this.wCubeVertexIndexBuffer = canvas.gl.createBuffer();
        canvas.gl.bindBuffer(canvas.gl.ELEMENT_ARRAY_BUFFER, this.wCubeVertexIndexBuffer);
        var wCubeVertexIndices = [20, 21, 22,   20, 22, 23];canvas.gl.bufferData(canvas.gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(wCubeVertexIndices), canvas.gl.STATIC_DRAW);
        this.wCubeVertexIndexBuffer.itemSize = 1;
        this.wCubeVertexIndexBuffer.numItems = 6;
        
    };
    
    this.initTextures = function() {
      var newImage = new Image();
      
      // Loop through all the sides of the cube and create an image for it
      for(var i in cubeTextures) {
        var texture = canvas.gl.createTexture();
        texture.image = newImage;
        cubeTextures[i] = texture;
      }
      
      newImage.onload = function () {        
        for(var k in cubeTextures) {
          canvas.handleLoadedTexture(cubeTextures[k]);
        }
      }
      
      // Set the image with the default transparent texture
      newImage.src = "tile-transparent.png";
    };

    this.changeTexture = function(face,_fileName) {
     
      var newImage = new Image(); 
      var faceName = "";
      var texture = this.canvas.gl.createTexture();
      texture.image = newImage;
      
     
      switch(face) {
        case "u": case "up": 
          faceName = "uCubeTexture";
          break;
        
        case "d": case "down": 
          faceName = "dCubeTexture";
          break;
        
        case "n": case "north": 
          faceName = "nCubeTexture";
          break;
        
        case "s": case "south": 
          faceName = "sCubeTexture";
          break;
        
        case "e": case "east": 
          faceName = "eCubeTexture";
          break;
        
        case "w": case "west": 
          faceName = "wCubeTexture";
          break;
        
      } 
      
      cubeTextures[faceName] = texture;
      
      newImage.onload = function () {
        this.handleLoadedTexture(cubeTextures[faceName]);
      }
      
      newImage.src = _fileName;
    };


    this.drawScene = function() {
    
        canvas.gl.bindBuffer(canvas.gl.ARRAY_BUFFER, this.cubeVertexPositionBuffer);
        canvas.gl.vertexAttribPointer(canvas.shaderProgram.vertexPositionAttribute, this.cubeVertexPositionBuffer.itemSize, canvas.gl.FLOAT, false, 0, 0);
    
        canvas.gl.bindBuffer(canvas.gl.ARRAY_BUFFER, this.cubeVertexTextureCoordBuffer);
        canvas.gl.vertexAttribPointer(canvas.shaderProgram.textureCoordAttribute, this.cubeVertexTextureCoordBuffer.itemSize, canvas.gl.FLOAT, false, 0, 0);

    
        canvas.gl.activeTexture(canvas.gl.TEXTURE0);
        canvas.gl.bindTexture(canvas.gl.TEXTURE_2D, cubeTextures.uCubeTexture);
        canvas.gl.uniform1i(canvas.shaderProgram.samplerUniform, 0);
    
        canvas.gl.bindBuffer(canvas.gl.ELEMENT_ARRAY_BUFFER, this.uCubeVertexIndexBuffer);
        canvas.setMatrixUniforms();
        canvas.gl.drawElements(canvas.gl.TRIANGLES, this.uCubeVertexIndexBuffer.numItems, canvas.gl.UNSIGNED_SHORT, 0);
    
        canvas.gl.activeTexture(canvas.gl.TEXTURE0);
        canvas.gl.bindTexture(canvas.gl.TEXTURE_2D, cubeTextures.dCubeTexture);
        canvas.gl.uniform1i(canvas.shaderProgram.samplerUniform, 0);
            
        canvas.gl.bindBuffer(canvas.gl.ELEMENT_ARRAY_BUFFER, this.dCubeVertexIndexBuffer);
        canvas.setMatrixUniforms();
        canvas.gl.drawElements(canvas.gl.TRIANGLES, this.dCubeVertexIndexBuffer.numItems, canvas.gl.UNSIGNED_SHORT, 0);
        
        canvas.gl.activeTexture(canvas.gl.TEXTURE0);
        canvas.gl.bindTexture(canvas.gl.TEXTURE_2D, cubeTextures.nCubeTexture);
        canvas.gl.uniform1i(canvas.shaderProgram.samplerUniform, 0);
        
        canvas.gl.bindBuffer(canvas.gl.ELEMENT_ARRAY_BUFFER, this.nCubeVertexIndexBuffer);
        canvas.setMatrixUniforms();
        canvas.gl.drawElements(canvas.gl.TRIANGLES, this.nCubeVertexIndexBuffer.numItems, canvas.gl.UNSIGNED_SHORT, 0);
        
        canvas.gl.activeTexture(canvas.gl.TEXTURE0);
        canvas.gl.bindTexture(canvas.gl.TEXTURE_2D, cubeTextures.sCubeTexture);
        canvas.gl.uniform1i(canvas.shaderProgram.samplerUniform, 0);
        
        canvas.gl.bindBuffer(canvas.gl.ELEMENT_ARRAY_BUFFER, this.sCubeVertexIndexBuffer);
        canvas.setMatrixUniforms();
        canvas.gl.drawElements(canvas.gl.TRIANGLES, this.sCubeVertexIndexBuffer.numItems, canvas.gl.UNSIGNED_SHORT, 0);
        
        canvas.gl.activeTexture(canvas.gl.TEXTURE0);
        canvas.gl.bindTexture(canvas.gl.TEXTURE_2D, cubeTextures.eCubeTexture);
        canvas.gl.uniform1i(canvas.shaderProgram.samplerUniform, 0);
        
        canvas.gl.bindBuffer(canvas.gl.ELEMENT_ARRAY_BUFFER, this.eCubeVertexIndexBuffer);
        canvas.setMatrixUniforms();
        canvas.gl.drawElements(canvas.gl.TRIANGLES, this.eCubeVertexIndexBuffer.numItems, canvas.gl.UNSIGNED_SHORT, 0);
        
        canvas.gl.activeTexture(canvas.gl.TEXTURE0);
        canvas.gl.bindTexture(canvas.gl.TEXTURE_2D, cubeTextures.wCubeTexture);
        canvas.gl.uniform1i(canvas.shaderProgram.samplerUniform, 0);
        
        canvas.gl.bindBuffer(canvas.gl.ELEMENT_ARRAY_BUFFER, this.wCubeVertexIndexBuffer);
        canvas.setMatrixUniforms();
        canvas.gl.drawElements(canvas.gl.TRIANGLES, this.wCubeVertexIndexBuffer.numItems, canvas.gl.UNSIGNED_SHORT, 0);
    }
    
  }
  
  
  
  /******* THIS SHOULD BE IN A UTILS FILE ******/


function degToRad(degrees) {
    return degrees * Math.PI / 180;
}




/******* keyboard.js SHOULLD TAKE CARE OF THESE *******/
var currentlyPressedKeys = {};

function handleKeyDown(event) {
    currentlyPressedKeys[event.keyCode] = true;
    
}

function handleKeyUp(event) {
    currentlyPressedKeys[event.keyCode] = false;
    
    // Left Arrow
    if (event.keyCode == "37") {
      
      // Shift key
      if(event.shiftKey) { }
      else y -= 45;
    }   
    
    // Up Arrow
    if (event.keyCode == "38") {
      
      // Shift key
      if(event.shiftKey) { }
      else x += 45;
    }   
    
    // Right Arrow
    if (event.keyCode == "39") {
      
      // Shift key
      if(event.shiftKey) { }
      else y += 45;
    }   
    
    // Down Arrow
    if (event.keyCode == "40") {
      
      // Shift key
      if(event.shiftKey) { }
      else x -= 45;
    }    
}

// This will run continually long as the key is pressed down
function handleKeys() {
    if (currentlyPressedKeys[33]) {
        // Page Up
        z -= 0.05;
    }
    if (currentlyPressedKeys[34]) {
        // Page Down
        z += 0.05;
    }

}




