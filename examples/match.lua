


function split(input, sep)
    local content={}
    for str in string.gmatch(input, "([^"..sep.."]+)") do
        table.insert(content, str)
    end
    return content
end

local s = ""..
"/**\n"..
" * \n"..
" * \n"..
" * @param x {{something}}\n"..
" * @{{param}} y something else\n"..
" * \n"..
" * drawsomething\n"..
" * \n"..
" * something else {{blablablal}} \n"..
" * something else blablablal \n"..
" * something else blablablal \n"..
" * \n"..
" * \n"..
" */\n"..
"int circle(lua_State* L) {\n";

print(string.match(s, "{{.-}}"));
