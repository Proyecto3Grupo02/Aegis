local NAME = "Seek"
local table = {};

function table.GetNew(entity, params)

    -- Lua Component Creation
    local component = Aegis.CreateComponent(NAME, entity);
    -- Lua Component Data for local handling
    local data = component.data;
    local transform = entity.transform;
    local funcs = component.funcs;
	
    local rb;   
    local speed;
    local maxSpeed;

    local rotation;
    local maxRotation;
    local rotTime;
    
    local target;       --entity target to the seek component
    local onTarget;     --bool that checks if we are inside the radius
    local slowRadius;   --distance to start the slowing
    local distance;     --real time distance

    function Init()
        rb = component.entity:GetComponent("Rigidbody").type;       
        rotTime = 5;
        
        onTarget = false;
        slowRadius = 2;
    end;

    function Update(deltaTime)

        if distance < slowRadius then       --target approached
            speed = 0;
            transform.rotation = rotation;  --no estoy seguro de esto
            onTarget = true;
        else                                --case of approaching the target       
            speed = maxSpeed * transform.rotation;
            distance = target.transform.position - transform.position;
            onTarget = false;
        end;

        rb:AddForce(speed);
    end;

    --useful for events derived of the approaching
    function onTarget()
        return onTarget;
    end;

end;