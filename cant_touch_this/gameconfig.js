GAMECONFIG = (function(){
        var config = {}

        var settings = {};
        var players = {};
        var levels = {};
        var screens = {};
        var fx = {};
        var enemies = {};
        var images = {};

        config.init = function(configObj) {
            console.log(configObj);
            config.settings = configObj.settings;
            config.enemies = configObj.enemies;
            config.players = configObj.players;
            config.fx = configObj.resources.gameFx;
            config.images = configObj.resources.gameImages;
            config.levels = configObj.resources.levels;
            config.screens = configObj.resources.screens;

        }

        config.loadLevelResources = function(level) {

                RESOURCES.markResource(GAMECONFIG.levels[level].name, "./"+GAMECONFIG.settings.resourcePath+"/"+GAMECONFIG.levels[level].src, RESOURCES.TYPES.IMAGE);
                
                GAMECONFIG.loadPlayers(level);
                GAMECONFIG.loadEnemies(level);
                GAMECONFIG.loadGameFX(level);
                GAMECONFIG.loadGameImages(level);
                GAMECONFIG.loadGameScreens(level);

        }
         config.loadPlayers = function(level) {
                
                for (var key in GAMECONFIG.players) {
                   
                   var obj = GAMECONFIG.players[key];
                  // console.log(obj);
                   if (!obj.loaded) {

                        if (obj.level) {
                            if (obj.level  == 'all' || parseInt(obj.level) == parseInt(level)) {
                                RESOURCES.markResource(obj.name, "./"+GAMECONFIG.settings.resourcePath+"/"+obj.sprite.src, RESOURCES.TYPES.IMAGE);
                                GAMECONFIG.players[key].loaded = true;
                                config.loadObjFX(obj);
                            } 
                        } else {

                                RESOURCES.markResource(obj.name, "./"+GAMECONFIG.settings.resourcePath+"/"+obj.sprite.src, RESOURCES.TYPES.IMAGE);
                                GAMECONFIG.players[key].loaded = true;
                                config.loadObjFX(obj);
                        }

                   } 
                 
                }


        }

        config.checkObj = function() {



        }

        config.loadObjFX = function(obj) {

            for (var fxKey in obj.fx) {

                    var fx = obj.fx[fxKey];
                    //console.log(fx);
                    RESOURCES.markResource(fx.name, "./"+GAMECONFIG.settings.resourcePath+"/"+fx.src, RESOURCES.TYPES.AUDIO);       
            }

        }

        config.loadEnemies = function(level) {
        
            for (var key in GAMECONFIG.enemies) {
               
               var obj = GAMECONFIG.enemies[key];
           // console.log(obj);
               if (!obj.loaded) {

                     if (obj.level) {
                            if (obj.level  == 'all' || parseInt(obj.level) == parseInt(level)) {

                                RESOURCES.markResource(obj.name, "./"+GAMECONFIG.settings.resourcePath+"/"+obj.sprite.src, RESOURCES.TYPES.IMAGE);

                                GAMECONFIG.enemies[key].loaded = true;
                                config.loadObjFX(obj);

                            } 
                    } else {

                        RESOURCES.markResource(obj.name, "./"+GAMECONFIG.settings.resourcePath+"/"+obj.sprite.src, RESOURCES.TYPES.IMAGE);
                        GAMECONFIG.enemies[key].loaded = true;
                        config.loadObjFX(obj);
                     
                    }

               } 
             
            }
           
        }


        config.loadGameImages = function(level) {

                 for (var key in GAMECONFIG.images) {
               
                   var obj = GAMECONFIG.images[key];
                   //console.log(obj);
                   if (!obj.loaded) {

                        if (obj.level) {
                            if (obj.level  == 'all' || parseInt(obj.level) == parseInt(level)) {

                                RESOURCES.markResource(obj.name, "./"+GAMECONFIG.settings.resourcePath+"/"+obj.src, RESOURCES.TYPES.IMAGE);
                                GAMECONFIG.images[key].loaded = true;
                            } 
                        } else {

                           RESOURCES.markResource(obj.name, "./"+GAMECONFIG.settings.resourcePath+"/"+obj.src, RESOURCES.TYPES.IMAGE);
                           GAMECONFIG.images[key].loaded = true;
                       }
                   } 
                 
                }

        }



        config.loadGameScreens = function(level) {

                for (var key in GAMECONFIG.screens) {
               
                   var obj = GAMECONFIG.screens[key];
                  // console.log(obj);
                   if (!obj.loaded) {

                        if (obj.level) {
                            if (obj.level  == 'all' || parseInt(obj.level) == parseInt(level)) {

                                RESOURCES.markResource(obj.name, "./"+GAMECONFIG.settings.resourcePath+"/"+obj.src, RESOURCES.TYPES.IMAGE);
                                GAMECONFIG.screens[key].loaded = true;
                            }    
                        }else {

                            RESOURCES.markResource(obj.name, "./"+GAMECONFIG.settings.resourcePath+"/"+obj.src, RESOURCES.TYPES.IMAGE);
                            GAMECONFIG.screens[key].loaded = true;
                       }
                   } 
                 
                }


        }

        config.loadGameFX = function(level) {

                for (var key in GAMECONFIG.fx) {
               
                   var obj = GAMECONFIG.fx[key];
                   
                   if (!obj.loaded) {

                         if (obj.level) {
                            if (obj.level  == 'all' || parseInt(obj.level) == parseInt(level)) {

                                RESOURCES.markResource(obj.name, "./"+GAMECONFIG.settings.resourcePath+"/"+obj.src, RESOURCES.TYPES.AUDIO);
                                GAMECONFIG.fx[key].loaded = true;
                            }
                        } else {

                         RESOURCES.markResource(obj.name,"./"+GAMECONFIG.settings.resourcePath+"/"+obj.src, RESOURCES.TYPES.AUDIO);
                         GAMECONFIG.fx[key].loaded = true;
                       }

                   } 
                 
                }

        }

        config.getLevels = function() {



        }
        

        return config;
    })();