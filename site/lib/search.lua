--- Format an array of modules, to a single table of contents of all methods
---@param arr any
local function get_method_table_of_contents(arr)
    local methods = {}
    for _, mod in ipairs(arr) do
        for _, method in ipairs(mod.methods) do
            if (method.doc._type ~= "constant") then
                table.insert(methods, {
                    name = method.doc.name,
                    module = mod.source
                    -- -- Not needed
                    --   description = method.doc.description,
                    --   type = method.doc._type
                })
            end
        end
    end
    return methods
end

return { get_method_table_of_contents=get_method_table_of_contents }