-- this is the main file for the game, 
--it's called from c++ just before starting the game loop

local utility = require "Utils";
local testScene = require "TerrainScene";
--local testScene = require "RotScene"; --"TerrainScene";
math.randomseed(os.time());
utility.ParseScene(testScene);