-- simple modules

-- capture the name searched for by require
local NAME="myMath"

-- table for our functions
local M = { }

function M.addtwo(a,b) return a+b end
function M.subtwo(a,b) return a-b end

return M