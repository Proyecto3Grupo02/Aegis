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
	local lastTimeRay; 
	local random; 
	local random2; 
	
    function Init() 
        rigidbody = component.entity:GetComponent("Rigidbody").type;
		lastTime=0;
		lastTimeRay = 0;
		acumulatedDT=0;
		acumulatedRay=0;
		root = 0;			
		ray = false;
		random = 0;
		random2 = 0;
		rigidbody:SetAngular();
    end;
	function Update(deltaTime) 
		if acumulatedDT > lastTime + 1 then
			canRoot=true;
			root = math.random(-10,10);
			lastTime = acumulatedDT;		
		end;
		if acumulatedRay > lastTimeRay + 1 then
			ray = true;
			
			random = math.random(0,3); 
			random2 = math.random(0,3)
			-- while (random == 1) do 
			-- 	random = math.random(0,3); 
			-- 	random= random - 1; 
			-- end;
			lastTimeRay = acumulatedRay;
		end;
		acumulatedRay = acumulatedRay + deltaTime;
		acumulatedDT = acumulatedDT + deltaTime;
	end;
    
	function LateUpdate(deltaTime)
	end;
	function FixedUpdate() 
		rigidbody:AccelerateTo(Aegis.Maths.Vector3(0,0,0), 0);
		if canRoot then
			--rigidbody:SetRotationEuler(transform.localEulerAngles + Aegis.Maths.Vector3(0,random*3,0));
			rigidbody:AccelerateTo(Aegis.Maths.Vector3(random*3,0,random2*3), 100000000);			
			--rigidbody:AccelerateToRand();
			--rigidbody:AddTorque(Aegis.Maths.Vector3(0,root,0));
			canRoot=false;
		end;
		--comprobacion de colision
		if ray and rigidbody:RayCastWorld()  then
			ray = false;			
			rigidbody:AccelerateToRand();
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