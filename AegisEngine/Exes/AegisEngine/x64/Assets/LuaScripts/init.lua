-- this is the main file for the game, 
--it's called from c++ just before starting the game loop

local utility = require "Utils";
local testScene = require "PhysicsScene";
math.randomseed(os.time());
utility.ParseScene(testScene);