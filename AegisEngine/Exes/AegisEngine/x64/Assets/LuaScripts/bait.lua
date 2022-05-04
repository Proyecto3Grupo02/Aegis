local NAME = "Bait";
local table = {};
function table.GetNew(entity, params)
	local component = Aegis.CreateComponent(NAME, entity);
	local data = component.data;
	local transform = entity.transform;
    local rigidbody;
    local funcs = component.funcs;
    local renderer = component.entity:GetComponent("Renderer").type;
    local offset;
    local ready;
    data.player = "player";
    function Init()
        rigidbody = component.entity:GetComponent("Rigidbody").type;
        renderer.visible=false;
        offset = Aegis.Maths.Vector3(0,-0.5,-2);
        transform.position = offset; 
        ready = false;
     end;

	function Update(deltaTime)
        if Input:KeyWasPressed("Space")then
            renderer.visible = not renderer.visible;  
            ready = not ready         
        end;   
        if ready then
            if Input:KeyWasPressed("y")then
                rigidbody:AddForce(Aegis.Maths.Vector3(0,-20,-100))
            end;   
        else 
            rigidbody.position = offset
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