local NAME = "YourComponentName";
local table = {};
function table.GetNew(entity, params)
	local component = Aegis.CreateComponent(NAME);
	local data = component.data;
	local transform = entity.transform;
    local funcs = component.funcs;

	if params ~= nil then
		data = params;
	else
		data.time = 0;
	end;

    function Init() end;
	function Update(deltaTime) end;
	function LateUpdate(deltaTime) end;
	function FixedUpdate() end;
	function OnCollision(other) end;
	function OnTrigger(other) end;
	
    funcs.update = Update;
	return component;
end;
return table;
