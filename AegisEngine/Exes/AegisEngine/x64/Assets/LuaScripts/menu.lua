--Example of scene, it's just a table with list of entities

local NAME = "menu";
local scene = {
-- camera and light
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
		},

	
-- UI FONDO Y TITULO
	{
		type = "UI",
		data = 
			{
				type = "Image",--Button/Image
				nombre = "Fondo",
				material = "fondo_menu_material",
				order = 0,
				x = 0,
				y = 0,
				width = 0.999,
				height = 0.999,
				visible = true,
			},
	},
	{
        type = "UI",
		data = 
			{
				type = "Image",--Button/Image
				nombre = "Titulo",
				material = "nombre_material",
				order = 1,
				x = 0.35,
				y = 0,
				width = 0.4,
				height = 0.2,
				visible = true,
			},
	},
-- UI BOTONES
	{
        type = "UI",
		data = 
			{
				type = "Image",--Button/Image
				nombre = "Logo",
				material = "logo_aegis_material",
				order = 1,
				x = 0,
				y = 1,
				width = 0.1,
				height = 0.2,
				visible = true,
			},
	},
	{
        type = "UI",
		data = 
			{
				type = "Button",--Button/Image
				nombre = "Play",
				material = "start_material",
				order = 1,
				x = 0.475,
				y = 0.7,
				width = 0.2,
				height = 0.2,
				visible = true,
				callback = function()
					print("START");	
					-- local fondo = "@Fondo"
					-- fondo:SetVisible(false)
				end 
			},
	},
	{
        type = "UI",
		data = 
			{
				type = "Button",--Button/Image
				nombre = "Story",
				material = "story_material",
				order = 1,
				x = 0,
				y = 0.1,
				width = 0.1,
				height = 0.1,
				visible = true,
				callback = function()
					print("STORY");	
				end 
			},
	},
	{
        type = "UI",
		data = 
			{
				type = "Button",--Button/Image
				nombre = "HowToPlay",
				material = "htp_material",
				order = 1,
				x = 0,
				y = 0.3,
				width = 0.1,
				height = 0.1,
				visible = true,
				callback = function()
					print("HTP");	
				end 
			},
	},
-- UI CONTROLES E HISTORIA
	{
		type = "UI",
		data = 
			{
				type = "Image",--Button/Image
				nombre = "Controles",
				material = "controles_material",
				order = 3,
				x = 0.15,
				y = 0.15,
				width = 0.999,
				height = 0.999,
				visible = false,
			},
	},
	{
		type = "UI",
		data = 
			{
				type = "Image",--Button/Image
				nombre = "Historia",
				material = "historia_material",
				order = 3,
				x = 0,
				y = 0,
				width = 0.999,
				height = 0.999,
				visible = false,
			},
	},
	{
        type = "UI",
		data = 
			{
				type = "Button",--Button/Image
				nombre = "Back",
				material = "back_material",
				order = 4,
				x = 0,
				y = 0,
				width = 0.2,
				height = 0.2,
				visible = false,
				callback = function()
					print("BACK");	
				end 
			},
	},
};
return scene;
