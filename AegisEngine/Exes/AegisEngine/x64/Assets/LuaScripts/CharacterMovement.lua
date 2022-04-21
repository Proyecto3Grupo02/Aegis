local NAME = "CharacterMovement";
local table = {};
function table.GetNew(entity, params)
	local component = Aegis.CreateComponent(NAME, entity);
	local data = component.data;
	local transform = entity.transform;
    local funcs = component.funcs;
    local rigidbody = component.entity:GetComponent("Rigidbody").type;
    data.initPos = transform.position;

    function Init() end;
	function Update(deltaTime) 
        if  Input:AnyKeyWasPressed() then -- GENERIC CHECK BEFORE CHECKING INDIVIDUAL KEY ==> NECESSARY
            if Input:KeyWasPressed("s") then
                rigidbody.position = data.initPos;
            end;
            if Input:KeyWasPressed("a") then
               print("Transform: x: " .. transform.position.x .." y: " .. transform.position.y .. " z: " .. transform.position.z);
            end;
        end  
    end;
    	function LateUpdate(deltaTime) end;
	function FixedUpdate() 
        local rigidbody = component.entity:GetComponent("Rigidbody").type; -- RETURNS NIL
        --local transform = component.entity.transform;
        -- MOVE CHARACTER:
        if  Input:AnyKeyIsDown() then -- GENERIC CHECK BEFORE CHECKING INDIVIDUAL KEY ==> NECESSARY
            if Input:IsKeyDown("w") then
                
               print("Tecla W");
               print("Transform: x: " .. transform.position.x .." y: " .. transform.position.y .. " z: " .. transform.position.z);
               print("Rigidbody: x: " .. rigidbody.position.x .." y: " .. rigidbody.position.y .. " z: " .. rigidbody.position.z);
               rigidbody:AddForce(Aegis.Maths.Vector3(20, 0, 0))
                
            end;
        end  
    end;
	function OnCollision(other) end;
	function OnTrigger(other) end;

	funcs.init = Init;
    funcs.update = Update;
    funcs.fixedUpdate = FixedUpdate;
	return component;
end;
return table;