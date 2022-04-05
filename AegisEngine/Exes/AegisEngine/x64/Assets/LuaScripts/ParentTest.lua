local NAME = "ParentTest";
local table = {};
function table.GetNew(entity, params)
	local component = Aegis.CreateComponent(NAME, entity);
	local data = component.data;
	local transform = entity.transform;
	local funcs = component.funcs;
	local external = {};
	local parent = {};
	local entity = component.entity;
	
    data.time = 0;
    data.parented = false;

	function Init()
		external = component.external;
        parent = external.parent.entity;
	end;
	function Update(deltaTime)
		if data.time > 2 then
			if data.parented == false then
                print(entity:GetName() .. ": " .. transform.localEulerAngles.x .. " " .. transform.localEulerAngles.y .. " " .. transform.localEulerAngles.z);
				entity:SetParent(parent);
                print(entity:GetName() .. ": " .. transform.localEulerAngles.x .. " " .. transform.localEulerAngles.y .. " " .. transform.localEulerAngles.z);
                data.parented = true;
			else
                print(entity:GetName() .. ": " .. transform.localEulerAngles.x .. " " .. transform.localEulerAngles.y .. " " .. transform.localEulerAngles.z);
				entity:SetParent(nil);
                print(entity:GetName() .. ": " .. transform.localEulerAngles.x .. " " .. transform.localEulerAngles.y .. " " .. transform.localEulerAngles.z);
                data.parented = false;
			end;
			data.time = data.time - 5;
		end;
		data.time = data.time + deltaTime;

        --print each position of entity
        --print(entity:GetName() .. ": " .. transform.position.x .. " " .. transform.position.y .. " " .. transform.position.z);
	end;
    
    funcs.init = Init;
    funcs.update = Update;
    return component;
end;

return table;
