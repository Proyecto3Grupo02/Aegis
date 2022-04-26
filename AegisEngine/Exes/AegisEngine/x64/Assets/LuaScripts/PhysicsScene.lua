-- Example of scene, it's just a table with list of entities

local NAME = "PhysicsScene";
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
	{
		type = "Entity",
		name = "Cubo",
		position = { y = 2},
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
			},
			{
				type = "CharacterMovement"				
			}
		}
	},
	{
		type = "Entity",
		name = "Cubo2",
		position = { y = 2, x = 2},
		scale = { x = 0.5, y = 0.5, z = 0.5 },
		components = {
			{
				type = "Renderer",
				data = {
					mesh = "Cube.mesh",
					material= "yellow"
				}
			},
			{
				type = "Rigidbody",
			},
		}
	},
	{
		type = "Entity",
		name = "Suelo",
		position = { y = -2 },
		scale = { x = 50, y = 0.1, z = 50},
		components = {
			{
				type = "Renderer",
				data = {
					mesh = "Cube.mesh",
					material= "red"
				}
			},
			{
				type = "Rigidbody",
				data = 
				{
					isKinematic = true
				}
			},
			{
				type = "DestroyTest",
				data =
				{
					child = "@Cubo"
				}
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
		
	},
	{
		type = "Entity",
		name = "RandomFish",
		position = { y = 1.1, z =1.01 },
		scale = {x = 0.5, y = 0.5, z =0.5},
		components = {
			{
				type = "Renderer",
				data = {
						mesh = "Cube.mesh",
						material= "yellow"
					}
			},
			{
				type = "Rigidbody"
			},
			{
				type = "RandomMovement"
			}
		}
	}
};
return scene;
