-- Example of scene, it's just a table with list of entities

local NAME = "UIScene";
local scene = {
	{
        type = "MainCamera",
        position = { z = 10 },
        components = 
        {
            {
                type = "CameraTest"
            }
        }
    },

	-- {
	-- 	type= "Canvas",
	-- 	elements={
			
	-- 	}

	-- },

	{
		type = "Entity",
		name = "Cubo",
		position = { y = 2},
		scale= {x=10, y=10, z=0.2},
		components = {
			{
				type = "Renderer",
				data = {
					mesh = "Cube.mesh",
					material= "blue"
				}
			}
			,
			{
				type = "CharacterMovement"				
			}
		}
	},
	{
		type = "Entity",
		name = "light",
		position = { x = 0, y = 4, z = 0},
		components = {
			{
				type = "Light",
				data = {
					lightType = "DirLight",
					color = { r = 0.8, g = 0.8, b = 0.8  },
					spec = { r = 0.8, g = 0.8, b = 0.8 },
					direction = { x = 0, y = 0.25, z = -0.75 }
				}
			}
		}
		
	}
};
return scene;
