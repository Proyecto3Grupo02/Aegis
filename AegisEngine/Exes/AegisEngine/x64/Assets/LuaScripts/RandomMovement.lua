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
			ray = true;		
		end;
		-- if acumulatedRay > lastTimeRay + 1 then
		-- 	ray = true;			
		-- 	random = math.random(-10,10); 			
		-- end;
		--acumulatedRay = acumulatedRay + deltaTime;
		acumulatedDT = acumulatedDT + deltaTime;
	end;
    
	function LateUpdate(deltaTime)
	end;
	function FixedUpdate() 
		
		rigidbody:SetRotationEuler(transform.localEulerAngles + Aegis.Maths.Vector3(0,root / 10,0));
			rigidbody:AccelerateTo(transform.forward * -1 * 7, 10000000);
		
		if ray then
			local type = rigidbody:RayCastWorld();
			if type == 1 then
				ray = false;			
			rigidbody:SetRotationEuler(transform.localEulerAngles + Aegis.Maths.Vector3(0,180,0));
			rigidbody:AccelerateTo(transform.forward * -1 * 7, 10000000);
			end;
			if type == 2 then
				
			end;
			
			
			
			
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