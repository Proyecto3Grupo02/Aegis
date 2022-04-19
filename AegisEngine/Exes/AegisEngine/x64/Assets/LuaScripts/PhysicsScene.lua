-- Example of scene, it's just a table with list of entities

local NAME = "PhysicsScene";
local scene = {
	{
		type = "Entity",
		name = "Fish",
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
				type = "RigidBody",
				data = 
				{
					bodyName = "R1"
				}
			}
		}
	},
	{
		type = "Entity",
		name = "LittleFish",
		position = { y = -2 },
		scale = { x = 5, y = 0.1, z = 5},
		components = {
			{
				type = "Renderer",
				data = {
					mesh = "Cube.mesh",
					material= "red"
				}
			},
			{
				type = "RigidBody",
				data = 
				{
					bodyName = "R2",
					isKinematic = true,
					useGravity = false
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
	}
};
return scene;
