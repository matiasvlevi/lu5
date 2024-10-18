file_counters = {
    html=0,
    css=0,
    js=0,
    json=0
};

function get_counters(key)
    return file_counters[key];
end

function rm(path)
    os.remove(path);
end

function update_file_counters(c, path)
    if path:find(".html") ~= nil then c.html = c.html + 1 end
    if path:find(".css") ~= nil then  c.css  = c.css  + 1 end

    if path:find(".json") ~= nil then 
        c.json = c.json + 1
    elseif path:find(".js") ~= nil then 
        c.js = c.js   + 1 
    end
end

function find_files_in_dir(directory, f)
    if (f == nil) then
        f = function (str)
            return true;
        end
    end

    local i, t, popen = 0, {}, io.popen
    local pfile = popen('ls -a "'..directory..'"');
    for filename in pfile:lines() do
        i = i + 1
        if (f(filename)) then
            if (#filename > 2) then
                table.insert(t, 1, filename);
            end
        end
    end
    pfile:close();
    return t;
end

function color_weight(bytes)
    if (bytes > 1024 * 16) then
        return '31'
    elseif (bytes > 1024 * 8) then
        return '33'
    elseif (bytes > 1024 * 4) then
        return '93'
    end
    return '92';
end

function format_file_size(bytes)
    local size_str = string.format("%.2f kB", bytes/1000);
    local MAX_SIZE = 11;
    for i=#size_str, MAX_SIZE do
        size_str = ' ' .. size_str;
    end
    return '\x1b['.. color_weight(bytes) ..'m' .. size_str .. '\x1b[0m';
end

function write_file(path, content, log)
    if (log == nil) then log = false end;

    -- Write to file
    docs_file = io.open(path, "w");
    if (docs_file == nil) then return end;
    
    docs_file:write(content);

    if (log) then
        print(format_file_size(#content) .. ' \x1b[90m' .. path .. '\x1b[0m');
    end

    update_file_counters(file_counters, path);
end

function scandir(dir, _type)
    local p = io.popen('find "'..dir..'" -maxdepth 1 -type ' .. _type)    
    local res = {}
    for file in p:lines() do
        table.insert(res, file)
    end
    return res;
end

function mkdir(path)
    -- TODO: Will not work on windows...
    os.execute("mkdir -p " .. path)
end

function read_file(path)
    local c = io.open(path, 'r');
    if (c == nil) then
        error('Could not read ' .. path);
    end
    return c:read('a*');
end

--- Write a version controlled file
--- Used for pages or files that might have a version history
---@param dest_path string
---@param name string
---@param pagename string
---@param html string
---@param current_latest string
function write_vc_file(dest_path, name, pagename, html, current_latest)
    -- Formatting module page
    if (current_latest == VERSION) then
        local page_dir = dest_path .. '/latest/' .. name;
        mkdir(page_dir);
        write_file(page_dir .. '/' .. pagename, html, false);
    end

    -- Write in specific version
    local page_dir_v = dest_path .. '/v' .. VERSION .. '/' .. name;
    mkdir(page_dir_v);
    write_file(page_dir_v .. '/' .. pagename, html, true);
end

function copy_dir(source_dir, dest_dir)
    -- Copy all assets
    local asset_files = find_files_in_dir(source_dir);
    for i, filename in pairs(asset_files) do
        write_file(dest_dir .. '/' .. filename,
        read_file(source_dir .. '/' .. filename), true);
    end
end

return {
    mkdir=mkdir,
    scandir=scandir,
    map=map,
    filter=filter,
	write_file=write_file,
    read_file=read_file,
	find_files_in_dir=find_files_in_dir,
    get_counters=get_counters,
    write_vc_file=write_vc_file,
    copy_dir=copy_dir,
    rm=rm
}
