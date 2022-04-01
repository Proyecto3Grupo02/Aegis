-- utility methods to use in other scripts

local NAME="Utils"

local parseEntity = function(object)

    -- check if type is Entity, if it is create entity and parse components
    if object.type == "Entity" then
        local entity = Aegis.CreateEntity(currentScene);
        entity:setName(object.name);
        for i, v in ipairs(object.components) do
            local component = require(v.type).GetNew(entity, v.data);
            entity:AddComponent(component);
            if v.overrideData == nil or v.overrideData == true then
            component.data = v.data;
            end
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