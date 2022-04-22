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
        if Input:IsKeyDown("w") then
            w = true;           
        end;
        if Input:IsKeyDown("a") then
            a=true;
        end;
        if Input:IsKeyDown("s") then
            s=true;
        end;
        if Input:IsKeyDown("d")then
            d=true;
        end;
        if Input:KeyWasReleased("w") then
            w=false;
        end;
        if Input:KeyWasReleased("a")then
            a=false;
        end;
        if Input:KeyWasReleased("s") then
            s=false;
        end;
        if Input:KeyWasReleased("d") then
            d=false;
        end;
          
    end;

    function LateUpdate(deltaTime) end;

	function FixedUpdate() 
        local rigidbody = component.entity:GetComponent("Rigidbody").type; -- RETURNS NIL
        --local transform = component.entity.transform;
        -- MOVE CHARACTER:
        if w then                
            rigidbody:AddForce(Aegis.Maths.Vector3(0, 0, 0.5))
            rigidbody.position= rigidbody.position + Aegis.Maths.Vector3(0,0, -0.05);                 
        end;
        if a then                
            rigidbody:AddForce(Aegis.Maths.Vector3(-0.5, 0, 0))
            rigidbody.position= rigidbody.position + Aegis.Maths.Vector3(-0.05,0,0);   
        end;
        if s then                
            rigidbody:AddForce(Aegis.Maths.Vector3(0, 0, -0.5))
            rigidbody.position= rigidbody.position + Aegis.Maths.Vector3(0,0, 0.05);
        end;
        if d then                
            rigidbody:AddForce(Aegis.Maths.Vector3(0.5, 0, 0))
            rigidbody.position= rigidbody.position + Aegis.Maths.Vector3(0.05,0,0);   

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