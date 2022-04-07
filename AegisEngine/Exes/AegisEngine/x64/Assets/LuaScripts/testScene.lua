-- Example of scene, it's just a table with list of entities

local NAME = "TestScene";
local scene = {
	{
		type = "Entity",
		name = "Fish",
		position = { x = 2, y = 1, z = -2},
		scale = { x = 1, y = 0.25, z = 0.25},
		rotation = { x = 40, y = 120, z = 60 },
		components = {
			{
				type = "SimpleRotate"
			},
			-- {
			-- 	type = "TestComponent",
			-- },
			{
				type = "Renderer",
				data = {
					mesh = "fish.mesh",
					material= "blue"
				}
			},
			{
				type = "TestVisible"
			}
		}
	},
	{
		type = "Entity",
		name = "LittleFish",
		position = { y = 2, x = 1, z = 2},
		scale = { x = 0.5, y = 0.25, z = 0.75},
		rotation = { z = 30, x = 60, x = 20 },
		components = {
			{
				type = "Renderer",
				data = {
					mesh = "fish.mesh",
					material= "red"
				}
			},
			{
				type = "ParentTest",
				dependencies =
				{
					{
						entity = "Fish",
						name = "parent"
					}
				}
			},
			-- {
			-- 	type = "SimpleRotate"
			-- }
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
					color = { r = 0.6, g = 0.6, b = 0.6  },
					spec = { r = 0.6, g = 0.6, b = 0.6 },
					direction = { x = 0, y = 0, z = -0.75 }
				}
			}
		}
	}
};
return scene;
