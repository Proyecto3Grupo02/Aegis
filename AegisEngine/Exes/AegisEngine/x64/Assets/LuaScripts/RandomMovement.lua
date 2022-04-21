local NAME = "CharacterMovement";
local table = {};
function table.GetNew(entity, params)
	local component = Aegis.CreateComponent(NAME, entity);
	local data = component.data;
	local transform = entity.transform;
    local funcs = component.funcs;
	local rigidbody = component.entity:GetComponent("Rigidbody").type;
	local lastTime = 0;
    function Init() end;
	function Update(deltaTime) 
         -- RETURNS NIL
        --local transform = component.entity.transform;
        -- MOVE CHARACTER; 
		-- cada x tiempo random
		if deltatime > lastTime+5 then
		local rot =math.random(rigidbody:getRotation()-Aegis.Maths.Vector4(5, 0, 0, 0),rigidbody:getRotation()+Aegis.Maths.Vector4(5, 0, 0, 0));
		rigidbody:setRbRotation(rot,0,0,0);
		lastTime = deltaTime;
		end;
		rigidbody:AddForce(Aegis.Maths.Vector3(20, 0, 0));
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