local NAME = "CharacterMovement";
local table = {};
function table.GetNew(entity, params)
	local component = Aegis.CreateComponent(NAME, entity);
	local data = component.data;
	local transform = entity.transform;
    local funcs = component.funcs;
    local rigidbody;
    local w; local a; local s; local d; local fishing;
    data.initPos = transform.position;
    data.camera = "mainCam";
    data.bait = "Bait"; --ANZUELO------------------
    local cameraTf = nil;

    function Init()
        rigidbody = component.entity:GetComponent("Rigidbody").type;
        w=false;
        a=false;
        s=false;
        d=false;
        fishing = false;
        data.camera.transform:SetParent(entity)
        data.bait.transform:SetParent(entity) --ANZUELO------------------
        cameraTf=data.camera.transform;
     end;

	function Update(deltaTime)
        if(Input:KeyWasPressed("Space"))then
            fishing = not fishing;
            print(fishing)
        end;
        if (fishing)then
            return;
        end;
        w = Input:IsKeyDown("w");
        a = Input:IsKeyDown("a");
        s = Input:IsKeyDown("s");
        d = Input:IsKeyDown("d");
    -- IF key is f then set rigibody pos to init pos
        if Input:IsKeyDown("f") then
            rigidbody.position = data.initPos;
        end;
    end;

    function LateUpdate(deltaTime) end;

	function FixedUpdate() 
        -- print("Force Y Axis: " .. rigidbody:GetForce().y);
        -- MOVE CHARACTER:
        local force = 10;
        local targetSpeed = 100;
        local maxAcceleration = 50;
        if s then                
            --rigidbody:AddForce(Aegis.Maths.Vector3(0, 0, 0.5) * force)
            rigidbody:AccelerateTo(cameraTf.forward * targetSpeed, maxAcceleration);
            --rigidbody.position= rigidbody.position + Aegis.Maths.Vector3(0,0, -0.05);                 
        end;
        if a then                
            --rigidbody:AddForce(Aegis.Maths.Vector3(-0.5, 0, 0) * force)
            rigidbody:AccelerateTo(cameraTf.right * -1 * targetSpeed, maxAcceleration);
            --rigidbody.position= rigidbody.position + Aegis.Maths.Vector3(-0.05,0,0);   
        end;
        if w then                
            --rigidbody:AddForce(Aegis.Maths.Vector3(0, 0, -0.5) * force)
            rigidbody:AccelerateTo(cameraTf.forward * -1 * targetSpeed, maxAcceleration);
            --rigidbody.position= rigidbody.position + Aegis.Maths.Vector3(0,0, 0.05);
        end;
        if d then                
            --rigidbody:AddForce(Aegis.Maths.Vector3(0.5, 0, 0) * force)
            rigidbody:AccelerateTo(cameraTf.right * targetSpeed, maxAcceleration);
            -- rigidbody.position= rigidbody.position + Aegis.Maths.Vector3(0.05,0,0); 
            --print("Force X Axis: " .. rigidbody:GetForce().x);  
        end;
        if  (w == false and a == false and s==false and d ==false)  then
            rigidbody:AccelerateTo(cameraTf.right * 0, maxAcceleration);
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