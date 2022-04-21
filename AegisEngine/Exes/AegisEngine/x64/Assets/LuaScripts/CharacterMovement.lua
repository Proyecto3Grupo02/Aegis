local NAME = "CharacterMovement";
local table = {};
function table.GetNew(entity, params)
	local component = Aegis.CreateComponent(NAME, entity);
	local data = component.data;
	local transform = entity.transform;
    local funcs = component.funcs;

    function Init() end;
	function Update(deltaTime) 
        local rigidbody = component.entity:GetComponent("Rigidbody").type;
        --local transform = component.entity.transform;
        -- MOVE CHARACTER:
        if  Input:AnyKeyIsDown() then -- GENERIC CHECK BEFORE CHECKING INDIVIDUAL KEY ==> NECESSARY
            if Input:IsKeyDown("w") then
                --if (meshRenderer.visible == true) then
                --  meshRenderer.visible = false;
                --else
                --  meshRenderer.visible = true;
                --end;
                print("Tecla W");
                
                rigidbody:AddForce(Aegis.Maths.Vector3(0,10, 0));
                
            end;
            if Input:IsKeyDown("a") then
                print("Tecla A");
            end;
            if Input:IsKeyDown("s") then
                print("Tecla S");
            end;
            if Input:IsKeyDown("d") then
                print("Tecla D");
            end;
        end        

    end;
	function LateUpdate(deltaTime) end;
	function FixedUpdate() 
        
    end;
	function OnCollision(other) end;
	function OnTrigger(other) end;

	funcs.init = Init;
    funcs.update = Update;
    funcs.fixedUpdate = FixedUpdate;
	return component;
end;
return table;