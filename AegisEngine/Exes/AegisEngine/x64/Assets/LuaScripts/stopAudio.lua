local NAME = "StopSound";

local table = {}
function table.GetNew(entity, params)
    local component = Aegis.CreateComponent(NAME,entity);
    local data = component.data;
    local funcs = component.funcs;
    

    function stopAll() 
		local stopAudio = component.entity:GetComponent("SoundEmitter").type;
        
        stopAudio:Stop();

    end
   

    funcs.init = Init;
end
return table;