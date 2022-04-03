local NAME = "YourComponentName";
local table = {};
function table.GetNew(entity, params)
	local component = Aegis.CreateComponent(NAME, entity);
	local data = component.data;
	local transform = entity.transform;
    local funcs = component.funcs;

    function Init() end;
	function Update(deltaTime) end;
	function LateUpdate(deltaTime) end;
	function FixedUpdate() end;
	function OnCollision(other) end;
	function OnTrigger(other) end;

	funcs.init = Init;
    funcs.update = Update;
	return component;
end;
return table;
