local NAME = "CharacterMovement";
local table = {};
function table.GetNew(entity, params)
	local component = Aegis.CreateComponent(NAME, entity);
	local data = component.data;
	local transform = entity.transform;
    local funcs = component.funcs;
    local rigidbod;
    data.initPos = transform.position;

    function Init()
        rigidbody = component.entity:GetComponent("Rigidbody").type;
     end;

	function Update(deltaTime) 
            if Input:KeyWasPressed("s") then
                print("Key S was pressed");
            end;
            if Input:IsKeyDown("a") then
                print("Key A is down");
            end;
    end;
    	function LateUpdate(deltaTime) end;
	function FixedUpdate() 
        -- print("Force Y Axis: " .. rigidbody:GetForce().y);
        local rigidbody = component.entity:GetComponent("Rigidbody").type; -- RETURNS NIL
        --local transform = component.entity.transform;
        -- MOVE CHARACTER:
        if  Input:AnyKeyIsDown() then -- GENERIC CHECK BEFORE CHECKING INDIVIDUAL KEY ==> NECESSARY
            
        end  
        if Input:IsKeyDown("s") then               
                
            rigidbody.position = data.initPos;
            print("Force Y Axis: " .. rigidbody:GetForce().y);
            --local vector =; 
         end;
        if Input:IsKeyDown("w") then
            
           print("Tecla W");
           print("Transform: x: " .. transform.position.x .." y: " .. transform.position.y .. " z: " .. transform.position.z);
           print("Rigidbody: x: " .. rigidbody.position.x .." y: " .. rigidbody.position.y .. " z: " .. rigidbody.position.z);
           rigidbody:AddForce(Aegis.Maths.Vector3(20, 0, 0))
           print("Force Y Axis: " .. rigidbody:GetForce().x);
           
            
        end;
    end;
	function OnCollision(other) end;
	function OnTrigger(other) end;

	funcs.init = Init;
    funcs.update = Update;
    funcs.fixedUpdate = FixedUpdate;
	return component;
end;
return table;