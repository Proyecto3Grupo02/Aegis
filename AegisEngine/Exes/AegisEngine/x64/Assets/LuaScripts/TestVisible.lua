local NAME = "TestVisible";
local table = {};
function table.GetNew(entity, params)
	local component = Aegis.CreateComponent(NAME, entity);
	local data = component.data;
	local transform = entity.transform;
    local funcs = component.funcs;

    function Init() end;
	function Update(deltaTime) 
        local meshRenderer = component.entity:GetComponent("Renderer").type;
        -- change visibility when pressing v
    if  Input:AnyKeyWasPressed() then -- GENERIC CHECK BEFORE CHECKING INDIVIDUAL KEY ==> NECESSARY
        if Input:KeyWasPressed("v") then
            if (meshRenderer.visible == true) then
                meshRenderer.visible = false;
            else
                meshRenderer.visible = true;
            end;
        end;
    end        

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