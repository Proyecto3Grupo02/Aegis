local NAME = "CharacterMovement";
local table = {};
function table.GetNew(entity, params)
	local component = Aegis.CreateComponent(NAME, entity);
	local data = component.data;
	local transform = entity.transform;
    local funcs = component.funcs;
	local rigidbody;
	local root;
	
    function Init() 
        rigidbody = component.entity:GetComponent("Rigidbody").type;
		lastTime=0;
		root = false;
    end;
	function Update(deltaTime) 
		if deltaTime> lastTime+5 then
			root = true;
			lastTime = deltaTime;
		end;
		-- RETURNS NIL
        --local transform = component.entity.transform;
        -- MOVE CHARACTER; 
		-- cada x tiempo random
		-- if deltatime > lastTime+5 then
		-- local rot = math.random(-45,45);
		-- rigidbody.rotation = Aegis.Maths.Vector4(rot,0,0,0);
		-- -- rigidbody:addTorque(Aegis.Maths.Vector3(0, rot, 0);
		-- lastTime = deltaTime;
		-- end;
		-- -- rigidbody:AddForce(Aegis.Maths.Vector3(20, 0, 0));
		-- rigidbody.position = rigidbod.position + Aegis.Maths.Vector3(20,0,0);
    end;
    
	function LateUpdate(deltaTime)
	end;
	function FixedUpdate() 
		if root then
			local rot = math.random(-45,45);
			rigidbody.rotation = Aegis.Maths.Vector4(rot,0,0,0);
			root = false;
		end;
		rigidbody.position = rigidbody.position + Aegis.Maths.Vector3(0,0,0.05);
	end;

	function OnCollision(other) end;
	function OnTrigger(other) end;

	funcs.init = Init;
    funcs.update = Update;
    funcs.fixedUpdate = FixedUpdate;
	return component;
end;
return table;