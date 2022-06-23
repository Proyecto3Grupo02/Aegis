local NAME = "ParentTest";
local table = {};
function table.GetNew(entity, params)
	local component = Aegis.CreateComponent(NAME, entity);
	local data = component.data;
	local transform = entity.transform;
	local funcs = component.funcs;
	local parent = {};
	local entity = component.entity;

	data.time = 13;
	data.parented = false;
	data.parent = "undefined";
	data.parentRender = "null";

	function Init()
		print("ParentMat is " .. data.parentRender.data.material);
	end;

	function Update(deltaTime)
		if parent ~= "undefined" then
			if Input:AnyKeyWasPressed() then
				if Input:KeyWasPressed("p") then
					if data.parented == false then
						entity:SetParent(data.parent);
						data.parented = true;
					else
						entity:SetParent(nil);
						data.parented = false;
					end;
					data.time = data.time - 5;
				end;
			end;
			data.time = data.time + deltaTime;
		end;
	end;
	funcs.init = Init;
	funcs.update = Update;
	return component;
end;
return table;
