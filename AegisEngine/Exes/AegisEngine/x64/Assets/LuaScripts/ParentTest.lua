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
	if  Input:AnyKeyWasPressed() then
		if Input:KeyWasPressed("p") then
			if data.parented == false then
				entity:SetParent(parent);
                data.parented = true;
			else
				entity:SetParent(nil);
                data.parented = false;
			end;
			data.time = data.time - 5;
		end;
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
