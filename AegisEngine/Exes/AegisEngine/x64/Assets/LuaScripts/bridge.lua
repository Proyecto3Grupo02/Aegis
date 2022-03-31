testEntity = ECS.CreateEntity(currentScene);
testEntity:setName("Entidad de prueba");
currentScene:AddEntity(testEntity);

local myMath = require "myMath";
print(myMath.subtwo(myMath.addtwo(2+3, 1), 1));

local M = { }

M.two = 2;
M.hola = "hola"

local component = ECS.CreateComponent();
--print(component:componentData());

component.update = (function(a) print("Update from lua " .. a) end);
ECS.TestAegisComponent(component);