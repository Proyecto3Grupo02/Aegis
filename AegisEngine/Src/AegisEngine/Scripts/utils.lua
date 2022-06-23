local funcs = {};

funcs.ParseEntity = function(object)
	local scene = SceneManager:GetCurrentScene();
	local entity = Aegis.CreateEntity(scene, funcs.ParseVector3(object.position));
	entity.transform.scale = funcs.ParseVector3(object.scale, 1);
	entity.transform.localEulerAngles = funcs.ParseVector3(object.rotation, 0);
	
	entity:SetName(object.name);
	funcs.AddComponents(entity, object.components);
	scene:AddEntity(entity);
	return entity;
end;

funcs.AddComponents = function(entity, components)
	if components == nil or entity == nil then
		return;
	end;


	for i, v in ipairs(components) do
		local componentType = require(v.type);
		if componentType == true then
			print("Component " .. v.type .. " is not found");
		else
			local component = componentType.GetNew(entity, v.data or {});
			entity:AddComponent(component);

			local native = componentType.isNative;
			if ((v.overrideData == nil or v.overrideData == true) and v.data ~= nil) and native == nil then
				funcs.CopyComponentData(v.data, component.data, component.name, entity:GetName());
			end;
		end;
	end;
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

funcs.HasDependencies = function(data)
	if data == nil then
		print("Error: data is nil");
		return false;
	end;
	for i, v in pairs(data) do
		if type(v) == "string" and v:sub(1, 1) == "@" then
			return true;
		end;
		return false;
	end;
end;

-- Splits a string into a table of strings using a delimiter (default is :)
funcs.Split = function(str, sep)
	local sep, fields = sep or ":", {}
	local pattern = string.format("([^%s]+)", sep)
	str:gsub(pattern, function(c) fields[#fields+1] = c end)
	return fields
end;

-- Receives a string with the form "Entity.Component" where Component is optional and returns 
-- the entity or component found, if any
funcs.SearchEntityOrComponent = function(entities,data)
	local splitStr = funcs.Split(data, ".");
	local entityName = splitStr[1];
	--print("Seaching for entity: " .. entityName);
	local entity = entities[entityName]
	if entity == nil then
		print("Searcher: Entity " .. entityName .. " not found");
		return nil;
	end;

	-- If splitStr has more than 1 element, then we are searching for a component
	if #splitStr == 1 then
		--print("Entity found: " .. entityName);
		return entity;
	end;

	-- If there is a point, then we want to search for a component in that entity
	-- Substring data from first point to second point or end of string
	local component = entity:GetComponent(splitStr[2]);

	if component == nil then
		print("Searcher: Component " .. splitStr[2] .. " not found");
		return nil;
	else
		return component;
	end;
end;

funcs.ResolveDependencies = function(scene, entities)
	for i, v in ipairs(scene) do
		if v.type == "Entity" then
			for p, data in ipairs(v.components or {}) do
				if data.data ~= nil and funcs.HasDependencies(data.data) then
					print("Solving dependencies for " .. v.name .. ":");
					local resolvedCorrectly = true;
					local entityData = entities[v.name]:GetComponent(data.type).data;
					for key, cmpData in pairs(data.data) do
						if entityData[key] ~= nil then
						
						if type(cmpData) == "string" and cmpData:sub(1, 1) == "@" then
							local dependencyData = funcs.SearchEntityOrComponent(entities, cmpData:sub(2));
							if dependencyData == nil then
								print("* Error: Data " .. cmpData:sub(2) .. " was not found, field is untouched");
								resolvedCorrectly = false;
							else
								print("* Inyecting " ..  cmpData:sub(2) .. " into " .. data.type .. "." .. key);
								entityData[key] = dependencyData;
							end;
						end;
					else
						print("* Error: " .. key .. " is not a field of " .. data.type .. ".data, " .. key .. " wasn't was copied");
						resolvedCorrectly = false;
					end;
					end;
					print();
					if resolvedCorrectly == false then
						print("* Could not resolve dependencies for " .. v.name);
					else
						print("* Dependency solved correctly");
					end;
					print("-------------------");
				end;
			end;
		elseif  v.type == "UI" then
			local uiData = entities[v.data.name].data;
			for p, data in pairs(v.data.uiData or {}) do
				if  type(data) == "string" and data:sub(1, 1) == "@" then
					print("UI: Solving dependencies for " .. v.data.name .. ":");
					resolvedCorrectly = true;
						local dependencyData = funcs.SearchEntityOrComponent(entities, data:sub(2));
						if dependencyData == nil then
							print("* Error: Data " .. data:sub(2) .. " was not found, field is untouched");
							resolvedCorrectly = false;
						else
							print("* Inyecting " ..  data:sub(2) .. " into " .. v.data.type);
							uiData[p] = dependencyData;
						end;
					print();
					if resolvedCorrectly == false then
						print("* Could not resolve dependencies for " .. v.name);
					else
						print("* Dependency solved correctly");
					end;
					print("-------------------");
				end;
			end;
		end;
	end;
end;

funcs.TreatSpecialCase = function(object)
	local possibleEntity = _G[object.type];
	print("Found entity: " .. object.type);
	if possibleEntity ~= nil then
		possibleEntity.transform.position = funcs.ParseVector3(object.position);
		possibleEntity.transform.scale = funcs.ParseVector3(object.scale, 1);
		possibleEntity.transform.localEulerAngles = funcs.ParseVector3(object.rotation, 0);

		funcs.AddComponents(possibleEntity, object.components);
		return possibleEntity;
	end;
end;

local entities = {};
funcs.ParseSceneObject = function(object)
	if object.type == "Entity" then
		local entity = funcs.ParseEntity(object);
		entities[entity:GetName()] = entity;
	elseif object.type == "UI" then
		local uiObject = funcs.ParseUI(object);
		entities[object.data.name] = uiObject.type;
	else
		local entity = funcs.TreatSpecialCase(object);
		if entity ~= nil then
			entities[entity:GetName()] = entity;
		end;
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

funcs.ParseUI = function (object)
	return UISystem:CreateUIElem(object.data);
end

return funcs;