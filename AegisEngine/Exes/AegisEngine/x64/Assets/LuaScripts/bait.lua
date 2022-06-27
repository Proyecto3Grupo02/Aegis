local NAME = "Bait";
local table = {};
function table.GetNew(entity, params)
    local WATER_Y = -56
	local component = Aegis.CreateComponent(NAME, entity);
	local data = component.data;
	local transform = entity.transform;
    local renderer;
    local rigidbody;
    local funcs = component.funcs;
    local offset;
    local ready;
    local throwForce;
    local maxForce;
    data.player = "player";
    function Init()
        renderer = component.entity:GetComponent("Renderer").type;
        renderer.visible=false;

        rigidbody = component.entity:GetComponent("Rigidbody").type;        
        offset = Aegis.Maths.Vector3(0,-0.5,-2);
        transform.position = offset;
        ready = false;
        rigidbody:FreezeRot(true,true,true)
        maxForce = 5;
        rigidbody.position = Aegis.Maths.Vector3(transform.position.x+data.player.transform.position.x,transform.position.y+data.player.transform.position.y,transform.position.z+data.player.transform.position.z);
        rigidbody:EnableCol(false);
     end;

	function Update(deltaTime)
       -- print(data.player.transform.rotation);
      
        if Input:KeyWasPressed("Space")then
            renderer.visible = not renderer.visible;  
            ready = not ready 
            transform.position = offset;
            rigidbody.position = Aegis.Maths.Vector3((transform.position.x+data.player.transform.position.x),transform.position.y+data.player.transform.position.y,transform.position.z+data.player.transform.position.z);              
            transform.localEulerAngles = data.player.transform.localEulerAngles;
        end;   
        if ready then
            if Input:IsMouseButtonDown(0)then
               throwForce = throwForce + deltaTime * 3
            end
            if Input:MouseButtonWasReleased(0)then
                if throwForce>maxForce then
                    throwForce = maxForce
                end;
                --rigidbody:AddForce(Aegis.Maths.Vector3(0,throwForce*20,throwForce*-150))
              
                rigidbody:AddForce(transform.forward  * throwForce * -100)
                rigidbody.useGravity=true
            end;
        else 
            throwForce=0
            rigidbody.useGravity=false
            rigidbody:ClearForce();
            rigidbody.position = offset
            rigidbody:EnableCol(false);
        end

        if rigidbody.position.y < WATER_Y and rigidbody.useGravity then
            rigidbody:ClearForce();
            rigidbody.useGravity=false;
            rigidbody:EnableCol(true);         
        end;
    end;

    function LateUpdate(deltaTime) end;

	function FixedUpdate() 

    end;

	function OnCollision(other)
        print("Colision del anzuelo con algo");
    end;

	funcs.init = Init;
    funcs.update = Update;
    funcs.fixedUpdate = FixedUpdate;
    funcs.onCollisionEnter = OnCollision;
	return component;
end;
return table;