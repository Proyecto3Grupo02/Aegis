

local NAME = "PlayOnInit";

local table = {};
function table.GetNew(entity, params)
    local component = Aegis.CreateComponent(NAME,entity);
    --local data = component.data;
    local funcs = component.funcs;
    local sonic; 
    local booli;

    function Init() 
	sonic = component.entity:GetComponent("SoundEmitter").type;
        sonic:PlayMusic(sonic.data.sound);
        booli = true;
    end;
    function Update(deltatime)
        if Input:KeyWasPressed("Space")then 
            --print("espacio presed");
            if booli then
                --print("booli true");
            --sonic:StopSound();
            
            else
                --print("booli false");
                sonic:PlayMusic(sonic.data.sound);
            end;
            booli = not booli
        end;
            --end;        
    end;
    funcs.init = Init;
    funcs.update = Update;
    return component;
end;
return table;

