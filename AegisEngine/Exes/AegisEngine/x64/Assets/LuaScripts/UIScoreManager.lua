local NAME = "UIScoreManager";
local table = {};
function table.GetNew(entity, params)
	local component = Aegis.CreateComponent(NAME, entity);
	local data = component.data;
	local transform = entity.transform;
    local funcs = component.funcs;
    data.text = "nil";
    data.win = "WinMsg";
    data.home ="HomeButton";
    data.camera = "mainCam";
    local numFish;
    function Init()
        numFish = 10;
    end;
	function Update(deltaTime) 
    if  Input:AnyKeyWasPressed() then -- GENERIC CHECK BEFORE CHECKING INDIVIDUAL KEY ==> NECESSARY
        if Input:KeyWasPressed("l") then
            UpdateScore();
        end;
    end        

    end;
	function LateUpdate(deltaTime) end;
	function FixedUpdate() end;
	function OnCollision(other) end;
	function OnTrigger(other) end;

    function UpdateScore()
        print(data.text:GetName());
        if numFish > 0 then
            numFish = numFish -1;
            data.text:SetText(numFish);
            if numFish == 0 then
                print("Enhorabuena! Todos los peces han sido pescados.\n");
                data.win:SetVisible(true);
                -- DEBERIA BLOQUEARSE LA CAMARA && DESPLOQUEAR RATON
                data.camera:GetComponent("CameraTest").enabled = false;
                Input:BlockMouse(false);
                data.home:SetVisible(true);
            end;
        end;
    end; 

	funcs.init = Init;
    funcs.update = Update;
    funcs.updateScore = UpdateScore;
	return component;
end;
return table;