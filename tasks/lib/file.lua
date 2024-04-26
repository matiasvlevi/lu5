function find_headers_in_dir(directory)
    local i, t, popen = 0, {}, io.popen
    local pfile = popen('ls -a "'..directory..'"');
    for filename in pfile:lines() do
        print(filename);
        i = i + 1
        if (string.find(filename, '%.h')) then
            -- Store filename without extention
            table.insert(t, 1, string.sub(filename, 1, #filename-2));
        end
    end
    pfile:close()
    return t
end

function write_file(path, content)
    -- Write to file
    docs_file = io.open(path, "w");
    docs_file:write(content);

    print(#content .. ' bytes written in \x1b[90m' .. path .. '\x1b[0m');
end

return {
	write_file=write_file,
	find_headers_in_dir=find_headers_in_dir
}
