local NAME = "RandomMovement";
local table = {};
function table.GetNew(entity, params)
	local component = Aegis.CreateComponent(NAME, entity);
	local data = component.data;
	local transform = entity.transform;
    local funcs = component.funcs;
	local rigidbody;
	local canRoot;
	local ray;
	local root;
	local acumulatedDT;
	local acumulatedRay;
	local cooldown = 5; 
	
    function Init() 
        rigidbody = component.entity:GetComponent("Rigidbody").type;
		lastTime=0;
		acumulatedDT=0;
		acumulatedRay=0;
		root = 0;	
		ray = false;
    end;
	function Update(deltaTime) 
		if acumulatedDT > lastTime + 3 then
			canRoot=true;
			root = math.random(-10,10);
			lastTime = acumulatedDT;		
		end;
		if acumulatedRay > cooldown then
			ray = true;
			acumulatedRay = 0;
		end;
		acumulatedRay = acumulatedRay + deltaTime;
		acumulatedDT = acumulatedDT + deltaTime;
	end;
    
	function LateUpdate(deltaTime)
	end;
	function FixedUpdate() 
		--rigidbody:AccelerateTo(Aegis.Maths.Vector3(0,0,0), 0);
		if canRoot then
			
			rigidbody:AccelerateToRand();
			--rigidbody:AddTorque(Aegis.Maths.Vector3(0,root,0));
			canRoot=false;
		end;
		--comprobacion de colision
		-- if ray and rigidbody:RayCastWorld()  then
		-- 	ray = false;
		-- 	local random; random = math:random(0,3); 
		-- 	while (random == 1) do random = math:random(0,3); random= random - 1; end;
		-- 	rigidbody:addTorque({ 0,float(random),0 });
		-- end;
	end;

	function OnCollision(other) end;
	function OnTrigger(other) end;

	funcs.init = Init;
    funcs.update = Update;
    funcs.fixedUpdate = FixedUpdate;
	return component;
end;
return table;