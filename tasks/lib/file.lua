
function write_file(path, content)
    -- Write to file
    docs_file = io.open(path, "w");
    docs_file:write(content);

    print(#content .. ' bytes written in \x1b[90m' .. path .. '\x1b[0m');
end

return {
	write_file=write_file
}
