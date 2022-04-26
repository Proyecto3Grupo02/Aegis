local NAME = "RandomMovement";
local table = {};
function table.GetNew(entity, params)
	local component = Aegis.CreateComponent(NAME, entity);
	local data = component.data;
	local transform = entity.transform;
    local funcs = component.funcs;
	local rigidbody;
	local canRoot;
	local root;
	local acumulatedDT;
	
    function Init() 
        rigidbody = component.entity:GetComponent("Rigidbody").type;
		lastTime=0;
		acumulatedDT=0;
		root = 0;	
    end;
	function Update(deltaTime) 
		if acumulatedDT > lastTime + 1 then
			canRoot=true;
			root = math.random(-10,10);
			lastTime = acumulatedDT;		
		end;
		acumulatedDT = acumulatedDT + deltaTime;
	end;
    
	function LateUpdate(deltaTime)
	end;
	function FixedUpdate() 
		rigidbody:AddForce(Aegis.Maths.Vector3(0, 0, -5));
		if canRoot then
			rigidbody:AddTorque(Aegis.Maths.Vector3(0,root,0));
			canRoot=false;
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