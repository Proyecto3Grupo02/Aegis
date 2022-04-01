-- utility methods to use in other scripts

local NAME="Utils"

local ParseEntity = function(object)

    -- check if type is Entity, if it is create entity and parse components
    -- if a component is not found it will print a message to console, but 
    -- execution will continue
    if object.type == "Entity" then
        local entity = Aegis.CreateEntity(currentScene);
        entity:SetName(object.name);
        for i, v in ipairs(object.components) do
            local componentType = require(v.type);
            if componentType == true then
                print("Component " .. v.type .. " is not found");
            else
                local component = componentType.GetNew(entity, v.data);
                entity:AddComponent(component);
                if (v.overrideData == nil or v.overrideData == true) and v.data ~= nil then
                    component.data = v.data;
                end
            end
        end
        currentScene:AddEntity(entity);
    end
end

local table = 
{
    ParseEntity = ParseEntity,
    ParseScene = function(scene)
        for i, v in ipairs(scene) do
            ParseEntity(v);
        end
    end,
}

return table;