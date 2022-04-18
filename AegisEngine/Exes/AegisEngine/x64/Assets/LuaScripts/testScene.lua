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
				type = "Renderer",
				data = {
					mesh = "fish.mesh",
					material= "blue"
				}
			},
			{
				type = "TestVisible"
			},
			{
				type = "Animation",
				data = {
					loop = true,
					easing = "linear", --Currently not working, we haven't implemented it yet, but we can
					keyframes = 
					{
						{
							position = { x = 0, y = 0, z = 0 },
							rotation = { x = 0, y = 0, z = 0 },
							scale = { x = 1, y = 1, z = 1 },
							time = 0
						},
						{
							position = {x = 2, y = 1, z = -2},
							rotation = { x = 90 },
							scale = { x = 1, y = 0.25, z = 0.25},
							time = 0.4
						},
						{
							position = {x = 2, y = 2, z = -2},
							time = 2
						},
						{
							position = { x = 0, y = 0, z = 0 },
							rotation = { x = 0, y = 0, z = 0 },
							scale = { x = 1, y = 1, z = 1 },
							time = 3
						}
					}
				}
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
				data = {
					parent="@Fish",
					parentRender = "@Fish.Renderer",
				}
			},
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
					color = { r = 0.6, g = 0.6, b = 0.6  },
					spec = { r = 0.6, g = 0.6, b = 0.6 },
					direction = { x = 0, y = 0, z = -0.75 }
				}
			}
		}
	}
};
return scene;
