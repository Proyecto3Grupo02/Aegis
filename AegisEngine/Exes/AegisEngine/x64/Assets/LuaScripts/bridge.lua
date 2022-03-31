local testComponent = require "testComponent"
local cT = testComponent.GetNew();

testEntity = ECS.CreateEntity(currentScene);
testEntity:setName("Entidad de prueba");
testEntity:AddComponent(cT);
currentScene:AddEntity(testEntity);

--cT.data.update(0);
