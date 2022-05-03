-- Example of scene, it's just a table with list of entities

local NAME = "RotScene";
local scene = {
	{
		type = "MainCamera",
		position = { z = 10, y = 3  },
		components = {
			{
				type = "CameraTest"
			}
		}
	},
	{
		type = "Entity",
		name = "Player",
        -- rotation = {y=45},
		components = {
			{
				type = "Renderer",
				data = {
					mesh = "Cube.mesh",
					material= "blue"
				}
			},
			{
				type = "Rigidbody",
				data = 
				{
					useGravity = false,
				}
			},
			{
				type = "CharacterRotation"
			}
		},
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
					direction = { x = 0, y = -0.5, z = -0.75 }
				}
			}
		}
	}
};
return scene;
