local NAME = "CameraTest";
local table = {};
function table.GetNew(entity, params)
	local component = Aegis.CreateComponent(NAME, entity);
	local data = component.data;
	local transform = entity.transform;
    local funcs = component.funcs;
    data.child = "Undefined";

    function Init() 
        --entity:GetComponent("Camera");
        print("Entity name " .. entity:GetName());
    end;
	function Update(deltaTime)
        -- Move position of transform using awsd keys witha  value of 1, save the value and normalize before applying to transform
        local move = Aegis.Maths.Vector3(0, 0, 0);
        if Input:IsKeyDown("i") then
            move = move + Aegis.Maths.Vector3(0, 0, -1);
        end;
        if Input:IsKeyDown("j") then
            move = move + Aegis.Maths.Vector3(-1, 0, 0);
        end;
        if Input:IsKeyDown("k") then
            move = move + Aegis.Maths.Vector3(0, 0, 1);
        end;
        if Input:IsKeyDown("l") then
            move = move + Aegis.Maths.Vector3(1, 0, 0);
        end;

        move:Normalize();
        transform.position = transform.position + move * deltaTime * 10;
    end        

    function LateUpdate(deltaTime) end;
	function FixedUpdate() end;
	function OnCollision(other) end;
	function OnTrigger(other) end;

	funcs.init = Init;
    funcs.update = Update;
	return component;
end;
return table;