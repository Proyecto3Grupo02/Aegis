local NAME = "Utils";
local funcs = {};
funcs.ParseEntity = function(object)
	local entity = Aegis.CreateEntity(currentScene, funcs.ParseVector3(object.position));
	entity.transform.scale = funcs.ParseVector3(object.scale, 1);
	entity.transform.localEulerAngles = funcs.ParseVector3(object.rotation);
	entity:SetName(object.name);
	for i, v in ipairs(object.components) do
		local componentType = require(v.type);
		if componentType == true then
			print("Component " .. v.type .. " is not found");
		else
			local component = componentType.GetNew(entity, v.data);
			entity:AddComponent(component);
			if (v.overrideData == nil or v.overrideData == true) and v.data ~= nil then
				funcs.CopyComponentData(v.data, component.data, component.name);
			end;
		end;
	end;
	currentScene:AddEntity(entity);
	return entity;
end;

--from: component
--to: data
funcs.CopyComponentData = function(from, to, componentName)
-- if key in to is not in from, dont copy and print warning
    for k, v in pairs(to) do
        if from[k] == nil then
            print("Warning: " .. k .. " is not found in " .. componentName .. " data");
        else
            -- Intended for debug
            --print("Copying " .. k .. "(" .. from[k] ..")" .. " from " .. componentName .. " to data" .. "(" .. to[k] .. ")");
            to[k] = from[k];
        end
    end
end


funcs.ParseVector3 = function(vec3, default)
	if default == nil then
		default = 0;
	end;
	if vec3 == nil then
		return Aegis.Maths.Vector3(default, default, default);
	end;
	local x = vec3.x or default;
	local y = vec3.y or default;
	local z = vec3.z or default;
	return Aegis.Maths.Vector3(x, y, z);
end;
funcs.ResolveDependencies = function(scene, entities)
	for i, v in ipairs(scene) do
		for p, cmp in ipairs(v.components or {}) do
			if v.type == "Entity" and cmp.dependencies ~= nil then
                print("Solving dependencies for " .. v.name .. "\n");
				for key, dependencie in ipairs(cmp.dependencies) do
					local entity = entities[dependencie.entity];
					if entity == nil then
						print("Entity " .. dependencie.entity .. " is not found, could not resolve dependency for " .. v.name);
					else
						local localComponent = entities[v.name]:GetComponent(cmp.type);

                        localComponent.external= {};
                        localComponent.external[entity:GetName()] = {};
                        localComponent.external[entity:GetName()].entity = entity; 

						for j, componentName in ipairs(dependencie.components) do
							local component = entity:GetComponent(componentName);
							if component == nil then
								print("Component " .. componentName .. " wasn't found in " .. dependencie.entity .. ", could not resolve dependency for " .. v.name);
							else
                                print("Inyecting " .. componentName .. " from " .. dependencie.entity .. " into " .. cmp.type);
								localComponent.external[entity:GetName()][componentName] = component;
                                print("Dependency solved correctly\n");
							end;
						end;
					end;
				end;
			end;
		end;
	end;
end;
local entities = {};
funcs.ParseSceneObject = function(object)
	if object.type == "Entity" then
		local entity = funcs.ParseEntity(object);
		entities[entity:GetName()] = entity;
	end;
end;
funcs.ParseScene = function(scene)
	for i, v in ipairs(scene) do
		local object = funcs.ParseSceneObject(v);
	end;
	funcs.ResolveDependencies(scene, entities);
end;
return funcs;
