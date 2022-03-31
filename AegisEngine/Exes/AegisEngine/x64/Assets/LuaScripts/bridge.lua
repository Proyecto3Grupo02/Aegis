local testComponent = require "testComponent"
local cT = testComponent.GetNew();
cT.data.two = 9;
--ECS.TestAegisComponent(cT);

testEntity = ECS.CreateEntity(currentScene);
testEntity:setName("Entidad de prueba");
testEntity:AddComponent(cT);
currentScene:AddEntity(testEntity);