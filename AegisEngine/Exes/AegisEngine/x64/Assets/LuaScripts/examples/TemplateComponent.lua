local NAME = "YourComponentName";
local table = {};
function table.GetNew(entity, params)
	local component = Aegis.CreateComponent();
	component.name = NAME;

    local data = {};
    component.data = data;
    
	if params ~= nil then
		data = params;
	else
		data.time = 0;
	end;

    
	function update(deltaTime) end;
	function lateUpdate() end;
	function lateUpdate(deltaTime) end;
	function fixedUpdate() end;
	function onCollision(other) end;
	function onTrigger(other) end;
	
	local funcs = {};
    funcs.update = update;
	component:setCallbacks(funcs);

	return component;
end;
return table;
