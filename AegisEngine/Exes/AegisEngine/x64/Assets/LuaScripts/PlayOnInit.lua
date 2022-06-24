local NAME = "PlayOnInit";

local table = {};
function table.GetNew(entity, params)
    local component = Aegis.CreateComponent(NAME,entity);
    local data = component.data;
    local funcs = component.funcs;
    

    function Init() 
		local sonic = component.entity:GetComponent("SoundEmitter").type;
        
        sonic:play(sonic.data.sound);

    end;
   

    funcs.init = Init;
end;
return table;

-- Play unico (menu con loop)
-- Play tecla
-- Play raton
-- Play collision
-- Play UI (optional)