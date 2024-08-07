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
    pfile:close()
    return t;
end

function write_file(path, content)
    -- Write to file
    docs_file = io.open(path, "w");
    docs_file:write(content);

    -- Color based on file size
    local color = '92';
    local bytes = #content;
    if (bytes > 1024 * 16) then
        color = '91'
    elseif (bytes > 1024 * 8) then
        color = '93'
    end

    local fmt_size = '\x1b['.. color ..'m' .. 
        string.format("%.2f kB", bytes/1000) .. '\x1b[0m';

    print(fmt_size .. ' written in \x1b[90m' .. path .. '\x1b[0m');
end

function read_file(path)
    local c = io.open(path, 'r');
    if (c == nil) then
        error('Could not read ' .. path);
    end
    return c:read('a*');
end

return {
	write_file=write_file,
    read_file=read_file,
	find_files_in_dir=find_files_in_dir
}
