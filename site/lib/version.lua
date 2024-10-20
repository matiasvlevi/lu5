local luax = require('./site/lib/luax');
local fs   = require('./site/lib/file');

local function to_number(version)
    local ans = {}
    for part in string.gmatch(version, "%d+") do
        table.insert(ans, tonumber(part))
    end
    return ans;
end

local function compare_version_tags(v1, v2)
    local parts1 = to_number(v1);
    local parts2 = to_number(v2);

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

function get_version_tags(path)
    local versions = luax.map(luax.filter(fs.scandir(path, "d"), 
    function(dir, i)
        return string.find(dir, "v%d.%d.%d");
    end), 
    function(version_dir, i)
        return string.match(version_dir, "%d.%d.%d");
    end);
    table.sort(versions, compare_version_tags);
    return versions;
end

return { get_version_tags=get_version_tags, to_number=to_number };