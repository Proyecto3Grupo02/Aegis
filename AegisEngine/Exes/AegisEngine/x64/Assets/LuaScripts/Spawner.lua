local NAME = "Spawner";

local table = {};
function table.GetNew(entity, params)
	local component = Aegis.CreateComponent(NAME, entity);
	local data = component.data;
	local transform = entity.transform;
    local funcs = component.funcs;
	local acumulatedDT;
    local lastTime;
	local utility = require "Utils";
    local prefabs = require "Prefabs";
    local maxFish = 6;
    data.currFish = 0;
    function Init() 
		lastTime=10;
		acumulatedDT=0;
    end;
	function Update(deltaTime) 
		if acumulatedDT > lastTime and data.currFish < maxFish then
            lastTime = acumulatedDT +10;
            print(lastTime);
            print(acumulatedDT);
                local fish = utility.ParseEntity(prefabs[math.random(#prefabs)]);
                local rbFish = fish:GetComponent("Rigidbody").type;
                rbFish.position = Aegis.Maths.Vector3(0,-55,0);
                data.currFish = data.currFish+1;
		end;
		acumulatedDT = acumulatedDT + deltaTime;
	end;
    
	funcs.init = Init;
    funcs.update = Update;
	return component;
end;
return table;