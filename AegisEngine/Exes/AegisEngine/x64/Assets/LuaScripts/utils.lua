local NAME = "Utils";
local funcs = {};
funcs.ParseEntity = function(object)
	local entity = Aegis.CreateEntity(currentScene, funcs.ParseVector3(object.position));
	entity.transform.scale = funcs.ParseVector3(object.scale, 1);
	
	if object.rotation ~= nil then
		entity.transform.localEulerAngles = funcs.ParseVector3(object.rotation);
	end
	
	entity:SetName(object.name);
	for i, v in ipairs(object.components) do
		local componentType = require(v.type);
		if componentType == true then
			print("Component " .. v.type .. " is not found");
		else
			local component = componentType.GetNew(entity, v.data);
			entity:AddComponent(component);
			if (v.overrideData == nil or v.overrideData == true) and v.data ~= nil then
				funcs.CopyComponentData(v.data, component.data, component.name, object.name);
			end;
		end;
	end;
	currentScene:AddEntity(entity);
	return entity;
end;

--from: component
--to: data
funcs.CopyComponentData = function(from, to, componentName, entityName)
-- if key in to is not in from, dont copy and print warning
    for k, v in pairs(from) do
        if to[k] == nil then
            bool = false;   
            print("Error: " .. k .. " is not a field of " .. componentName .. ".data, " .. k .. " wasn't copied (" .. entityName ..")");
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
                print("Solving dependencies for " .. v.name .. ":\n");
                local resolvedCorrectly = true;
				for key, dependency in ipairs(cmp.dependencies) do
					local entity = entities[dependency.entity];
					local name = dependency.name;
                    print("--Solving dependencies from " .. dependency.entity .. ":");
					if entity == nil then
                        resolvedCorrectly = false;
						print("----Entity " .. dependency.entity .. " wasn't found, dependency could not be resolved");
					elseif name == nil then
                        resolvedCorrectly = false;
						print("----No name found, dependency could not be resolved");
					else
						local localComponent = entities[v.name]:GetComponent(cmp.type);

                        localComponent.external.inited = true;
                        localComponent.external[name] = {};
                        localComponent.external[name].entity = entity; 

						for j, componentName in ipairs(dependency.components or {}) do
							local component = entity:GetComponent(componentName);
							if component == nil then
                                resolvedCorrectly = false;
								print("----Component " .. componentName .. " wasn't found in " .. dependency.entity .. ", dependency could not be resolved");
							else
                                print("----Inyecting " .. componentName .. " from " .. dependency.entity .. " into " .. cmp.type);
								localComponent.external[name][componentName] = component;
							end;
						end;
					end;
				end;

                print();
                if resolvedCorrectly == false then
                    print("Could not resolve dependencies for " .. v.name);
                else 
                    print("Dependency solved correctly");
                end;
                print("-------------------");
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
    print("Creating Scene Objects");
    print("-------------------");
	for i, v in ipairs(scene) do
		local object = funcs.ParseSceneObject(v);
	end;
    print("\nResolving dependencies:");
    print("-------------------");
	funcs.ResolveDependencies(scene, entities);
end;
return funcs;
