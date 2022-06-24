local NAME = "CharacterRotation";
local table = {};
function table.GetNew(entity, params)
	local component = Aegis.CreateComponent(NAME, entity);
	local data = component.data;
	local transform = entity.transform;
    local funcs = component.funcs;
    data.senstivity = 2;
    function Init() 
        euAng = transform.localEulerAngles;
        rigidbody = component.entity:GetComponent("Rigidbody").type;
    end;
	function Update(deltaTime)
        print("data sens"..data.senstivity)
    end        

    function LateUpdate(deltaTime) end;

	function FixedUpdate()
        local mouseMotion = Input:GetMouseMotion();
        if mouseMotion.x ~= 0 and mouseMotion.y ~= 0 then
            local x = mouseMotion.x * data.senstivity;
            euAng = (transform.localEulerAngles +  Aegis.Maths.Vector3(0, x, 0));
        end;
        -- Lerp current Rotation to target rotation
        rigidbody:SetRotationEuler(euAng);

    end;
	function OnCollision(other) end;
	function OnTrigger(other) end;

	funcs.init = Init;
    funcs.update = Update;
    funcs.lateUpdate = LateUpdate;
    funcs.fixedUpdate = FixedUpdate;
	return component;
end;
return table;