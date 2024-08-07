local luax = require('./tasks/lib/luax');
local fs   = require('./tasks/lib/file');
local Config = require('./tasks/siteconfig');

function get_version_tags()
    local function compare_version_tags(v1, v2)
        local parts1 = {}
        for part in string.gmatch(v1, "%d+") do
            table.insert(parts1, tonumber(part))
        end
    
        local parts2 = {}
        for part in string.gmatch(v2, "%d+") do
            table.insert(parts2, tonumber(part))
        end
    
        for i = 1, math.max(#parts1, #parts2) do
            local num1 = parts1[i] or 0
            local num2 = parts2[i] or 0
            if num1 < num2 then
                return true
            elseif num1 > num2 then
                return false
            end
        end
    
        return false
    end
    
    local versions = luax.map(luax.filter(fs.scandir(Config.build.dest, "d"), 
    function(dir, i)
        return string.find(dir, "v%d.%d.%d");
    end), 
    function(version_dir, i)
        return string.match(version_dir, "%d.%d.%d");
    end);
    table.sort(versions, compare_version_tags);

    return versions;
end

return get_version_tags;