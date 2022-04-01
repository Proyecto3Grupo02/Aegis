testEntity = ECS.CreateEntity(currentScene);

local testComponent = require "TestComponent"
local cT = testComponent.GetNew();

local rnd = ECS.CreateRenderer(testEntity, "fish.mesh");

testEntity:setName("Entidad de prueba");
testEntity:AddComponent(cT);
testEntity:AddComponent(rnd);
currentScene:AddEntity(testEntity);

--cT.data.update(0);
