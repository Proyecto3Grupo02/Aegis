local NAME = "Rod";
local table = {};
function table.GetNew(entity, params)
	local component = Aegis.CreateComponent(NAME, entity);
    local renderer;
    local funcs = component.funcs;

    function Init()
        renderer = component.entity:GetComponent("Renderer").type;
        renderer.visible=false;        
     end;

	function Update(deltaTime)
        if Input:KeyWasPressed("Space")then
            renderer.visible = not renderer.visible;
        end;   
    end;

    function LateUpdate(deltaTime) end;

	function FixedUpdate() end;

	function OnCollision(other) end;
	function OnTrigger(other) end;

	funcs.init = Init;
    funcs.update = Update;
	return component;
end;
return table;