testEntity = ECS.CreateEntity(currentScene);
testEntity:setName("Entidad de prueba");
currentScene:AddEntity(testEntity);

--package.path = package.path .. ";../Assets/LuaScripts/?.lua"
local myMath = require "myMath";
print(myMath.addtwo(2+3, 1));