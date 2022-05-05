local NAME= "Wander"
local table={};
function table.GetNew(entity, params)
    local component= Aegis.CreateComponent(NAME, entity);
    local data= component.data;
    local transform= entity.transform;
    local funcs = component.funcs;
	

    local rb;
    local maxSpeed;

    local rotation;
    local velocity;
    local maxRotation;
    local rotTime;
    local lastTime;
    function Init()
        rb= component.entity:GetComponent("Rigidbody").type;
        lastTime=0;         
        rotTime=5;

    
    end;

    function Update(deltaTime)
        
        
        velocity= maxSpeed* transform.rotation; 
        if lastTime >rotTime then
        rotation= RandomBinomial() * maxRotation; 
        lastTime= rotTime;
        rotTime=rotTime + deltaTime;
        rb:SetRotationEuler(rotation);
        end;

        rb:AddForceForward(velocity);

        --Ian Millington pseudocode-------------------------------------------------------------------------------
        -- result.velocity= maxSpeed* character.orientationAsVector(look vector)
        --result.rotation=randomBinomial* maxRotation --just added a time to decide when rotate as a plus
        --return result
        ----------------------------------------------------------------------------------------------------------

    end;

    function RandomBinomial()
        return math.random(-1,1) - math.random(-1,1);
    end;

end;