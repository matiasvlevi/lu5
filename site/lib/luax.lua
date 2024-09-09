---
--- A simple JSX-Like String builder
---
--- @param tag - The element's tag name
--- @param props - Properties & attributes
--- @param children - Children elements
---
--- @example
--- local luax = require('path/to/this/file');
---
--- local div = luax('div', {
---      luax('h2', 'Hello world!')
--- });
--- print(div) -- <div><h2>Hello world!</h2></div>
--- @example
--- 
--- @example
--- local luax = require('path/to/this/file');
---
--- local div = luax('div', {class="container"}, {
---      luax('h2', 'Hello world!'),
---      luax('span', {class="red"}, 'This text is red.')
--- });
--- print(div) -- <div class="container"><h2>Hello world!</h2><span class="red">This text is red.</span></div>
--- @example
---
--- Luax concatenates strings and wraps it with a tag.
--- If no tag is provided, luax just concatenates the strings.
---
--- @example
--- local luax = require('path/to/this/file');
---
--- local result = luax('', { 'a', 'b', 'c' });
--- print(result) -- abc
---
--- local result_with_tag = luax('tag', { 'a', 'b', 'c' });
--- print(result_with_tag) -- <tag>abc</tag>
--- @example
---
--- @author Matias Vazquez-Levi
--- @license MIT
---

--- Table used to include utilities or other JS-like functions (filter, map, join, etc) in the utils table.
local utils = {
    --- Map of all self closing tags
    self_closing_tags = {
        area=0,
        base=0, 
        br=0, 
        col=0, 
        command=0, 
        embed=0, 
        hr=0, 
        img=0, 
        input=0, 
        keygen=0, 
        link=0, 
        meta=0, 
        param=0, 
        source=0, 
        track=0, 
        wbr=0
    };
};

--- Determine if is a self closing tag according to Modern HTML spec
---@param elem string
function utils.is_single_closing(elem)
    return (utils.self_closing_tags[elem] ~= nil);
end

--- Join an array of strings to a strng
---@param list string[] The array to join
---@param sep string The separator segment in between array elements.
function utils.join(list, sep)
    if (sep == nil) then sep = '' end;
    if (#list < 1) then return '' end;
    if (#list == 1) then return list[1]; end;

    local str = list[1];

    for i=2,#list do
        str = str .. sep .. list[i];
    end
    
    return str;
end

---
--- Map data to strings
---
--- @param data The table data to map (either with indicies or keys)
--- @param cb The function which maps the data element to a string (Can be a component)
---
--- @example
--- local div = luax.map({ 'Bob', 'Jonh', 'Mark' }, function(name, i)
---     return luax('span', {id=i}, name);
--- end)
---
--- print(div) -- <span id="1">Bob</span><span id="2">Jonh</span><span id="3">Mark</span>
--- @example
---
function utils.map(data, cb)
    local res = {}
    local it = (type(data) == "table" and data[1] ~= nil) and ipairs or pairs;
    for k, value in it(data) do
        res[k] = cb(value, k);
    end
    return res;
end

---
--- Match case for inline logic
---
--- @param key The key to match
--- @param cases A table of strings
---
--- @example
--- -- can be either "banana", "apple", "raisin"
--- local value = "raisin";
--- local div = luax.match(value, {
---      banana=luax('p', 'todo: banana component'),
---      apple=luax('p', 'todo: apple component'),
---      raisin=luax('div', {
---          luax('p', 'This is a raisin')
---      }),
--- })
---
--- print(div) -- <div><p>This is a raisin</p></div>
--- @example
---
function utils.match(key, cases)
    if ((cases[key] ~= nil)) then
        local t = type(cases[key]);
        if (t == "string") then 
            return cases[key];
        elseif (t == "function") then
            return cases[key](key);
        else
            return '';
        end
    else
        return (cases["default"] ~= nil) and cases["default"] or '';
    end
end

--- Split a string in an array
---@param input string Main string
---@param sep string The separator segment
function utils.split(input, sep)
    local content={}
    for str in string.gmatch(input, "([^"..sep.."]+)") do
        table.insert(content, str);
    end
    return content
end

--- Filter a numeric table
---@param list any[] the numeric table to filter 
---@param cb (any)=>bool the filter callback, if returns false, element is filtered out. 
function utils.filter(list, cb)
    local res = {}
    for i, elem in ipairs(list) do
        if (cb(elem, i)) then
            table.insert(res, elem)
        end
    end
    return res;
end

--- Equivalent to javascript's destructuring (operator ...)
--- @param a host object
--- @param b object to merge
---
function utils.merge(a, b)
    local res = {};

    for key, value in pairs(a) do
        res[key] = value;
    end
    for key, value in pairs(b) do
        res[key] = value;
    end
    
    return res;
end

--- Reverse a numeric table
--- @param list the table to reverse
function utils.reverse(list)
    local res = {}
    for i, elem in ipairs(list) do
        table.insert(res, 1, elem)
    end
    return res;
end

--- Insert segment into string
--- @param host The main string
--- @param segment The segment to insert into the main string
--- @param pos The character postition of the inserted segment
function utils.insert(host, segment, pos)
    return host:sub(1,pos-1)..segment..host:sub(pos+1)
end

--- Format xml attributes
--- @param props The properties or attributes to add to the resulting xml
function utils.format_props(props)
    -- Format props to string
    local prop_index = 1;
    local prop_count = 0;
    for _,_ in pairs(props) do prop_count = prop_count + 1 end
    local prop_string = (prop_count > 0 and ' ' or '');
    for name, value in pairs(props) do
        local value_type = type(value);
        
        -- Append property
        if (value_type == "boolean") then
            prop_string = prop_string ..  (value and name or '');
        else
            prop_string = prop_string .. 
                name .. '="' .. value .. '"'
        end

         -- Append Space Separator 
        prop_string = prop_string .. 
                ((prop_index < prop_count and value) and ' ' or '');        
        
        prop_index = prop_index + 1
    end
    return prop_string;
end

--- Get formatted children
--- @param children
function utils.children_to_string(children)
    -- Format children to string
    local children_string = '';

    if (type(children) == "table") then
        for i, child in ipairs(children) do
            if (type(child) == "table") then
                -- Add table child & concatenate with luax
                children_string = children_string .. luax('', {}, child)
            else
                -- Add string child
                children_string = children_string .. tostring(child);
            end
        end
    elseif (children ~= nil) then
        -- Set sing children string
        children_string = tostring(children);
    end

    return children_string;
end

--- Core luax function
---@param tag string The tag to create
---@param props any{} Tag attributes
---@param children string|string[] The children elements
function luax(tag, props, children)
    -- If tag is empty, return children alone without formating
    -- Commonly known as 'Fragment'
    if (#tag == 0 or string.len(tag) == 0) then
        return utils.children_to_string(children);
    end

    -- Self closing
    local is_single_closing = utils.is_single_closing(tag);
    if (is_single_closing) then
        return '<'..tag .. utils.format_props(props) .. '/>';
    end

    -- With closing tag
    return (
        '<'..tag .. utils.format_props(props) .. '>'
            .. utils.children_to_string(children) ..
        '</' .. tag .. '>'
    )
end;

--- __call will handle luax's argument logic.
local mt = { 
    __call=function(t, tag, arg1, arg2)
        -- Set arguments
        local props, children;
        if (arg2 == nil and (type(arg1) ~= "table" or arg1[1] ~= nil)) then
            props = {}  ; children = arg1;
        else
            props = arg1; children = arg2;
        end

        return luax(tag, props, children);
    end
};

return setmetatable(utils, mt);