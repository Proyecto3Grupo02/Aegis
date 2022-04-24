local NAME = "CharacterMovement";
local table = {};
function table.GetNew(entity, params)
	local component = Aegis.CreateComponent(NAME, entity);
	local data = component.data;
	local transform = entity.transform;
    local funcs = component.funcs;
    local rigidbod;
    local w; local a; local s; local d;
    data.initPos = transform.position;

    function Init()
        rigidbody = component.entity:GetComponent("Rigidbody").type;
        w=false;
        a=false;
        s=false;
        d=false;
     end;

	function Update(deltaTime)
        w = Input:IsKeyDown("w");
        a = Input:IsKeyDown("a");
        s = Input:IsKeyDown("s");
        d = Input:IsKeyDown("d");
    -- IF key is f then set rigibody pos to init pos
        if Input:IsKeyDown("f") then
            rigidbody.position = data.initPos;
        end;
    end;

    function LateUpdate(deltaTime) end;

	function FixedUpdate() 
        -- print("Force Y Axis: " .. rigidbody:GetForce().y);
        -- MOVE CHARACTER:
        if w then                
            rigidbody:AddForce(Aegis.Maths.Vector3(0, 0, 0.5))
            --rigidbody.position= rigidbody.position + Aegis.Maths.Vector3(0,0, -0.05);                 
        end;
        if a then                
            rigidbody:AddForce(Aegis.Maths.Vector3(-0.5, 0, 0))
            --rigidbody.position= rigidbody.position + Aegis.Maths.Vector3(-0.05,0,0);   
        end;
        if s then                
            rigidbody:AddForce(Aegis.Maths.Vector3(0, 0, -0.5))
            --rigidbody.position= rigidbody.position + Aegis.Maths.Vector3(0,0, 0.05);
        end;
        if d then                
            rigidbody:AddForce(Aegis.Maths.Vector3(0.5, 0, 0))
            -- rigidbody.position= rigidbody.position + Aegis.Maths.Vector3(0.05,0,0); 
            --print("Force X Axis: " .. rigidbody:GetForce().x);  
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