-- this is the main file for the game, 
--it's called from c++ just before starting the game loop

-- No soy capz de portarlo asi que lo he reescrito 
-- aqui de forma TEMPORAL para poder probar al menos como va
Vector3Lerp = function(start_value, end_value, t)
    return Aegis.Maths.Vector3(
        start_value.x + (end_value.x - start_value.x) * t,
        start_value.y + (end_value.y - start_value.y) * t,
        start_value.z + (end_value.z - start_value.z) * t
    );
end

local utility = require "Utils";
local testScene = require "RotScene";
math.randomseed(os.time());
utility.ParseScene(testScene);