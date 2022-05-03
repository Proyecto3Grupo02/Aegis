local NAME = "Bait";
local table = {};
function table.GetNew(entity, params)
	local component = Aegis.CreateComponent(NAME, entity);
	local data = component.data;
	local transform = entity.transform;
    local funcs = component.funcs;
    local renderer = component.entity:GetComponent("Renderer").type;
    --data.player = "player";
    function Init()
        local meshRenderer = component.entity:GetComponent("Renderer").type;
        -- renderer.visible=false;
      --  data.player.transform:SetParent(entity)
     end;

	function Update(deltaTime)
        -- transform.position= data.player.position
    end;

    function LateUpdate(deltaTime) end;

	function FixedUpdate() 

    end;

	function OnCollision(other) end;
	function OnTrigger(other) end;

	funcs.init = Init;
    funcs.update = Update;
    funcs.fixedUpdate = FixedUpdate;
	return component;
end;
return table;