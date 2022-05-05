local NAME = "Bait";
local table = {};
function table.GetNew(entity, params)
    local WATER_Y = -5
	local component = Aegis.CreateComponent(NAME, entity);
	local data = component.data;
	local transform = entity.transform;
    local renderer;
    local rigidbody;
    local funcs = component.funcs;
    local offset;
    local ready;
    local throwForce;
    data.player = "player";
    function Init()
        renderer = component.entity:GetComponent("Renderer").type;
        renderer.visible=false;
        rigidbody = component.entity:GetComponent("Rigidbody").type;        
        offset = Aegis.Maths.Vector3(0,-0.5,-2);
        transform.position = offset; 
        ready = false;
        rigidbody:FreezeRot(true,true,true)
     end;

	function Update(deltaTime)
        if Input:KeyWasPressed("Space")then
            renderer.visible = not renderer.visible;  
            ready = not ready         
        end;   
        if ready then
            if Input:IsMouseButtonDown(0)then
               throwForce = throwForce + deltaTime * 3
            end
            if Input:MouseButtonWasReleased(0)then
                if throwForce>5 then
                    throwForce = 5
                end;
                rigidbody:AddForce(Aegis.Maths.Vector3(0,throwForce*20,throwForce*-150))
                rigidbody.useGravity=true
            end;
        else 
            throwForce=0
            rigidbody.useGravity=false
            rigidbody:ClearForce();
            rigidbody.position = offset
        end

        if rigidbody.position.y < WATER_Y and rigidbody.useGravity then
            rigidbody.useGravity=false;
            rigidbody:ClearForce();
        end;
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