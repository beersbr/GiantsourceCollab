RESOURCES = (function(){
        var resources = {};

        var resourcesCount = 0,
            resourcesLoaded = 0,
            resourcesAreLoaded = false,
            resourceCache = {};

        resources.TYPES = {};
        resources.TYPES.AUDIO = 1;
        resources.TYPES.IMAGE = 2;

        function onResourceLoaded(event, type, key){
            resourcesLoaded += 1;

            if (type == "audio") {
                $(resourceCache[key]).unbind("loadeddata");
                resourceCache[key] = new audio(resourceCache[key]);
            }
             
            return true;
        }

        // this is just an audio tag wrapper that creates a bunch of the same audio tag 
        // so we can play more than one instance of that sound at a time... actually we can 
        // play maxChannels many :D
        function audio(audio) {
            this.maxChannels = 20;
            this.channels = [];

            this.audio = audio;
            this.currentChannel = 0;
            this.volume = 1;

            for (var i = 0; i < this.maxChannels; i++) {
                this.channels[i] = new Audio();
                this.preload = true;
                this.channels[i].src = this.audio.src;
            }

            this.play = function () {

                this.channels[this.currentChannel].load();
                this.channels[this.currentChannel].volume = this.volume;
                this.channels[this.currentChannel].play();
                this.currentChannel = (this.currentChannel + 1) % this.maxChannels;
            }

            this.load = function () { }
        }

        resources.isLoaded = function(){
            if(resourcesCount == resourcesLoaded){
                resourcesAreLoaded = true;
            }
            return resourcesAreLoaded;
        }

        resources.markResource = function(resourceKey, resourcePath, resourceType){
            var object = null;

           
            switch(resourceType){
                case resources.TYPES.IMAGE: 
                    resourcesCount += 1;
                    object = new Image();
                    object.src = resourcePath;
                    resourceCache[resourceKey] = object;
                    object.onload = onResourceLoaded;

                    break;
                case resources.TYPES.AUDIO:
                    resourcesCount += 1;
                    object = new Audio();
                    object.preload = true;
                    
                    resourceCache[resourceKey] = object;
                    $(object).on("loadeddata", function (event) { onResourceLoaded(event, "audio", resourceKey); });
                    object.src = resourcePath;
                    object.load();
                    o = object;
                    break;
            }

        }

        resources.get = function(resourceKey){
            if(!resourcesAreLoaded)
                throw "Resources aren't loaded yet :(";

            return resourceCache[resourceKey];
        }

        return resources;
    })();