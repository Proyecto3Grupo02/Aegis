

local NAME = "PlayOnRequest";

local table = {};
function table.GetNew(entity, params)
    local component = Aegis.CreateComponent(NAME,entity);
    local data = component.data;
    local funcs = component.funcs;
    local sonic;

    function Init() 
		sonic = component.entity:GetComponent("SoundEmitter").type;
        --sonic:PlaySound(sonic.data.sound);

    end;
    function Update(deltatime)
        if Input:KeyWasPressed("Space")then
            sonic:PlaySound(sonic.data.sound);
        end;
    end;
    funcs.init = Init;
    funcs.update = Update;
    return component;
end;
return table;
