local NAME = "DestroyTest";
local table = {};
function table.GetNew(entity, params)
	local component = Aegis.CreateComponent(NAME, entity);
	local data = component.data;
	local transform = entity.transform;
    local funcs = component.funcs;
    data.child = "Undefined";
    data.callback = true

    function Init() 
        --data.child:SetParent(entity);
    end;
	function Update(deltaTime) 
        local meshRenderer = component.entity:GetComponent("Renderer").type;
        -- change visibility when pressing v
    if  Input:AnyKeyWasPressed() then -- GENERIC CHECK BEFORE CHECKING INDIVIDUAL KEY ==> NECESSARY
        if Input:KeyWasPressed("v") and data.callback then
            --data.child:SetParent(entity);
            print("DestroyTest: " .. component.entity:GetName());
           entity:Destroy();
        elseif Input:KeyWasPressed("o") then
            data.child:SetParent(entity);
            print(data.child:GetName() .. " is now child of " .. component.entity:GetName());
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