local NAME="initLua"
print("Lua initialization from engine");
local utility = require "utils";
_G["utils"] = utility;

function initLua()
end