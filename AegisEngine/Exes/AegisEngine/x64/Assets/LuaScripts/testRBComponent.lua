-- test component as example

local NAME="TestRBComponent"

local table = {};
function table.GetNew(entity, params)
	local component = Aegis.CreateComponent(NAME, entity);
	local data = component.data;
	local transform = entity.transform;
    local funcs = component.funcs;

    function Init() end;
	function Update(deltaTime) 
        local transform = component.entity.transform;

        --local rb = component.entity.GetComponent("Rigidbdoy").type;

        transform.position = Aegis.Maths.Vector3(math.sin(data.time) * 5,0, 0);
       
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