  function glCanvas(args) {
    if(args == undefined) args = {};
    
    var gl;

    var x = args.x || 0.0;
    var y = args.y || 0.0;
    var z = args.z || -5.0;
        
    var xRot = args.xRot || 0;
    var xSpeed = args.xSpeed || 0;
    var yRot = args.yRot || 0;
    var ySpeed = args.ySpeed || 0;
    var zRot = args.zRot || 0;
    var zSpeed = args.zSpeed || 0;

    var shaderProgram;
    
    var mvMatrix = mat4.create();    
    var pMatrix = mat4.create();
    var mvMatrixStack = [];
    
    var lastTime = 0;
  
    this.initGL = function(canvas) {
        try {
            gl = canvas.getContext("experimental-webgl");
            gl.viewportWidth = canvas.width;
            gl.viewportHeight = canvas.height;
        } catch (e) {
        }
        if (!gl) {
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
          shader = gl.createShader(gl.FRAGMENT_SHADER);
      } else if (shaderScript.type == "x-shader/x-vertex") {
          shader = gl.createShader(gl.VERTEX_SHADER);
      } else {
          return null;
      }
  
      gl.shaderSource(shader, str);
      gl.compileShader(shader);
  
      if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
          alert(gl.getShaderInfoLog(shader));
          return null;
      }
  
      return shader;
    };
    
    this.initShaders = function() {
        var fragmentShader = getShader(gl, "shader-fs");
        var vertexShader = getShader(gl, "shader-vs");
    
        shaderProgram = gl.createProgram();
        gl.attachShader(shaderProgram, vertexShader);
        gl.attachShader(shaderProgram, fragmentShader);
        gl.linkProgram(shaderProgram);
    
        if (!gl.getProgramParameter(shaderProgram, gl.LINK_STATUS)) {
            alert("Could not initialise shaders");
        }
    
        gl.useProgram(shaderProgram);
    
        shaderProgram.vertexPositionAttribute = gl.getAttribLocation(shaderProgram, "aVertexPosition");
        gl.enableVertexAttribArray(shaderProgram.vertexPositionAttribute);
    
        shaderProgram.textureCoordAttribute = gl.getAttribLocation(shaderProgram, "aTextureCoord");
        gl.enableVertexAttribArray(shaderProgram.textureCoordAttribute);
    
        shaderProgram.pMatrixUniform = gl.getUniformLocation(shaderProgram, "uPMatrix");
        shaderProgram.mvMatrixUniform = gl.getUniformLocation(shaderProgram, "uMVMatrix");
        shaderProgram.samplerUniform = gl.getUniformLocation(shaderProgram, "uSampler");
    }; 

    this.handleLoadedTexture = function(texture) {
        
        
        //gl.blendFunc(gl.SRC_ALPHA, gl.ONE_MINUS_SRC_ALPHA);
        //gl.enable(gl.BLEND);
        gl.bindTexture(gl.TEXTURE_2D, texture);
        
        // Set the parameters so we can render any size image.
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, gl.CLAMP_TO_EDGE);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);
        
        // Upload the image into the texture.
        gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, texture.image);
        gl.bindTexture(gl.TEXTURE_2D, null);    
        
    };

    this.setMatrixUniforms = function() {
      gl.uniformMatrix4fv(shaderProgram.pMatrixUniform, false, pMatrix);
      gl.uniformMatrix4fv(shaderProgram.mvMatrixUniform, false, mvMatrix);
    };


    this.mvPushMatrix = function() {
        var copy = mat4.create();
        mat4.set(mvMatrix, copy);
        mvMatrixStack.push(copy);
    };
    
    this.mvPopMatrix = function() {
        if (mvMatrixStack.length == 0) {
            throw "Invalid popMatrix!";
        }
        mvMatrix = mvMatrixStack.pop();
    };

    this.drawScene = function() {
        gl.viewport(0, 0, gl.viewportWidth, gl.viewportHeight);
        gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
    
        mat4.perspective(45, gl.viewportWidth / gl.viewportHeight, 0.1, 100.0, pMatrix);
    
        mat4.identity(mvMatrix);
    
        mat4.translate(mvMatrix, [0.0, 0.0, z]);
    
        mat4.rotate(mvMatrix, degToRad(xRot), [1, 0, 0]);
        mat4.rotate(mvMatrix, degToRad(yRot), [0, 1, 0]);
    
        gl.bindBuffer(gl.ARRAY_BUFFER, cubeVertexPositionBuffer);
        gl.vertexAttribPointer(shaderProgram.vertexPositionAttribute, cubeVertexPositionBuffer.itemSize, gl.FLOAT, false, 0, 0);
    
        gl.bindBuffer(gl.ARRAY_BUFFER, cubeVertexTextureCoordBuffer);
        gl.vertexAttribPointer(shaderProgram.textureCoordAttribute, cubeVertexTextureCoordBuffer.itemSize, gl.FLOAT, false, 0, 0);
    
    
        gl.activeTexture(gl.TEXTURE0);
        gl.bindTexture(gl.TEXTURE_2D, cubeTextures.uCubeTexture);
        gl.uniform1i(shaderProgram.samplerUniform, 0);
    
        gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, uCubeVertexIndexBuffer);
        setMatrixUniforms();
        gl.drawElements(gl.TRIANGLES, uCubeVertexIndexBuffer.numItems, gl.UNSIGNED_SHORT, 0);
    
        gl.activeTexture(gl.TEXTURE0);
        gl.bindTexture(gl.TEXTURE_2D, cubeTextures.dCubeTexture);
        gl.uniform1i(shaderProgram.samplerUniform, 0);
            
        gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, dCubeVertexIndexBuffer);
        setMatrixUniforms();
        gl.drawElements(gl.TRIANGLES, dCubeVertexIndexBuffer.numItems, gl.UNSIGNED_SHORT, 0);
        
        gl.activeTexture(gl.TEXTURE0);
        gl.bindTexture(gl.TEXTURE_2D, cubeTextures.nCubeTexture);
        gl.uniform1i(shaderProgram.samplerUniform, 0);
        
        gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, nCubeVertexIndexBuffer);
        setMatrixUniforms();
        gl.drawElements(gl.TRIANGLES, nCubeVertexIndexBuffer.numItems, gl.UNSIGNED_SHORT, 0);
        
        gl.activeTexture(gl.TEXTURE0);
        gl.bindTexture(gl.TEXTURE_2D, cubeTextures.sCubeTexture);
        gl.uniform1i(shaderProgram.samplerUniform, 0);
        
        gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, sCubeVertexIndexBuffer);
        setMatrixUniforms();
        gl.drawElements(gl.TRIANGLES, sCubeVertexIndexBuffer.numItems, gl.UNSIGNED_SHORT, 0);
        
        gl.activeTexture(gl.TEXTURE0);
        gl.bindTexture(gl.TEXTURE_2D, cubeTextures.eCubeTexture);
        gl.uniform1i(shaderProgram.samplerUniform, 0);
        
        gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, eCubeVertexIndexBuffer);
        setMatrixUniforms();
        gl.drawElements(gl.TRIANGLES, eCubeVertexIndexBuffer.numItems, gl.UNSIGNED_SHORT, 0);
        
        gl.activeTexture(gl.TEXTURE0);
        gl.bindTexture(gl.TEXTURE_2D, cubeTextures.wCubeTexture);
        gl.uniform1i(shaderProgram.samplerUniform, 0);
        
        gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, wCubeVertexIndexBuffer);
        setMatrixUniforms();
        gl.drawElements(gl.TRIANGLES, wCubeVertexIndexBuffer.numItems, gl.UNSIGNED_SHORT, 0);
    }
    
    
    this.animate = function() {
        var timeNow = new Date().getTime();
        if (lastTime != 0) {
            var elapsed = timeNow - lastTime;
    
            //xRot += (xSpeed * elapsed) / 1000.0;
            xRot = x;
            //yRot += (ySpeed * elapsed) / 1000.0;
            yRot = y;
        }
        lastTime = timeNow;
    }
    
    
    this.tick = function() {
        handleKeys();
        drawScene();
        animate();
        requestAnimFrame(tick);
    }
    
    
    
    this.webGLStart = function() {
        var canvas = document.getElementById("cubeEditor");
        initGL(canvas);
        initShaders();
        initBuffers();
        initTextures();
    
        gl.clearColor(0.0, 0.0, 0.0, 1.0);
        gl.enable(gl.DEPTH_TEST);
    
        document.onkeydown = handleKeyDown;
        document.onkeyup = handleKeyUp;
    
        tick();
    }
  
  }
  
  
  function glCube(args) {
    
    var cubeVertexPositionBuffer,
        cubeVertexTextureCoordBuffer,
        uCubeVertexIndexBuffer,
        dCubeVertexIndexBuffer,
        nCubeVertexIndexBuffer,
        sCubeVertexIndexBuffer,
        eCubeVertexIndexBuffer,
        wCubeVertexIndexBuffer; 
    
    

    var cubeTextures = {
        uCubeTexture: null,
        dCubeTexture: null,
        nCubeTexture: null,
        sCubeTexture: null,
        eCubeTexture: null,
        wCubeTexture: null
    };

    this.initBuffers = function() {
        cubeVertexPositionBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ARRAY_BUFFER, cubeVertexPositionBuffer);
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
        gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);
        cubeVertexPositionBuffer.itemSize = 3;
        cubeVertexPositionBuffer.numItems = 24;
    
        cubeVertexTextureCoordBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ARRAY_BUFFER, cubeVertexTextureCoordBuffer);
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
        gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(textureCoords), gl.STATIC_DRAW);
        cubeVertexTextureCoordBuffer.itemSize = 2;
        cubeVertexTextureCoordBuffer.numItems = 24;
        
        
        // Up face
        uCubeVertexIndexBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, uCubeVertexIndexBuffer);
        var uCubeVertexIndices = [0, 1, 2,      0, 2, 3];
        gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(uCubeVertexIndices), gl.STATIC_DRAW);
        uCubeVertexIndexBuffer.itemSize = 1;
        uCubeVertexIndexBuffer.numItems = 6;
        
        // Down face
        dCubeVertexIndexBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, dCubeVertexIndexBuffer);
        var dCubeVertexIndices = [4, 5, 6,      4, 6, 7];
        gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(dCubeVertexIndices), gl.STATIC_DRAW);
        dCubeVertexIndexBuffer.itemSize = 1;
        dCubeVertexIndexBuffer.numItems = 6;
        
        // North face
        nCubeVertexIndexBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, nCubeVertexIndexBuffer);
        var nCubeVertexIndices = [8, 9, 10,     8, 10, 11];
        gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(nCubeVertexIndices), gl.STATIC_DRAW);
        nCubeVertexIndexBuffer.itemSize = 1;
        nCubeVertexIndexBuffer.numItems = 6;
        
        // South face
        sCubeVertexIndexBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, sCubeVertexIndexBuffer);
        var sCubeVertexIndices = [12, 13, 14,   12, 14, 15];
        gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(sCubeVertexIndices), gl.STATIC_DRAW);
        sCubeVertexIndexBuffer.itemSize = 1;
        sCubeVertexIndexBuffer.numItems = 6;
        
        // East face
        eCubeVertexIndexBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, eCubeVertexIndexBuffer);
        var eCubeVertexIndices = [16, 17, 18,   16, 18, 19];
        gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(eCubeVertexIndices), gl.STATIC_DRAW);
        eCubeVertexIndexBuffer.itemSize = 1;
        eCubeVertexIndexBuffer.numItems = 6;
        
        // West face
        wCubeVertexIndexBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, wCubeVertexIndexBuffer);
        var wCubeVertexIndices = [20, 21, 22,   20, 22, 23];gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(wCubeVertexIndices), gl.STATIC_DRAW);
        wCubeVertexIndexBuffer.itemSize = 1;
        wCubeVertexIndexBuffer.numItems = 6;
        
    };
    
    this.initTextures = function() {
      var newImage = new Image();
      
      // Loop through all the sides of the cube and create an image for it
      for(var i in cubeTextures) {
        var texture = gl.createTexture();
        texture.image = newImage;
        cubeTextures[i] = texture;
      }
      
      newImage.onload = function () {
        for(var k in cubeTextures) handleLoadedTexture(cubeTextures[k])
      }
      
      // Set the image with the default transparent texture
      newImage.src = "tile-transparent.png";
    };

    this.changeTexture = function(face,_fileName) {
     
      var newImage = new Image(); 
      var faceName = "";
      var texture = gl.createTexture();
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
        handleLoadedTexture(cubeTextures[faceName]);
      }
      
      newImage.src = _fileName;
    };
    
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




