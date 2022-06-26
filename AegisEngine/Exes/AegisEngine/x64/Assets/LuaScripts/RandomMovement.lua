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
	local scoreManagerScrpit;
	data.bait = "Bait"
	data.score = "Score"

    function Init() 
        rigidbody = component.entity:GetComponent("Rigidbody").type;
		lastTime=1;
		lastTimeRay = 0;
		acumulatedDT=0;
		acumulatedRay=0;
		root = 0;			
		ray = false;
		random = 0;
		random2 = 0;
		rigidbody:SetAngular();
		print(data.bait:GetName());
		--rigidbody:SetPosition(Aegis.Maths.Vector3(0,-57,0));
		rigidbody:FreezeRot(true,false,true)
    end;

	function Update(deltaTime) 
		
		if acumulatedDT > lastTime then
			canRoot=true;
			root = math.random(-10,10);
			acumulatedDT = acumulatedDT - lastTime;	
			ray = true;		
		end;
		acumulatedDT = acumulatedDT + deltaTime;
	end;
    
	function LateUpdate(deltaTime)
	end;

	function FixedUpdate() 
		
		rigidbody:SetRotationEuler(transform.localEulerAngles + Aegis.Maths.Vector3(0,root / 10,0));
		rigidbody:AccelerateTo(transform.forward * -1 * 7, 10000000);
		
		
		if ray then
			local dest = transform.forward * -1;
			local origin = transform.position;
			local rayCastResult = rigidbody:RayCastWorld(origin, dest, 10);
			--print(rayCastResult)
			-- print("Forward " .. transform.forward.x .. " " .. transform.forward.y .. " " .. transform.forward.z);
			-- print("Dest " .. dest.x .. " " .. dest.y .. " " .. dest.z);
			if rayCastResult == 1 then
				ray = false;			
			rigidbody:SetRotationEuler(transform.localEulerAngles + Aegis.Maths.Vector3(0,180,0));
			rigidbody:AccelerateTo(transform.forward * -1 * 7, 10000000);
			end;
			if rayCastResult == 2 then
				
			end;
		end;
	end;

	function OnCollision(other)
		print(other:GetName());
		if other:GetName() == 'Anzuelo' then
			print("Colision de un pez con el anzuelo");
			data.score.funcs.updateScore();
			entity:Destroy();			
		end;
	end;
	
	function OnTrigger(other) end;

	funcs.init = Init;
    funcs.update = Update;
    funcs.fixedUpdate = FixedUpdate;
    funcs.onCollisionEnter = OnCollision;
	return component;
end;
return table;