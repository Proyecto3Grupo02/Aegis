-- utility methods to use in other scripts

local NAME="Utils"

local funcs = {}

funcs.ParseEntity = function(object)
    local entity = Aegis.CreateEntity(currentScene, funcs.ParsePosition(object.position));
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
    return entity;
end

-- position may contain x, y, z or a mix of them, create Vector3 from it, changing nil to 0
funcs.ParsePosition = function(position)
    if position == nil then
        return Aegis.Maths.Vector(0, 0, 0);
    end
    local x = position.x or 0;
    local y = position.y or 0;
    local z = position.z or 0;
    return Aegis.Maths.Vector3(x, y, z);
end

funcs.ResolveDependencies = function(scene, entities)
    -- read the scene again but this time solving dependencies for each entity component in components
    -- entities entity have a dependencies field with an array of table that contains entity = "EntityName" and componentArray = { "ComponentName", "ComponentName" }
    -- to find entity name we can acceess entities table directly using entity.name

    for i, v in ipairs(scene) do
    
    if v.type == "Entity" and v.dependencies ~= nil then

        for key, dependencie in ipairs(v.dependencies) do
            local entity = entities[dependencie.entity];
            if entity == nil then
                print("Entity " .. dependencie.entity .. " is not found, could not resolve dependencie for entity " .. v.name);
            else
                for j, component in ipairs(dependencie.components) do
                    local component = entity:GetComponent(component);
                    if component == nil then
                        print("Component " .. component .. " is not found, could not resolve dependencie for entity " .. v.name);
                    else
                        local localEntity = entities[v.name];
                        localEntity.external[entity:GetName()] = {};

                        --insert entity and component into external table
                        localEntity.external[entity:GetName()]["entity"] = entity;
                        localEntity.external[entity:GetName()][component:GetName()] = component;
                    end
                end
            end
        end

    end

    end

end

local entities = {}
funcs.ParseSceneObject = function(object)

    -- check if type is Entity, if it is create entity and parse components
    -- if a component is not found it will print a message to console, but 
    -- execution will continue
    if object.type == "Entity" then
       local entity = funcs.ParseEntity(object);
       entities[entity:GetName()] = entity;
    end
end

funcs.ParseScene = function(scene)
    for i, v in ipairs(scene) do
        local object = funcs.ParseSceneObject(v);
    end
    --funcs.ResolveDependencies(scene, entities);
end

return funcs;