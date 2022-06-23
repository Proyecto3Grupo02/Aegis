-- Example of scene, it's just a table with list of entities

local NAME = "RotScene";
local scene = {
	{
		type = "MainCamera",
		position = { z = 10, y = 3  },
		rotation = { x = -25},
		components = {
			{
				type = "CameraTest"
			}
		}
	},
	-- {
	-- 	type = "UI",
	-- 	data = 
	-- 		{
	-- 			type = "Text",--Button/Image
	-- 			nombre = "TextoPrueba",
	-- 			order = 0,
	-- 			x = 1,
	-- 			y = 1,
	-- 			width = 100,
	-- 			height = 50,
	-- 			dimensionx=200,
	-- 			dimensiony=50,
	-- 		},
	-- }
	
};
return scene;
