local NAME = "UITextTest";
local table = {};
function table.GetNew(entity, params)
	local component = Aegis.CreateComponent(NAME, entity);
	local data = component.data;
	local transform = entity.transform;
    local funcs = component.funcs;
    data.text = "nil"

    function Init() end;
	function Update(deltaTime) 
    if  Input:AnyKeyWasPressed() then -- GENERIC CHECK BEFORE CHECKING INDIVIDUAL KEY ==> NECESSARY
        if Input:KeyWasPressed("l") then
            print(data.text:GetName());
            local textNum = data.text:GetText();
            textNum = textNum + 1;
            data.text:SetText(textNum);
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