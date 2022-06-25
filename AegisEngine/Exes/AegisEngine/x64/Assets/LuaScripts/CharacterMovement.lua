local NAME = "CharacterMovement";
local table = {};
function table.GetNew(entity, params)
	local component = Aegis.CreateComponent(NAME, entity);
	local data = component.data;
	local transform = entity.transform;
    local funcs = component.funcs;
    local rigidbody;
    local offset;
    local w; local a; local s; local d; local fishing;
    data.initPos = transform.position;
    data.camera = "mainCam";
    data.bait = "Bait"; --ANZUELO------------------
    data.canya = "Canya"; --CAÑA DE PESCAR------------------------
    data.homeButton = "HomeButton";
    local cameraTf = nil;
    local forward
    local euAng;
    local mouseB;
    data.sensitivity=0

    function Init()
        mouseB=true;
        Input:BlockMouse(true);
        rigidbody = component.entity:GetComponent("Rigidbody").type;
        renderer = component.entity:GetComponent("Renderer").type;
        w=false; a=false; s=false; d=false; fishing = false;
        offset = Aegis.Maths.Vector3(0, 10,20)
        ---- OBEJTOS HIJOS
        data.camera.transform:SetParent(entity)
        data.bait.transform:SetParent(entity)
        data.canya.transform:SetParent(entity)
        ---- TRANSFORM CAMARA
        cameraTf=data.camera.transform;
        forward = cameraTf.forward;
        euAng = transform.localEulerAngles;
        rigidbody:FreezeRot(true,true,true)
        renderer.visible=true;
     end;

	function Update(deltaTime)
        if(Input:KeyWasPressed("P"))then
            if(mouseB)then 
                mouseB=false
            else mouseB = true
            end;
            Input:BlockMouse(mouseB);
            data.camera:GetComponent("CameraTest").enabled = mouseB;
            data.homeButton:SetVisible(not mouseB)          
        end;
        if(Input:KeyWasPressed("Space"))then
            fishing = not fishing;
            renderer.visible = not renderer.visible;
            rigidbody:ResetVelocity()
        end;
        if (fishing)then
            cameraTf.position = Aegis.Maths.Vector3(0,0,0)
            data.sensitivity=0.1
        else   
            data.sensitivity = 0.2
            cameraTf.position= offset;
            w = Input:IsKeyDown("w");
            a = Input:IsKeyDown("a");
            s = Input:IsKeyDown("s");
            d = Input:IsKeyDown("d");
            -- IF key is f then set rigidbody pos to init pos
            if Input:IsKeyDown("f") then
                rigidbody.position = data.initPos; 
            end;
        end;   
    end;

    function LateUpdate(deltaTime) end;

	function FixedUpdate()
        if not mouseB then
            return;
        end;

        local mouseMotion = Input:GetMouseMotion();
        if mouseMotion.x ~= 0 and mouseMotion.y ~= 0 then
            local x = mouseMotion.x * data.sensitivity;
            euAng = (transform.localEulerAngles -  Aegis.Maths.Vector3(0, x, 0));
        end;
        -- Lerp current Rotation to target rotation
        rigidbody:SetRotationEuler(euAng);
        ------------------------------------------------------

        -- MOVE CHARACTER:
        local force = 10;
        local targetSpeed = 200;
        local maxAcceleration = 200;
        forward = cameraTf.forward;
        forward.y = 0;
        if(fishing)then
            rigidbody:AccelerateTo(transform.forward*0, maxAcceleration);
        else
            if s then                
                rigidbody:AccelerateTo(transform.forward* targetSpeed, maxAcceleration);           
            end;
            if a then                
                rigidbody:AccelerateTo(transform.right * -1 * targetSpeed, maxAcceleration); 
            end;
            if w then                
                rigidbody:AccelerateTo(transform.forward * -1 * targetSpeed, maxAcceleration);
            end;
            if d then                
                rigidbody:AccelerateTo(transform.right * targetSpeed, maxAcceleration); 
            end;
        end;
    end;

	function OnCollision(other)
        print("Colision general character");
	end;
	function OnTrigger(other) end;

	funcs.init = Init;
    funcs.update = Update;
    funcs.fixedUpdate = FixedUpdate;
    funcs.lateUpdate = LateUpdate;
    funcs.onCollisionEnter = OnCollision;
	return component;
end;
return table;