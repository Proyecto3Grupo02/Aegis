-- this is the main file for the game, 
--it's called from c++ just before starting the game loop

local utility = require "Utils";
_G["utils"] = utility; -- Esto hay que moverlo luego a otro lado

local testScene = require "TerrainScene";
--local testScene = require "RotScene"; --"TerrainScene";
math.randomseed(os.time());
SceneManager:LoadScene(testScene);