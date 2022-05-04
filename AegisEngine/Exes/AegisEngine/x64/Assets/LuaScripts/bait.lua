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
    data.player = "player";
    function Init()
        -- rigidbody = component.entity:GetComponent("Rigidbody").type;
        renderer.visible=false;
        offset = Aegis.Maths.Vector3(0,-0.5,-2);
        -- data.player.transform.forward * 3 + 
        transform.position = offset; 
     end;

	function Update(deltaTime)
        if Input:KeyWasPressed("Space")then
             renderer.visible = not renderer.visible;
        end;            
        transform.position = offset; 
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