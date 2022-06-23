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
				name = "Fondo",
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
				name = "Titulo",
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
				name = "Logo",
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
				name = "Play",
				material = "start_material",
				order = 1,
				x = 0.475,
				y = 0.7,
				width = 0.2,
				height = 0.2,
				visible = true,
				callback = function()
					print("START");	
					local terrainScene = require "TerrainScene";
					SceneManager:LoadScene(terrainScene);
				end 
			},
	},
	{
        type = "UI",
		data = 
			{
				type = "Button",--Button/Image
				name = "Story",
				material = "story_material",
				order = 1,
				x = 0,
				y = 0.2,
				width = 0.1,
				height = 0.1,
				visible = true,
				uiData = { id = 1, image = "@Historia", backButton="@Back" },
				callback = function(uiData)
					print("STORY");	
					uiData.image:SetVisible(true)
					uiData.backButton:SetVisible(true)
				end 
			},
	},
	{
        type = "UI",
		data = 
			{
				type = "Button",--Button/Image
				name = "HowToPlay",
				material = "htp_material",
				order = 1,
				x = 0,
				y = 0.4,
				width = 0.1,
				height = 0.1,
				visible = true,
				uiData = { id = 1, image = "@Controles", backButton="@Back" },
				callback = function(uiData)
					print("HTP");	
					uiData.image:SetVisible(true)
					uiData.backButton:SetVisible(true)
				end 
			},
	},
-- UI CONTROLES E HISTORIA
	{
		type = "UI",
		data = 
			{
				type = "Image",--Button/Image
				name = "Controles",
				material = "controles_material",
				order = 4,
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
				type = "Image",--Button/Image
				name = "Historia",
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
				name = "Back",
				material = "back_material",
				order = 4,
				x = 0,
				y = 0,
				width = 0.2,
				height = 0.2,
				visible = false,
				uiData = { id = 1, imageH ="@Historia", imageC = "@Controles", backButton="@Back" },
				callback = function(uiData)
					print("BACK");	
					uiData.imageH:SetVisible(false)
					uiData.imageC:SetVisible(false)
					uiData.backButton:SetVisible(false)
				end 
			},
	},
};
return scene;
