local NAME = "DestroyTest";
local table = {};
function table.GetNew(entity, params)
	local component = Aegis.CreateComponent(NAME, entity);
	local data = component.data;
	local transform = entity.transform;
    local funcs = component.funcs;
    data.child = "Undefined";

    function Init() end;
	function Update(deltaTime) 
        local meshRenderer = component.entity:GetComponent("Renderer").type;
        -- change visibility when pressing v
    if  Input:AnyKeyWasPressed() then -- GENERIC CHECK BEFORE CHECKING INDIVIDUAL KEY ==> NECESSARY
        if Input:KeyWasPressed("v") then
            --data.child:SetParent(entity);
            print("DestroyTest: " .. component.entity:GetName());
           entity:Destroy();
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