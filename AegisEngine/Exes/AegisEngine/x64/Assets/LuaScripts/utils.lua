local NAME="Utils"

local parseEntity = function(object)

    -- check if type is Entity, if it is create entity and parse components
    if object.type == "Entity" then
        local entity = ECS.CreateEntity(currentScene);
        entity:setName(object.name);
        for i, v in ipairs(object.components) do
            local component = require(v.type).GetNew(entity, v.data);
            entity:AddComponent(component);
            component.data = v.data;
        end
        currentScene:AddEntity(entity);
    end
end

local table = 
{
    parseEntity = parseEntity,
    parseScene = function(scene)
        for i, v in pairs(scene) do
            parseEntity(v);
        end
    end,
}

return table;