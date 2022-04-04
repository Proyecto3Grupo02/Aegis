-- Example of scene, it's just a table with list of entities

local NAME = "TestScene";
local scene = {
	{
		type = "Entity",
		name = "Fish",
		position = { x = 0, y = 0, z = 0},
		scale = { x = 0.5 },
		components = {
			{
				type = "SimpleRotate",
			},
			{
				type = "Renderer",
				data = {
					mesh = "fish.mesh",
					material= "blue"
				}
			}
		}
	},
	-- {
	-- 	type = "Entity",
	-- 	name = "Rust",
	-- 	components = {
	-- 		{
	-- 			type = "TestComponent",
	-- 			data = {
	-- 				test2 = 1,
	-- 				test4 = 3
	-- 			}
	-- 		},
	-- 		{
	-- 			type = "Renderer",
	-- 			data = {
	-- 				mesh = "Rust.mesh",
	-- 				material="red"
	-- 			}
	-- 		}
	-- 	}
	-- },

	{
		type = "Entity",
		name = "light",
		position = { x = 0, y = 4, z = 0},
		components = {
			{
				type = "Light",
				data = {
					lightType = "DirLight",
					color = { r = 0.5, g = 0.5, b = 0.5  },
					spec = { r = 0.2, g = 0.2, b = 0.2 },
					direction = { x = 0, y = 1, z = 0 }
				}
			}
		}
	}
};
return scene;
